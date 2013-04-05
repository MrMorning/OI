#include <cstdio>
#include <cstdlib>
int TST, n, A, B, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d%d", &TST, &n, &A, &B, &seed);
	srand(seed);
	printf("%d\n", TST);
	while ( TST -- ) {
		printf("%d\n", n);
		for ( int i = 0; i < n; i ++ )
			printf("%d ", rand());
		printf("\n");
		printf("%d %d\n", A, B);
	}
}
