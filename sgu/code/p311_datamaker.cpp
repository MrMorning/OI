#include <cstdio>
#include <cstdlib>
#define R 1000000
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	while ( n -- ) {
		int t = rand() % 2;
		if ( t == 0 )
			printf("ARRIVE %d %d\n", rand() % R + 1,rand() % R + 1);
		else
			printf("BUY %d %d\n", rand() % R + 1, rand() % R + 1);
	}
}
