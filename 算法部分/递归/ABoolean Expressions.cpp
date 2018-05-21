#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1005;

char str[maxn];

struct stack {
	int t, sta[maxn];

	stack() {
		t = 0;
	}

	bool empty() {
		return t == 0;
	}

	void push(int x) {
		sta[++t] = x;
	}

	int top() {
		return sta[t];
	}

	int pop() {
		return sta[t--];
	}
} num, opt;

int id(char ch) {
	if(ch == '(') return 0;
	if(ch == '|') return 1;
	if(ch == '&') return 2;
	if(ch == '!') return 3;
}

int pri(int id) {
	return id;
}

int calc(int x, int y, int op) {
	if(op == 1) return x | y;
	if(op == 2) return x & y;
}

void update() {
	if(opt.top() == 0) {
		opt.pop();
	}
	else if(opt.top() == 3) {
		int x = num.pop(); opt.pop();
		num.push(!x);
	} else {
		int x = num.pop();
		int y = num.pop();
		num.push(calc(y, x, opt.pop()));
	}
}

int main() {
	int T = 0;
	while(gets(str) != NULL) {
		printf("Expression %d: ", ++T);
		for(int i = 0; str[i] != 0; i++) {
			if(str[i] == ' ') continue;
			else if(str[i] == 'V')
				num.push(1);
			else if(str[i] == 'F')
				num.push(0);
			else if(str[i] == '(')
				opt.push(0);
			else if(str[i] == '&' || str[i] == '|' || str[i] == '!') {
				for(; !opt.empty() && pri(opt.top()) > pri(id(str[i])); update());
				opt.push(id(str[i]));
			}
			else if(str[i] == ')') {
				for(; !opt.empty() && opt.top() != 0; update());
				opt.pop();
			}
		}
		for(; !opt.empty(); update());
		printf(num.pop() ? "V\n" : "F\n");
	}
	return 0;
}

