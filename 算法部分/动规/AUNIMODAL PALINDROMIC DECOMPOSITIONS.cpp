#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 1005;

int n;
LL dp[maxn][maxn];

int main() {
	n = 250;
	for(int i = 1; i <= n; i++) {
		dp[0][i] = 1;
		for(int j = (i >> 1) + 1; j <= i; j++)
			dp[i][j] = 1;
		for(int j = i >> 1; j > 0; j--)
			dp[i][j] = dp[i][j + 1] + dp[i - (j << 1)][j];
	}
	while(1) {
		scanf("%d", &n);
		if(n == 0)
			break;
		
		printf("%d %lld\n", n, dp[n][1]);
	}
	return 0;
}

