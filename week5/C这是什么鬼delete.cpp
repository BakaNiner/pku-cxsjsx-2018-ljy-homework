#include <iostream> 
using namespace std;
class A 
{ 
public:
	A() { }
	~A() {
		cout << "destructor B" << endl << "destructor A" << endl;
	}
}; 
class B:public A { 
	public: 
	~B() { cout << "destructor B" << endl; } 
}; 
int main() 
{ 
	A * pa; 
	pa = new B; 
	delete pa; 
	return 0;
}
