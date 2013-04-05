#include <cstdio>
#include <cstdlib>
int T, N, X, Y, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d%d", &T, &N, &X, &Y, &seed);
	srand(seed);
	printf("%d\n", T);
	while ( T -- ) {
		printf("%d %d %d\n", N, X, Y);
		for ( int i = 0; i < N; i ++ )
			printf("%d %d\n", rand() % 1000 + 1, rand() % 1000 + 1);
	}
}
