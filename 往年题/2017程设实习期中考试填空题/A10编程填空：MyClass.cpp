#include <iostream>
using namespace std;
class CMyClassA {
	int val;
public:
	CMyClassA(int);
	void virtual print();
};
CMyClassA::CMyClassA(int arg) {
	val = arg;
	printf("A:%d\n", val);
}
void CMyClassA::print() {
	printf("%d\n", val);
	return;
}
class CMyClassB : public CMyClassA {
public:
	int val2;

	CMyClassB(int x) : CMyClassA(x * 3), val2(x) {
		printf("B:%d\n", val2);
	}

	void virtual print() {
		printf("%d\n", val2);
	}
};
int main(int argc, char** argv) {
	CMyClassA a(3), *ptr;
	CMyClassB b(5);
	ptr = &a; ptr->print();
	a = b;
	a.print();
	ptr = &b; ptr->print();
	return 0;
}
