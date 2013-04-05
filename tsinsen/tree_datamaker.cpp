#include <cstdio>
#include <cstdlib>
int n, m, need, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &need, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, need);
	for ( int i = 1; i < n; i ++ ) 
		printf("%d %d %d %d\n", rand() % i, i, rand() % 100 + 1, rand() % 2);
	for ( int i = 0; i < m - (n - 1); i ++ )
		printf("%d %d %d %d\n", rand() % n, rand() % n, rand() % 100 + 1, rand() % 2);
}
