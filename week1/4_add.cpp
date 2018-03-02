#include <cstdio>

int main(int argc, char *argv[]) {
	int a, b;
	sscanf(argv[1], "%d", &a);
	sscanf(argv[2], "%d", &b);
	printf("%d\n", a + b);
	return 0;
}

