#include <cstdio>
#include <cstdlib>
int T, N, M, R, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d%d", &T, &N, &M, &R, &seed);
	srand(seed);
	printf("%d\n", T);
	while ( T -- ) {
		printf("%d %d %d\n", N, M, rand() % R + 1);
		for ( int i = 0; i < N - 1; i ++ )
			printf("%d ", rand() % 2);
		printf("\n");
	}
}
