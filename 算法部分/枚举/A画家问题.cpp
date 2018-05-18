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
	int pos = m + 1;
	for(int i = 1; i <= m; i++) {
		if(A[i][i] == 0) {
			int j = i + 1;
			for(; j <= m && A[j][i] == 0; j++);
			if(j == m + 1) {
				pos = i;
				// ��Ϊϵ�������Ǹ���״�����������A[i][i]��0�Ļ������½Ƕ���0������ֹͣ��Ԫ 
				break;
			}
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
	
//	for(int i = 1; i <= m; i++) {
//		for(int j = 1; j <= m; j++)
//			printf("%d ", A[i][j]);
//		printf("%d\n", b[i]);
//	}
	
	// �ж��Ƿ��� 0 = 1 ���ַ��̣�pos֮�󣨰���pos����������Ԫ 
	int flag = 0;
	for(int i = pos; i <= m; i++)
		if(b[i] != 0) {
			flag = 1;
			break;
		}

	if(flag)
		printf("inf");
	else {
		int ans = m;
		// ����Ԫ�ĸ���
		int s = m - pos + 1;
		// ö������Ԫ��ȡֵ
		for(int i = (1 << s) - 1; ~i; i--) {
			int x[maxn];
			memset(x, 0, sizeof(x));
			for(int j = pos; j <= m; j++)
				x[j] = (i >> (j - pos)) & 1;
			// �ش�
			for(int j = 1; j < pos; j++) {
				x[j] = b[j];
				for(int k = pos; k <= m; k++)
					if(A[j][k] == 1)
						x[j] ^= x[k];
			}
			// ͳ�� 
			int res = 0;
			for(int j = 1; j <= m; j++)
				res += x[j] == 1;
			ans = min(ans, res);
		}
		printf("%d", ans);
	}
	return 0;
}

