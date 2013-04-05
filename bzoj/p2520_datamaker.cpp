#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	int pre = 0;
	while ( n -- ) {
		int delta = rand() % 10;
		printf("%d %d\n", pre + delta, rand() % 10);
		pre += delta;
	}
}
