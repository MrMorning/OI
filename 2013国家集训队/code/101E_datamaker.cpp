#include <cstdlib>
#include <cstdio>
int seed;
int n, m, p;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &p, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, p);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % p);
	puts("");
	for ( int i = 0; i < m; i ++ )
		printf("%d ", rand() % p);
}
