#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 1; i <= n; i ++ ) {
		printf("%d %d %d %d\n", i, rand() % 10 - rand() % 10, rand() % 10 - rand() % 10, rand() % 10 - rand() % 10);
	}
}
