#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++, puts("") )
		for ( int j = 0; j < m; j ++ )
			printf("%d", rand()%5);
	int x1 = rand()%m+1, y1 = rand()%n+1;
	int x2 = rand()%m+1, y2 = rand()%n+1;
	while ( x1==x2 && y1==y2 )
		x2 = rand()%m+1, y2 = rand()%n+1;
	printf("%d %d\n%d %d\n", x1, y1, x2, y2);
}
