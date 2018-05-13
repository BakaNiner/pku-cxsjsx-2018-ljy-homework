#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
class MyQueue
{
public:
	int k;
	priority_queue<int, vector<int>, less<int> > q;

	MyQueue(int _k) : k(_k) {}

	friend istream& operator >> (istream &is, MyQueue &t) {
		int x;
		is >> x;
		t.q.push(x);
		return is;
	}

	friend ostream& operator << (ostream &os, MyQueue &t) {
		int cnt = 0;
		for(; cnt != t.k; t.q.pop())
			if(t.q.top() % 2 == 0) {
				os << t.q.top() << " ";
				cnt++;
			}
		return os;
	}
};
int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		MyQueue q(k);
		for (int i = 0; i < n; ++i)
			cin >> q;
		cout<<q;
		cout << endl;
	}
	return 0; 
}
