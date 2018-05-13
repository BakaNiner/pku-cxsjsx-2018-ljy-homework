#include <iostream>
using namespace std;

template<class T1, class T2>
struct f {
	T1 a;

	f(const T1 &x) : a(x) {}

	T2 operator () (const T2 &b) {
		return b + a;
	}
};

int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}
