#include <cstdio>
#include <cstdlib>
int nCell, nCmd, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &nCell, &nCmd, &seed);
	srand(seed);
	printf("%d\n", nCmd);
	bool first = true;
	while ( nCmd -- ) {
		int t = rand() % 3;
		if ( t == 0 )
			printf("towers\n");
		else if ( first || t == 1 ) {
			printf("put %d %d\n", rand() % nCell + 1, 1);
			first = false;
		} else {
			printf("cubes %d\n", 1);
		}
	}
}
