#include <cstdio>

int main(int argc, char *argv[]) {
	int a, b;
	sscanf(argv[1], "%d", &a);
	sscanf(argv[argc - 1], "%d", &b);
	printf("%d\n", a + b);
	return 0;
}

