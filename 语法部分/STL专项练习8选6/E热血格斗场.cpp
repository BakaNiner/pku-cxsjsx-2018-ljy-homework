#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int n;
set<int> s;
map<int, int> m;

int main() {
	scanf("%d", &n);
	s.insert(1000000000);
	m[1000000000] = 1;
	for(int i = 1; i <= n; i++) {
		int id, x; scanf("%d%d", &id, &x);
		s.insert(x);
		m[x] = id;

		set<int>::iterator it = s.find(x);
		set<int>::iterator y1 = it, y2 = it;
		y1--; y2++;

		if(it == s.begin())
			it = y2;
		else if(*y2 - x >= x - *y1)
			it = y1;
		else
			it = y2;
		printf("%d %d\n", id, m[*it]);
	}
	return 0;
}

