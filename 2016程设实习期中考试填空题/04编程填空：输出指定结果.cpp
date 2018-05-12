#include <iostream>
using namespace std;

class A {
public:
	int n;

	A(int x) : n(x) {}
	A(const A &x) : n(x.n) {}

	friend ostream& operator << (ostream &os, const A &x) {
		os << x.n;
		return os;
	}

	A& operator += (const A &x) {
		this->n += x.n;
		return *this;
	}

	A& operator -= (const A &x) {
		this->n -= x.n;
		return *this;
	}

	int& getValue() {
		return n;
	}
};

int main() {
	int t;
	cin >> t;
	while(t-- ) {
		int m,n,k;
		cin >> m >> n >> k;	
	    A a(m);
	    A b = a;
	    cout << b << endl;
	    cout << (a += b -= n) << endl;
	    cout << a.getValue() << endl;
	    a.getValue() = k;
	    cout << a << endl;
	} 
	return 0;
}
