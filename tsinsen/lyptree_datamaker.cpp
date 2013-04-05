#include <cstdio>
#include <cstdlib>
int n, Q, seed;
int rv() {
	return rand() % 100000000+1;
}

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &Q, &seed);
	srand(seed);
	printf("%d %d\n", n, Q);
	printf("0 %d\n", rv());
	for ( int i = 1; i < n; i ++ )
		printf("%d %d\n", rand()%i+1, rv());
	while ( Q -- ) {
		int t = rand() % 3;
		if ( t == 0 ) {
			printf("V %d %d\n", rand()%n+1, rv());
		} else if ( t == 1 ) {
			printf("E %d\n", rand()%n+1);
		} else {
			printf("Q %d\n", rand()%n+1);
		}
	}
}
