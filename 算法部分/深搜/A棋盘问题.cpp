#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 105;

int n, k, g[maxn][maxn], vis[maxn], ans;
char str[maxn];

void dfs(int x, int left) {
	if(x == n + 1) {
		if(left == 0)
			ans++;
		return;
	}
	if(n - x + 1 < left)
		return;
	
	dfs(x + 1, left);
	for(int i = 1; i <= n; i++)
		if(g[x][i] && !vis[i]) {
			vis[i] = 1;
			dfs(x + 1, left - 1);
			vis[i] = 0;
		}
}

int main() {
	while(1) {
		scanf("%d%d", &n, &k);
		if(n == -1)
			break;
		
		for(int i = 1; i <= n; i++) {
			scanf("%s", str + 1);
			for(int j = 1; j <= n; j++)
				g[i][j] = str[j] == '#';
		}
		
		ans = 0;
		dfs(1, k);
		printf("%d\n", ans);
	}
	return 0;
}

