#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
public:
	int **p;

	Array2() : p(NULL) {}
	Array2(int n, int m) {
		p = new int*[n];
		for(int i = 0; i < n; i++)
			p[i] = new int[m];
	}

	int* operator [] (int x) {
		return p[x];
	}

	int operator () (int x, int y) {
		return p[x][y];
	}
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
