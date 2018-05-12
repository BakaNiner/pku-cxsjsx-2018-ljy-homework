#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

struct A {
	char type;
	int age;

	A(int x, char _t = 'A') : type(_t), age(x) {}
};

struct B : public A {
	B(int x) : A(x, 'B') {}
};

void Print(A *x) {
	cout << x->type << " " << x->age << endl;
}

struct Comp {
	bool operator () (const A *x, const A *y) {
		return x->age < y->age;
	}
};

int main()
{

	int t;
	cin >> t;
	set<A*,Comp> ct;
	while( t -- ) {
		int n;
		cin >> n;
		ct.clear();
		for( int i = 0;i < n; ++i)	{
			char c; int k;
			cin >> c >> k;
			
			if( c == 'A')
				ct.insert(new A(k));
			else
				ct.insert(new B(k));
		}	
		for_each(ct.begin(),ct.end(),Print);
		cout << "****" << endl;
	}
}
