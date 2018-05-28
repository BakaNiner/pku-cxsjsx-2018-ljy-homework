#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 205, maxv = 10005;

int n, V, v[maxn], dp[maxv], f[maxv];
vector<int> ans;

int main() {
	scanf("%d%d", &n, &V);
	for(int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	
	dp[0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = V; j >= v[i]; j--)
			dp[j] += dp[j - v[i]];
	
	for(int i = 1; i <= n; i++) {
		memset(f, 0, sizeof(f));
		
		f[0] = 1;
		for(int j = 1; j <= V; j++)
			f[j] = j >= v[i] ? dp[j] - f[j - v[i]] : dp[j];
			
		if(f[V] == 0)
			ans.push_back(i);
	}

	printf("%d\n", ans.size());
	for(int x : ans)
		printf("%d ", v[x]);	
	return 0;
}
