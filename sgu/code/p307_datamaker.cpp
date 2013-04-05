#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 1; i < n; i ++, puts("") )
		for ( int j = 1; j < m; j ++ )
			printf("%d", rand() % 3);
}
