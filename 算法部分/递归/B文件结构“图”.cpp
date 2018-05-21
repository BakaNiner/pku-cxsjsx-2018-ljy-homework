#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 105;

int clo;
string tmp;

void dfs(int depth) {
	if(depth == 0)
		cout << "DATA SET " << ++clo << ":" << endl << "ROOT" << endl;
	
	vector<string> file;
	while(1) {
		if(tmp[0] == ']') {
			cin >> tmp;
			break;
		}
		else if(tmp[0] == '*')
			break;
		else if(tmp[0] == 'f') {
			file.push_back(tmp);
			cin >> tmp;
		}
		else if(tmp[0] == 'd') {
			for(int i = 0; i <= depth; i++)
				cout << "|     ";
			cout << tmp << endl;
			cin >> tmp;
			dfs(depth + 1);
		}
	}
	sort(file.begin(), file.end());
	for(string &x : file) {
		for(int i = 0; i < depth; i++)
			cout << "|     ";
		cout << x << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	while(1) {
		cin >> tmp;
		if(tmp[0] == '#')
			break;
		dfs(0);
		cout << endl;
	}
	return 0;
}

