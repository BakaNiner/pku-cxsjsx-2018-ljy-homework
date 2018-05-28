#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;

int n, m, g[maxn][maxn], dp[maxn][maxn];

int dx[] = {-1, 1}, dy[] = {-1, 1};

int dfs(int i, int j) {
	if(dp[i][j])
		return dp[i][j];
		
	dp[i][j] = 1;
	for(int d = 0; d < 2; d++) {
		int x = i + dx[d], y = j;
		if(x >= 1 && x <= n && g[x][y] > g[i][j])
			dp[i][j] = max(dp[i][j], dfs(x, y) + 1);
	}
	for(int d = 0; d < 2; d++) {
		int x = i, y = j + dy[d];
		if(y >= 1 && y <= m && g[x][y] > g[i][j])
			dp[i][j] = max(dp[i][j], dfs(x, y) + 1);
	}
	return dp[i][j];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &g[i][j]);
	
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			ans = max(ans, dfs(i, j));
	printf("%d\n", ans);
	return 0;
}

