#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 405;

int n, A[maxn][maxn], b[maxn];
char str[maxn];

int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for(int i = 1; i <= n; i++) {
		b[i] = str[i] - '0';
			
		A[i][i] = 1;
		if(i != 1)
			A[i][i - 1] = 1;
		if(i != n)
			A[i][i + 1] = 1;
	}
	scanf("%s", str + 1);
	for(int i = 1; i <= n; i++)
		b[i] ^= str[i] - '0';
	
	int pos = n + 1;
	for(int i = 1; i <= n; i++) {
		if(A[i][i] == 0) {
			int j = i + 1;
			for(; j <= n && A[j][i] == 0; j++);
			if(j == n + 1) {
				pos = i;
				break;
			}
			for(int k = i; k <= n; k++)
				swap(A[i][k], A[j][k]);
			swap(b[i], b[j]);
		}
		for(int j = 1; j <= n; j++)
			if(i != j && A[j][i] != 0) {
				for(int k = i; k <= n; k++)
					A[j][k] ^= A[i][k];
				b[j] ^= b[i];
			}
	}
	
	int flag = 0;
	for(int i = pos; i <= n; i++)
		if(b[i] != 0) {
			flag = 1;
			break;
		}

	if(flag)
		printf("impossible");
	else {
		int ans = n;
		int s = n - pos + 1;
		for(int i = (1 << s) - 1; ~i; i--) {
			int x[maxn];
			memset(x, 0, sizeof(x));
			for(int j = pos; j <= n; j++)
				x[j] = (i >> (j - pos)) & 1;
			for(int j = 1; j < pos; j++) {
				x[j] = b[j];
				for(int k = pos; k <= n; k++)
					if(A[j][k] == 1)
						x[j] ^= x[k];
			}
			int res = 0;
			for(int j = 1; j <= n; j++)
				res += x[j] == 1;
			ans = min(ans, res);
		}
		printf("%d", ans);
	}
	return 0;
}

