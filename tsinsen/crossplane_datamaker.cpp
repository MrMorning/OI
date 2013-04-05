#include <cstdio>
#include <cstdlib>
int n, m, seed;
int id[1111][1111];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n * m, (n-1)*m+n*(m-1));
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j< m; j ++ ) {
			printf("%d %d\n", i, j);
			id[i][j] = i*m+j+1;
		}
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m-1; j ++ ) {
			int v = rand() % 100;
			printf("%d %d %d %d\n", id[i][j], id[i][j+1], v, v);
		}
	for ( int i = 0; i < n-1; i ++ )
		for ( int j = 0; j < m; j ++ ) {
			int v = rand() % 100;
			printf("%d %d %d %d\n", id[i+1][j], id[i][j], v, v);
		}
}
