#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

const int maxn = 20;

int n, dp[1 << maxn], bin[maxn];
string met[1 << maxn];

struct __data {
	int d, c;
	string name;
	
	bool operator < (const __data &x) const {
		return name < x.name;
	}
} p[maxn];

int main() {
	bin[0] = 1;
	for(int i = 1; i < maxn; i++)
		bin[i] = bin[i - 1] << 1;
	
	ios::sync_with_stdio(false);
	int T; cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> p[i].name >> p[i].d >> p[i].c;
		sort(p + 1, p + 1 + n);
		
		dp[0] = 0;
		met[0] = "";
		int maxs = bin[n];
		for(int s = 1; s < maxs; s++) {
			dp[s] = 0x3f3f3f3f;
			met[s] = string("z", 20);
		}
		
		for(int s = 0; s < maxs; s++) {
			int t = 0;
			for(int i = 1; i <= n; i++)
				if(s & bin[i - 1])
					t += p[i].c;
			
			for(int i = 1; i <= n; i++)
				if(!(s & bin[i - 1])) {
					string tmp = met[s];
					tmp.push_back(i - 1 + 'a');
					if(dp[s | bin[i - 1]] > dp[s] + max(0, t + p[i].c - p[i].d) || dp[s | bin[i - 1]] == dp[s] + max(0, t + p[i].c - p[i].d) && met[s | bin[i - 1]] > tmp) {
						dp[s | bin[i - 1]] = dp[s] + max(0, t + p[i].c - p[i].d);
						met[s | bin[i - 1]] = tmp;
					}
				}
		}
		
		cout << dp[maxs - 1] << endl;
		for(int i = 0; i < n; i++)
			cout << p[met[maxs - 1][i] - 'a' + 1].name << endl;
	}
	return 0;
}

