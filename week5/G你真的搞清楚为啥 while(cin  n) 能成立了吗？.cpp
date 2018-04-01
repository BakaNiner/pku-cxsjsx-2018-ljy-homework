#include <iostream>
using namespace std;
class MyCin {
public:
	bool flag;

	MyCin() : flag(1) {}

	MyCin& operator >> (int &x) {
		cin >> x;
		if(x == -1)
			flag = 0;
		return *this;
	}

	operator bool () {
		return flag;
	}
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}
