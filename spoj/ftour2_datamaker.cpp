#include <cstdio>
#include <cstdlib>
int n, k, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &k, &m, &seed);
	printf("%d %d %d\n", n, k, m);
	srand(seed);
	for ( int i = 0; i < m; i ++ ) 
		printf("%d\n", rand() % n + 1);
	for ( int i = 1; i < n; i ++ )
		printf("%d %d %d\n", i + 1, rand() % i + 1, rand() % 2000 - 1000);
}
