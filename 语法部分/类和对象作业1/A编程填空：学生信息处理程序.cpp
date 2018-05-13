#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
	char str[100];
	int age, id;
	double grade;
public:
	void input() {
		int len = 0;
		for(char ch = getchar(); ch != ','; ch = getchar())
			str[len++] = ch;
		str[len] = 0;
		int a, b, c, d;
		scanf("%d,%d,%d,%d,%d,%d", &age, &id, &a, &b, &c, &d);
		grade = a + b + c + d;
	}

	void calculate() {
		grade /= 4;
	}

	void output() {
		cout << str << "," << age << "," << id << "," << grade << endl;
	}
};

int main() {
	Student student;
	student.input();
	student.calculate();
	student.output();
}
