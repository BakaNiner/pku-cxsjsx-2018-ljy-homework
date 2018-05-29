#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 105;

int n, g[maxn][maxn], dis[maxn][maxn], vis[maxn][maxn];
queue<pii> q;
stack<pii> s;
pii pre[maxn][maxn];

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

int main() {
	n = 5;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &g[i][j]);
	
	memset(dis, 0x3f, sizeof(dis));
	q.push(pii(1, 1));
	dis[1][1] = 0;
	vis[1][1] = 1;
	pre[1][1] = pii(0, 0);
	
	while(!q.empty()) {
		pii p = q.front(); q.pop();
		int x = p.first, y = p.second;
		vis[x][y] = 0;
		
		for(int d = 0; d < 4; d++) {
			int xx = x + dx[d], yy = y + dy[d];
			if(xx < 1 || xx > n || yy < 1 || yy > n)
				continue;
			if(g[xx][yy] == 1)
				continue;
			
			if(!vis[xx][yy] && dis[xx][yy] > dis[x][y] + 1) {
				dis[xx][yy] = dis[x][y] + 1;
				vis[xx][yy] = 1;
				pre[xx][yy] = pii(x, y);
				q.push(pii(xx, yy));
			}
		}
	}
	
	int x = n, y = n;
	while(x != 0 || y != 0) {
		s.push(pii(x, y));
		pii t = pre[x][y];
		x = t.first;
		y = t.second;
	}
	while(!s.empty()) {
		pii t = s.top(); s.pop();
		printf("(%d, %d)\n", t.first - 1, t.second - 1);
	}
	return 0;
}

