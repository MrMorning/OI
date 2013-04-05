#include <cstdio>
#include <cstdlib>
int T, n, m, c, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d%d", &T, &n, &m, &c, &seed);
	srand(seed);
	while ( T -- ) {
		printf("%d %d %d\n", n, m, c);
		for ( int rep = 0; rep < c; rep ++ ) {
			int x = 0, y = rand() % m;
			int a = n,
				b = rand() % (m - y) + 1;
			printf("%d %d %d %d %d\n", a, b, rand() % 10001, x, y);
		}
	}
}
