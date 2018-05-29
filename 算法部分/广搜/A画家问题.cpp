#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 405;

int n, A[maxn][maxn], b1[maxn], b2[maxn];
char str[maxn];

int id(int x, int y) {
	return n * (x - 1) + y;
}

int main() {
	n = 4;
	for(int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		for(int j = 1; j <= n; j++) {
			b1[id(i, j)] = str[j] == 'w';
			b2[id(i, j)] = str[j] == 'b';
			
			A[id(i, j)][id(i, j)] = 1;
			if(i != 1)
				A[id(i, j)][id(i - 1, j)] = 1;
			if(i != n)
				A[id(i, j)][id(i + 1, j)] = 1;
			if(j != 1)
				A[id(i, j)][id(i, j - 1)] = 1;
			if(j != n)
				A[id(i, j)][id(i, j + 1)] = 1;
		}
	}
	
	int m = n * n;
	int pos = m + 1;
	for(int i = 1; i <= m; i++) {
		if(A[i][i] == 0) {
			int j = i + 1;
			for(; j <= m && A[j][i] == 0; j++);
			if(j == m + 1) {
				pos = i;
				break;
			}
			for(int k = i; k <= m; k++)
				swap(A[i][k], A[j][k]);
			swap(b1[i], b1[j]);
			swap(b2[i], b2[j]);
		}
		for(int j = 1; j <= m; j++)
			if(i != j && A[j][i] != 0) {
				for(int k = i; k <= m; k++)
					A[j][k] ^= A[i][k];
				b1[j] ^= b1[i];
				b2[j] ^= b2[i];
			}
	}
	
//	for(int i = 1; i <= m; i++) {
//		for(int j = 1; j <= m; j++)
//			printf("%d ", A[i][j]);
//		printf("%d ", b1[i]);
//		printf("%d\n", b2[i]);
//	}
	
	int flag1 = 0;
	for(int i = pos; i <= m; i++)
		if(b1[i] != 0) {
			flag1 = 1;
			break;
		}
	int flag2 = 0;
	for(int i = pos; i <= m; i++)
		if(b2[i] != 0) {
			flag2 = 1;
			break;
		}

	if(flag1 && flag2)
		printf("Impossible");
	else {
		int ans = m;
		int s = m - pos + 1;
		for(int i = (1 << s) - 1; ~i; i--) {
			int x[maxn];
			memset(x, 0, sizeof(x));
			for(int j = pos; j <= m; j++)
				x[j] = (i >> (j - pos)) & 1;
			if(!flag1) {
				for(int j = 1; j < pos; j++) {
					x[j] = b1[j];
					for(int k = pos; k <= m; k++)
						if(A[j][k] == 1)
							x[j] ^= x[k];
				}
				int res = 0;
				for(int j = 1; j <= m; j++)
					res += x[j] == 1;
				ans = min(ans, res);
			}
			if(!flag2) {
				for(int j = 1; j < pos; j++) {
					x[j] = b2[j];
					for(int k = pos; k <= m; k++)
						if(A[j][k] == 1)
							x[j] ^= x[k];
				}
				int res = 0;
				for(int j = 1; j <= m; j++)
					res += x[j] == 1;
				ans = min(ans, res);
			}		
		}
		printf("%d", ans);
	}
	return 0;
}

