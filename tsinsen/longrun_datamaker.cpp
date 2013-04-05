#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);

	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand()%10+1);
	puts("");
	for ( int i = 0; i < m; i++ ) {
		int p = rand() % 3;
		if ( p == 0 )
			printf("1 %d %d\n", rand()%n+1,rand()%n+1);
		else if ( p == 1 )
			printf("2 %d %d\n", rand()%n+1, rand()%10+1);
		else
			printf("3 %d %d\n", rand()%n+1, rand()%n+1);
	}
}
