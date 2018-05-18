#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 405;

int n, A[maxn][maxn], b[maxn];
char str[maxn];

int id(int x, int y) {
	return n * (x - 1) + y;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		for(int j = 1; j <= n; j++) {
			b[id(i, j)] = str[j] == 'w';
			
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
	int i = 1;
	for(; i <= m; i++) {
		if(A[i][i] == 0) {
			int j = i + 1;
			for(; j <= m && A[j][i] == 0; j++);
			if(j == m + 1)
				// 因为系数矩阵是个带状矩阵，所以如果A[i][i]是0的话，右下角都是0，可以停止消元 
				break;
			for(int k = i; k <= m; k++)
				swap(A[i][k], A[j][k]);
			swap(b[i], b[j]);
		}
		for(int j = 1; j <= m; j++)
			if(i != j && A[j][i] != 0) {
				for(int k = i; k <= m; k++)
					A[j][k] ^= A[i][k];
				b[j] ^= b[i];
			}
	}
	
	// 判断是否有 0 = 1 这种方程 
	int flag = 0;
	for(int j = i; j <= m; j++)
		if(b[j] != 0) {
			flag = 1;
			break;
		}

	if(flag)
		printf("inf");
	else {
		// 不用枚举自由元，直接令所有自由元为0就是最小解 
		for(int i = 1; i <= m; i++)
			b[0] += b[i];
		printf("%d", b[0]);
	}
	return 0;
}

