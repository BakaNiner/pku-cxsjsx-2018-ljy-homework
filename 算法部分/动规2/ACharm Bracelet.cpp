#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 5005, maxm = 15005;

int n, m, w[maxn], v[maxn], dp[maxm];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &w[i], &v[i]);
	
	for(int i = 1; i <= n; i++)
		for(int j = m; j >= w[i]; j--)
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
	
	printf("%d\n", dp[m]);
	return 0;
}

