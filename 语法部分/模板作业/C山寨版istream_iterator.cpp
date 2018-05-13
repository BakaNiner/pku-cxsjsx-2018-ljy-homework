#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator {
public:
	T a;
	istream &is;

	CMyistream_iterator(istream &s) : is(s) {
		is >> a;
	}

	T operator * () const {
		return a;
	}

	void operator ++ (int) {
		is >> a;
	}
};
int main()  
{ 
	int t;
	cin >> t;
	while( t -- ) {
		 CMyistream_iterator<int> inputInt(cin);
		 int n1,n2,n3;
		 n1 = * inputInt; //∂¡»Î n1
		 int tmp = * inputInt;
		 cout << tmp << endl;
		 inputInt ++;   
		 n2 = * inputInt; //∂¡»Î n2
		 inputInt ++;
		 n3 = * inputInt; //∂¡»Î n3
		 cout << n1 << " " << n2<< " " << n3 << " ";
		 CMyistream_iterator<string> inputStr(cin);
		 string s1,s2;
		 s1 = * inputStr;
		 inputStr ++;
		 s2 = * inputStr;
		 cout << s1 << " " << s2 << endl;
	}
	 return 0;  
}
