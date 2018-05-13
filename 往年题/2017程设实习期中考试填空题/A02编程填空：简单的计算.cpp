#include <iostream>
using namespace std;
template <class T>
class Add{
public:
	T f;

	Add(T _f) : f(_f) {};

	T operator () (T x, T y) {
		return x + y - f;
	}
};

int main(){
	double f;
	int n;
	while( cin >> f >> n) {
		
		Add<double> a1(f);
		Add<int> a2(n);
		double x,y;
		int p,q;
		cin >> x >> y >> p >> q;
		cout << a1(x, y) << endl;
		cout << a2(p, q) << endl;
	}
	return 0;
}
