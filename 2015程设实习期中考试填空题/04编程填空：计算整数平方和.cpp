#include <iostream>
using namespace std;

struct CType {
	int n;

	void setvalue(int _n) {
		n = _n;
	}

	int operator ++ (int) {
		int tmp = n;
		n *= n;
		return tmp;
	}

	friend ostream& operator << (ostream &os, const CType &x) {
		os << x.n;
		return os;
	}
};

int main(int argc, char* argv[]) {
	CType obj;
	int   n;		
	cin>>n;
	while ( n ) {
		obj.setvalue(n);
		cout<<obj++<<" "<<obj<<endl;
		cin>>n;
	}
	return 0;
}
