#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 205, maxv = 10005;

int n, V, v[maxn];
bool dp1[maxn][maxv], dp2[maxn][maxv];
vector<int> ans;

int main() {
	scanf("%d%d", &n, &V);
	for(int i = 1; i <= n; i++)
		scanf("%d", &v[i]);

	dp1[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= V; j++) {
			dp1[i][j] |= dp1[i - 1][j];
			if(j >= v[i])
				dp1[i][j] |= dp1[i - 1][j - v[i]];
		}
	
	dp2[n + 1][0] = 1;
	for(int i = n; i >= 1; i--)
		for(int j = 0; j <= V; j++) {
			dp2[i][j] |= dp2[i + 1][j];
			if(j >= v[i])
				dp2[i][j] |= dp2[i + 1][j - v[i]];
		}
	
	for(int i = 1; i <= n; i++) {
		bool flag = 0;
		for(int j = V; j >= 0; j--)
			if(dp1[i - 1][j] && dp2[i + 1][V - j]) {
				flag = 1;
				break;
			}
		if(!flag)
			ans.push_back(i);
	}

	printf("%d\n", ans.size());
	for(int x : ans)
		printf("%d ", v[x]);	
	return 0;
}
