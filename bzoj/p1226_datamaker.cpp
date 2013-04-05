#include <cstdio>
#include <cstdlib>
int T, n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &T, &n, &seed);
	srand(seed);
	printf("%d\n", T);
	while ( T -- ) {
		printf("%d\n", n);
		for ( int i = 0; i < n; i ++ )
			printf("%d %d\n", rand() % 1000 + 1, rand() % 8);
	}
}
