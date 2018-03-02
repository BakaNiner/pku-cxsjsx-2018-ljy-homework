#include <iostream>
#include <bitset>
using namespace std;

int bitManipulation3(int n, int i) {
	return n ^ -1 >> 32 - i << 32 - i;
}

int main() {
	int t, n, i;
	cin >> t;
	while (t--) {
		cin >> n >> i;
		cout << bitset<32>(n) << endl;
		cout << bitset<32>(bitManipulation3(n, i)) << endl;
	}
	return 0;
}
