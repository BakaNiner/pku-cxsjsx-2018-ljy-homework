#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
public:
	int num[1000], len;

	CHugeInt(const char *s) {
		memset(num, 0, sizeof(num));
		len = strlen(s);
		for(int i = len - 1; ~i; i--)
			num[len - i - 1] = s[i] - '0';
	}
	CHugeInt(int x) {
		memset(num, 0, sizeof(num));
		len = x == 0;
		for(; x; x /= 10)
			num[len++] = x % 10;
	}

	CHugeInt operator + (const CHugeInt &x) const {
		CHugeInt res(0);
		res.len = (len > x.len ? len : x.len) + 1;
		for(int i = 0; i < res.len; i++) {
			res.num[i] += num[i] + x.num[i];
			res.num[i + 1] += res.num[i] / 10;
			res.num[i] %= 10;
		}
		for(; res.len > 1 && res.num[res.len - 1] == 0; res.len--);
		return res;
	}

	friend CHugeInt operator + (const int x, const CHugeInt &y) {
		return CHugeInt(x) + y;
	}

	CHugeInt operator + (int x) const {
		return *this + CHugeInt(x);
	}

	CHugeInt& operator += (int x) {
		return *this = *this + CHugeInt(x);
	}

	CHugeInt& operator ++ () {
		return *this += 1;
	}

	CHugeInt operator ++ (int) {
		CHugeInt tmp = *this;
		*this += 1;
		return tmp;
	}

	friend ostream& operator << (ostream &os, const CHugeInt &x) {
		for(int i = x.len - 1; ~i; i--)
			os << x.num[i];
		return os;
	}
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}
