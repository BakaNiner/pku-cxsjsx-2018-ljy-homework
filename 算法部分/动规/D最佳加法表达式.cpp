#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 55;

int n, m;
string str;

struct bigint {
	int num[maxn];
	int len;
	
	bigint(int x = 0) {
		memset(num, 0, sizeof(num));
		if(x == 0)
			len = 1;
		else
			for(len = 0; x; x /= 10)
				num[++len] = x % 10;
	}
	
	bigint(const string &s) {
		memset(num, 0, sizeof(num));
		len = s.size();
		for(int i = 1; i <= len; i++)
			num[i] = s[len - i] - '0';
	}
	
	bool operator < (const bigint &x) const {
		if(len != x.len)
			return len < x.len;
		for(int i = len; i >= 1; i--)
			if(num[i] != x.num[i])
				return num[i] < x.num[i];
		return 0;
	}
	
	bigint operator + (const bigint &x) const {
		bigint res(0);
		res.len = max(len, x.len) + 1;
		for(int i = 1; i <= res.len; i++) {
			res.num[i] += num[i] + x.num[i];
			res.num[i + 1] += res.num[i] / 10;
			res.num[i] %= 10;
		}
		for(; res.len > 1 && res.num[res.len] == 0; res.len--);
		return res;
	}
	
	friend ostream& operator << (ostream &os, const bigint &x) {
		for(int i = x.len; i >= 1; i--)
			os << x.num[i];
		return os;
	}
	
} dp[maxn][maxn], inf;

int main() {
	ios::sync_with_stdio(false);
	
	inf.len = maxn - 1;
	for(int i = 1; i < maxn; i++)
		inf.num[i] = 9;

	while(cin >> m) {
		cin >> str;
		n = str.size();
		
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= m; j++)
				dp[i][j] = inf;
		
		dp[0][0] = 0;
		for(int i = 1; i <= n; i++) {
			dp[i][0] = str.substr(0, i);
			for(int k = 0; k < i; k++)
				for(int j = 1; j <= min(i - 1, m); j++)
					dp[i][j] = min(dp[i][j], dp[k][j - 1] + bigint(str.substr(k, i - k)));
		}
		cout << dp[n][m] << endl;
	}
	return 0;
}

