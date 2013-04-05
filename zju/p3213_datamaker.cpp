#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("1\n%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ ,puts("") )
		for ( int j = 0; j < m; j ++ )
			printf("%d ", rand() % 10);

}
