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
	
	int i = 1;
	for(; i <= n; i++) {
		if(A[i][i] == 0) {
			int j = i + 1;
			for(; j <= n && A[j][i] == 0; j++);
			if(j == n + 1)
				break;
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
	for(int j = i; j <= n; j++)
		if(b[j] != 0) {
			flag = 1;
			break;
		}

	if(flag)
		printf("impossible");
	else {
		for(int i = 1; i <= n; i++)
			b[0] += b[i];
		printf("%d", b[0]);
	}
	return 0;
}

