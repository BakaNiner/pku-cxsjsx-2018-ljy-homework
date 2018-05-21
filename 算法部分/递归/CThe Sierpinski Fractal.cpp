#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int maxn = 5005;

int n;
char a[maxn][maxn];

void dfs(int u, int x, int y) {
/*
	 /\ 
	/__\
*/
	if(u == 1) {
		a[x][y] = ' ';
		a[x][y + 1] = '/';
		a[x][y + 2] = '\\';
		a[x][y + 3] = ' ';
		a[x + 1][y] = '/';
		a[x + 1][y + 1] = '_';
		a[x + 1][y + 2] = '_';
		a[x + 1][y + 3] = '\\';
		return;
	}
	
	dfs(u - 1, x + (1 << (u - 1)), y);
	dfs(u - 1, x, y + (1 << (u - 1)));
	dfs(u - 1, x + (1 << (u - 1)), y + (1 << u));
}

int main() {
	while(1) {
		scanf("%d", &n);
		if(n == 0)
			break;
		
		memset(a, 0, sizeof(a));
		int tot = 1 << n;
		for(int i = 1; i <= tot; i++)
			for(int j = 1; j <= tot << 1; j++)
				a[i][j] = ' ';
		
		dfs(n, 1, 1);
		for(int i = 1; i <= tot; i++) {
			printf("%s", a[i] + 1);
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
