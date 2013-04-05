#include <cstdio>

int main() {
	freopen("t.in", "w", stdout);
	printf("100000 1000000000\n");
	for ( int i = 1; i <= 100000; i ++ )
		printf("%d ", 999900000 + i);
}
