#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

const int maxn = 20;

int a[maxn];
vector<int> ans, res;

// A 1 B 2 C 3 D 4 E 5 F 6 G 7 H 8 I 9
int tr[][6] = {
{4, 1, 2, 4, 5},
{3, 1, 2, 3},
{4, 2, 3, 5, 6},
{3, 1, 4, 7},
{5, 2, 4, 5, 6, 8},
{3, 3, 6, 9},
{4, 4, 5, 7, 8},
{3, 7, 8, 9},
{4, 5, 6, 8, 9}
};

bool check() {
	for(int i = 1; i <= 9; i++)
		if(a[i] != 0)
			return 0;
	return 1;
}

void dfs(int x) {
	if(x == 9) {
		if(check() && (ans.size() == 0 || res.size() < ans.size()))
			ans = res;
		return;
	}

	// 每个操作最多3次 
	for(int i = 0; i <= 3; i++) {
		for(int j = 1; j <= i; j++) {
			res.push_back(x);
			for(int j = 1; j <= tr[x][0]; j++)
				a[tr[x][j]] = (a[tr[x][j]] + 1) % 4;
		}
		dfs(x + 1);
		for(int j = 1; j <= i; j++) {
			res.pop_back();
			for(int j = 1; j <= tr[x][0]; j++)
				a[tr[x][j]] = (a[tr[x][j]] - 1 + 4) % 4;
		}
	}
}

int main() {
	for(int i = 1; i <= 9; i++)
		scanf("%d", &a[i]);
	dfs(0);
	for(int x : ans)
		printf("%d ", x + 1);
	return 0;
}

