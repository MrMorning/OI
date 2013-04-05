#include <cstdio>
#include <cstdlib>
int M, N, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &M, &N, &seed);
	srand(seed);
	printf("%d %d\n", M, N);
	for ( int i = 1; i <= N; i ++ )
		printf("%d %d\n", rand() % 10 + 1, rand() % 4 + 1);
}
