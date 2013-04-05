#include <cstdio>
#include <cstdlib>
#define RANGE 100001
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 1; i < n; i ++ )
		printf("%d %d %d\n", i + 1, rand() % i + 1, rand() % RANGE);
	m -= n - 1;
	while ( m -- ) {
		int u = rand() % n + 1,
			v = rand() % n + 1;
		while ( u == v )
			u = rand() % n + 1;
		printf("%d %d %d\n", u, v, rand() % RANGE);
	}
}
