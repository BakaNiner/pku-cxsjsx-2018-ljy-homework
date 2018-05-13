#include <iostream>
#include <set>
using namespace std;

struct Rectangle {
	int a, b;

	Rectangle(int _a, int _b) : a(_a), b(_b) {}

	bool operator < (const Rectangle &x) const {
		return a * b == x.a * x.b ? a + b > x.a + x.b : a * b > x.a * x.b;
	}

	friend ostream& operator << (ostream &os, const Rectangle &x) {
		os << x.a * x.b << " " << (x.a + x.b) * 2;
		return os;
	}
};

struct Comp {
	bool operator () (const Rectangle &x, const Rectangle &y) {
		return x.a + x.b == y.a + y.b ? x.a * x.b < y.a * y.b : x.a + x.b < y.a + y.b;
	}
};

int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
	return 0;
}
