#include <cstdio>
#include <cstdlib>
#define R 10
int N, A, B, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &N, &A, &B, &seed);
	srand(seed);
	printf("%d %d %d\n", N, A, B);
	while ( N -- )
		printf("%d %d %d\n", rand() % R + 1, rand() % R + 1, rand() % R + 1);
}
