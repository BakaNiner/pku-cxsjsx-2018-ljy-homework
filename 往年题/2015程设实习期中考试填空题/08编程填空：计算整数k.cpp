#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, i, j;
		scanf("%d%d%d", &n, &i, &j);

		int k = 0;
		k |= ((n >> i) & 1) << i;
		k |= (1 ^ ((n >> j) & 1)) << j;
		for(int x = i + 1; x < j; x++)
			k |= 1 << x;

		cout << setbase(16) << k << endl;
	}
	return 0;
}

