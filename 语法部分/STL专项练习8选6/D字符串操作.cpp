#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stack>

using namespace std;

const int maxn = 25, maxm = 10005;

int n;
string s[maxn];
string buf;
string opt[maxm];
stack<string> sta;

int mystoi(string str) {
	istringstream in(str);
	int x; in >> x;
	return x;
}

string myitos(int x) {
	ostringstream out;
	out << x;
	return out.str();
}

string copy(int N, int X, int L) {
	return s[N].substr(X, L);
}

string add(string S1, string S2) {
	if(S1.size() > 5 || S2.size() > 5)
		return S1 + S2;
	for(int i = 0; i < 5 && i < S1.size(); i++)
		if(S1[i] < '0' || S1[i] > '9')
			return S1 + S2;
	for(int i = 0; i < 5 && i < S2.size(); i++)
		if(S2[i] < '0' || S2[i] > '9')
			return S1 + S2;
	return myitos(mystoi(S1) + mystoi(S2));
}

string find(string S, int N) {
	int res = s[N].find(S);
	return res == string::npos ? myitos(S.size()) : myitos(res);
}

string rfind(string S, int N) {
	int res = s[N].rfind(S);
	return res == string::npos ? myitos(S.size()) : myitos(res);
}

void insert(string S, int N, int X) {
	s[N].insert(X, S);
}

void reset(string S, int N) {
	s[N] = S;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> s[i];

	while(getline(cin, buf)) {
		istringstream in(buf);
		int len = 0;
		while(in >> opt[len++]); len--;

		for(int i = len - 1; ~i; i--) {
			if(opt[i] == "copy") {
				string N = sta.top(); sta.pop();
				string X = sta.top(); sta.pop();
				string L = sta.top(); sta.pop();
				sta.push(copy(mystoi(N), mystoi(X), mystoi(L)));
			}
			else if(opt[i] == "add") {
				string S1 = sta.top(); sta.pop();
				string S2 = sta.top(); sta.pop();
				sta.push(add(S1, S2));
			}
			else if(opt[i] == "find") {
				string S = sta.top(); sta.pop();
				string N = sta.top(); sta.pop();
				sta.push(find(S, mystoi(N)));
			}
			else if(opt[i] == "rfind") {
				string S = sta.top(); sta.pop();
				string N = sta.top(); sta.pop();
				sta.push(rfind(S, mystoi(N)));
			}
			else if(opt[i] == "insert") {
				string S = sta.top(); sta.pop();
				string N = sta.top(); sta.pop();
				string X = sta.top(); sta.pop();
				insert(S, mystoi(N), mystoi(X));
			}
			else if(opt[i] == "reset") {
				string S = sta.top(); sta.pop();
				string N = sta.top(); sta.pop();
				reset(S, mystoi(N));
			}
			else if(opt[i] == "print") {
				string N = sta.top(); sta.pop();
				cout << s[mystoi(N)] << endl;
			}
			else if(opt[i] == "printall") {
				for(int i = 1; i <= n; i++)
					cout << s[i] << endl;
			}
			else if(opt[i] == "over") {
				break;
			}
			else {
				sta.push(opt[i]);
			}
		}
	}
	return 0;
}

