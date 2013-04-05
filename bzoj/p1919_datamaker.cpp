#include <cstdio>
#include <cstdlib>
int n, C, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &C, &seed);
	srand(seed);
	printf("%d %d\n", n, C);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % (n + 1));
	puts("");
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % (n + 1));
	puts("");
}
