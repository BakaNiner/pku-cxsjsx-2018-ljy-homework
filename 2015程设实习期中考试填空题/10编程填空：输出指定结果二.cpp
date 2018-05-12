#include <iostream>
#include <map>
using namespace std;

struct A {
	static int count;

	A(int x = 0) {
		count++;
	}

	virtual ~A() {
		count--;
		cout << "A::destructor" << endl;
	}
};

struct B : public A {
	B(int x = 0) {}

	B(const B &x) {}

	~B() {
		cout << "B::destructor" << endl;
	}
};

int A::count = 0;
void func(B b) {  }
int main()
{
	A a1(5),a2;
	cout << A::count << endl;
	B b1(4);
	cout << A::count << endl;
	func(b1);
	cout << A::count << endl;
	A * pa = new B(4);
	cout << A::count << endl;
	delete pa;
	cout << A::count << endl;
	return 0;
}
