#include <cstdio>
#include <cstdlib>
int T, n1, n2, K, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d%d", &T, &n1, &n2, &K, &seed);
	srand(seed);
	while ( T -- ) {
		printf("%d\n", K);
		for ( int i = 0; i < n1; i ++ )
			printf("%c", rand() % 26 + 'A');
		puts("");
		for ( int i = 0; i < n2; i ++ )
			printf("%c", rand() % 26 + 'A');
		printf("\n");
	}
	printf("0\n");
}
