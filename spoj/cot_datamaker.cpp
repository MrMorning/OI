#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 1; i <= n; i ++ )
		printf("%d ", rand());
	printf("\n");
	for ( int i = 1; i < n ; i ++ ) {
		printf("%d %d\n", i + 1, rand() % i + 1);
	}
	while ( m -- ) {
		int a = rand() % n + 1, b = rand() % n + 1;
		printf("%d %d %d\n", a, b, rand() % (a == b ? 1 : 2) + 1);
	}
}
