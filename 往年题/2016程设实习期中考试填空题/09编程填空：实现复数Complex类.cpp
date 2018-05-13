#include <iostream>
using namespace std;

struct Complex {
	int a, b;

	Complex(int _a = 0, int _b = 0) : a(_a), b(_b) {}

	Complex(const char *s) {
		a = s[0] - '0';
		b = s[2] - '0';
	}

	Complex(const Complex &c) : a(c.a), b(c.b) {}

	friend ostream& operator << (ostream &os, const Complex &x) {
		if(x.a == 0 && x.b == 0)
			os << 0;
		else if(x.a == 0 && x.b != 0)
			os << x.b << "i";
		else if(x.a != 0 && x.b == 0)
			os << x.a;
		else
			os << x.a << "+" << x.b << "i";
		return os;
	}

	Complex operator + (const Complex &x) const {
		return Complex(a + x.a, b + x.b);
	}

	Complex operator - (const Complex &x) const {
		return Complex(a - x.a, b - x.b);
	}

	Complex operator * (const Complex &x) const {
		return Complex(a * x.a - b * x.b, a * x.b + b * x.a);
	}

	Complex& operator += (const Complex &x) {
		return *this = *this + x;
	}

	Complex& operator -= (const Complex &x) {
		return *this = *this - x;
	}

	Complex& operator *= (const Complex &x) {
		return *this = *this * x;
	}
};

int main() {
	Complex c1;
	Complex c2("3+2i");
	Complex c3(c2);
	Complex c4(-15);
	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;
	cout << c2 + c4 << endl;
	cout << c2 - c3 << endl;
	cout << c2 * c3 << endl;
	c2 += c4;
	cout << c2 << endl;
	c2 -= -12;
	cout << c2 << endl;
	c3 *= c3;
	cout << c3 << endl;
	return 0;
}
