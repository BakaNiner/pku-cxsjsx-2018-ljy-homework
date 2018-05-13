#include <iostream>
#include <string>
using namespace std;
string dec2bin(int x){
	string res;
	for(; x != 0; x /= 2)
		res.push_back(x & 1 ? '1' : '0');
	for(; res.size() != 31; res.push_back('0'));
	string res2;
	for(int i = res.size() - 1; ~i; i--)
		res2.push_back(res[i]);
	return res2;
}
int main(){
	int n;
	cin >> n;
	while(n--) {
		int x;
		cin >> x;
		cout << dec2bin(x) << endl;
	}
	return 0;
}
