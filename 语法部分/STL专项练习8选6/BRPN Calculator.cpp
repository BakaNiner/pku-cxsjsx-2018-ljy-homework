#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

const int maxn = 1005;

int n;
string str;
stack<double> num;
priority_queue<double, vector<double>, greater<double> > mem;

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		double x; cin >> x;
		mem.push(x);
	}
	while(cin >> str) {
		if(str == "+") {
			double x = num.top(); num.pop();
			double y = num.top(); num.pop();
			num.push(x + y);
		}
		else if(str == "-") {
			double x = num.top(); num.pop();
			double y = num.top(); num.pop();
			num.push(y - x);
		}
		else if(str == "*") {
			double x = num.top(); num.pop();
			double y = num.top(); num.pop();
			num.push(x * y);
		}
		else if(str == "/") {
			double x = num.top(); num.pop();
			double y = num.top(); num.pop();
			num.push(y / x);
		}
		else if(str == "^") {
			double x = num.top(); num.pop();
			double y = num.top(); num.pop();
			num.push(pow(y, x));
		}
		else if(str == "=") {
			double res = num.top(); num.pop();
			printf("%e\n", res);
			mem.pop(); mem.push(res);
		}
		else
			num.push(atof(str.c_str()));
	}
	printf("\n");
	for(int i = 1; i <= n; i++) {
		printf("%e%c", mem.top(), " \n"[i % 10 == 0]);
		mem.pop();
	}
	return 0;
}

