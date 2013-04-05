#include <cstdio>
#include <cstdlib>
#define RANGE 100000000
int seed, q;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &q, &seed);
	srand(seed);
	for ( int i = 0; i < 3; i ++ )
		printf("%d %d ", rand() % RANGE, rand() % RANGE);
	printf("\n%d\n", q);
	while ( q -- )
		printf("%d %d\n", rand() % RANGE, rand() % RANGE);

}
