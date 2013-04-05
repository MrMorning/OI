#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, rand() % m + 1);
	for ( int i = 1; i < n; i ++ )
		printf("%d %d %d\n", i + 1, rand() % i + 1, rand() % 10);
	for ( int i = 0; i < m - n + 1; i ++ ) {
		int a = rand() % n + 1,
			b = rand() % n + 1;
		while ( a == b )
			a = rand() % n + 1;
		printf("%d %d %d\n", a, b, rand() % 10);
	}
}
