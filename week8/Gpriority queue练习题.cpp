#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 10000001;

int prime[maxn], cnt;
bool isnprime[maxn];

priority_queue<pii> q, q1;

void getprime() {
	isnprime[1] = 1;
	for(int i = 2; i < maxn; i++) {
		if(!isnprime[i]) prime[++cnt] = i;
		for(int j = 1; j <= cnt && i * prime[j] < maxn; j++) {
			isnprime[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
}

int getfactor(int n) {
	int res = 0;
	for(int i = 1; prime[i] < n; i++)
		if(n % prime[i] == 0) res++;
	return res;
}

int main() {
	getprime();
	int T; scanf("%d", &T);
	while(T--) {
		for(int i = 1; i <= 10; i++) {
			int x; scanf("%d", &x);
			q.push(pii(getfactor(x), x));
		}
		printf("%d ", q.top().second); q.pop();
		while(q.size() != 1) {
			q1.push(q.top()); q.pop();
		}
		printf("%d\n", q.top().second); q.pop();
		while(!q1.empty()) {
			q.push(q1.top()); q1.pop();
		}
	}
	return 0;
}

