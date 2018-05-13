#include <iostream>
using namespace std;

int sum(int *a, int n, int (*f)(int)) {
	int res = 0;
	for(int i = 0; i < n; i++)
		res += f(a[i]);
	return res;
}

int sqr(int n) {
    return n * n;
}
int main() {
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << sum(a, n, sqr) << endl;
    }
    return 0;
}
