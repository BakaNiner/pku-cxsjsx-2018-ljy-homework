#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>

using namespace std;

const int maxn = 10005;

char s[10];
list<int> l[maxn];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		if(s[0] == 'n') {
			int id; scanf("%d", &id);
		}
		else if(s[0] == 'a') {
			int id, x; scanf("%d%d", &id, &x);
			l[id].push_back(x);
		}
		else if(s[0] == 'o') {
			int id; scanf("%d", &id);
			l[id].sort();
			for(list<int>::iterator it = l[id].begin(); it != l[id].end(); it++)
				printf("%d ", *it);
			printf("\n");
		}
		else if(s[0] == 'm') {
			int id1, id2; scanf("%d%d", &id1, &id2);
			l[id1].merge(l[id2]);
		}
		else if(s[0] == 'u') {
			int id; scanf("%d", &id);
			l[id].sort();
			l[id].unique();
		}
	}
	return 0;
}

