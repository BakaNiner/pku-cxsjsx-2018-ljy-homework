#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

char str[10];
multiset<int> s;
map<int, bool> m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", str);
		if(str[1] == 'd') {
			int x; scanf("%d", &x);
			m[x] = 1;
			s.insert(x);
			printf("%d\n", s.count(x));
		}
		else if(str[1] == 'e') {
			int x; scanf("%d", &x);
			printf("%d\n", s.count(x));
			s.erase(x);
		}
		else if(str[1] == 's') {
			int x; scanf("%d", &x);
			printf("%d %d\n", m[x], s.count(x));
		}
	}
	return 0;
}

