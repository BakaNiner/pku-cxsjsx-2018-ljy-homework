#include <iostream>

using namespace std;

template <class T> 
struct MySharedPtr {
	T *a;
	int *cnt;
	
	MySharedPtr() : a(NULL), cnt(NULL) {}

	MySharedPtr(T *x) : a(x) {
		cnt = new int(1);
	}

	MySharedPtr(const MySharedPtr &x) : a(x.a), cnt(x.cnt) {
		(*cnt)++;
	}

	~MySharedPtr() {
		(*cnt)--;
		if((*cnt) == 0) {
			delete a;
			delete cnt;
		}
	}

	T* operator -> () {
		return a;
	}

	T& operator * () {
		return *a;
	}

	operator bool () {
		return a != NULL;
	}

	T* get() {
		return a;
	}

	void reset(T *x = NULL) {
		if(x == NULL) {
			if(a != NULL)
				if(--(*cnt) == 0) {
					delete a;
					delete cnt;
				}
		} else
			cnt = new int(1);
		a = x;
	}
};

struct A   {    
 	 int n;
	 A(int v = 0):n(v){ } 
	 ~A() { cout << n << " destructor" << endl; }
};
int main()
{
	MySharedPtr<A> sp1(new A(2)); 
	MySharedPtr<A> sp2(sp1);        
	cout << "1)" << sp1->n  << "," << sp2->n << endl; 
	MySharedPtr<A> sp3;
	A * p = sp1.get();  
	cout << "2)" << p->n << endl;
	sp3 = sp1; 
	cout << "3)" << (*sp3).n << endl;  
	sp1.reset();     
	if( !sp1 )
		cout << "4)sp1 is null" << endl; //会输出 
	A * q = new A(3);
	sp1.reset(q); // 
	cout << "5)" << sp1->n << endl;
	MySharedPtr<A> sp4(sp1); 
	MySharedPtr<A> sp5;
	sp5.reset(new A(8));
	sp1.reset();          
	cout << "before end main" <<endl;
	sp4.reset();          
	cout << "end main" << endl;
	return 0; //程序结束，会delete 掉A(2)
}

