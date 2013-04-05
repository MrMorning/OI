#include <cstdio>
#include <cstdlib>
int n, L, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &L, &seed);
	srand(seed);
	printf("%d %d\n", n, L);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % L + 1);
	puts("");
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % L + 1);
	puts("");
}
