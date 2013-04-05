#include <cstdio>
#include <cstdlib>

int n, k;
int seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &k, &seed);
	srand(seed);
	printf("%d %d\n", n, k);
	int be = 1;
	while ( n -- ) {
		int delta = rand() % 10;
		printf("%d\n", be + delta);
		be += delta;
	}
}
