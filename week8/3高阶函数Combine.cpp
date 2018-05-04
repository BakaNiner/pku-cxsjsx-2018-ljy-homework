#include <iostream>
using namespace std;

template<class T1, class T2, class T3>
struct combine {
	T1 f;
	T2 g;

	combine(const T1 &x, const T2 &y) : f(x), g(y) {}

	T3 operator () (T3 x) {
		return f(f(x) + g(x));
	}
};

int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}
