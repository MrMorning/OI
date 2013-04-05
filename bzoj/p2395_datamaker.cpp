#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 1; i < n; i ++ )
		printf("%d %d %d %d\n", rand() % i, i, rand() % 256, rand() % 256);
	m -= n - 1;
	while ( m -- ) {
		int a = rand() % n, b = rand() % n;
		while ( a == b )
			a = rand() % n;
		printf("%d %d %d %d\n", a, b, rand() % 256, rand() % 256);
	}
}
