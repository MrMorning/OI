#include <cstdio>
#include <cstdlib>
int n, m, q, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &q, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ , puts(""))
		for ( int j = 0; j < m; j ++ )
			printf("%d ", rand() % 1000000000 + 1);
	printf("%d\n", q);
	while ( q -- ) {
		printf("%d %d %d %d\n", rand() % n + 1, rand() % m + 1, rand() % n + 1, rand() % m + 1);
	}
}
