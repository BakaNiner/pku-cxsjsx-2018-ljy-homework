#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 105;

int n, V, Sbound[maxn], Vbound[maxn], ans;

void dfs(int x, int now, int left, int rb, int hb) {
	if(x == n + 1) {
		if(left == 0)
			ans = min(ans, now);
		return;
	}
	if(now + Sbound[x + 1] >= ans)
		return;
	if(left < Vbound[x + 1])
		return;
	// 体积固定的圆柱体，半径越大，表面积越小 
	if(2 * left / rb + now >= ans)
		return;
	
	for(int r = rb - 1; r >= n - x + 1; r--) {
		if(x == 1)
			now = r * r;
		int _hb = min(hb - 1, (left - Vbound[x + 1]) / (r * r));
		for(int h = _hb; h >= n - x + 1; h--)
			dfs(x + 1, now + 2 * r * h, left - r * r * h, r, h);
	}
}

int main() {
	scanf("%d%d", &V, &n);
	
	for(int i = 1; i <= n; i++) {
		Sbound[n - i + 1] = Sbound[n - i + 2] + 2 * i * i;
		Vbound[n - i + 1] = Vbound[n - i + 2] + i * i * i;
	}
	
	ans = 0x3f3f3f3f;
	dfs(1, 0, V, V + 1, V + 1);
	
	if(ans == 0x3f3f3f3f)
		ans = 0;
	printf("%d\n", ans);
	return 0;
}

