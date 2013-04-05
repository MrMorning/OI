#include <cstdio>
#include <cstdlib>
const int LIM = 10;
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	while ( n -- ) {
		int t = rand() % 4;
		if ( t == 0 ) 
			printf("INS %d\n", rand() % LIM);
		else if ( t == 1 )
			printf("DEL %d\n", rand() % LIM);
		else if ( t == 0 )
			printf("ADD %d\n", rand() % 10 + 1);
		else 
			printf("QBIT %d\n", rand() % 16);
	}
}
