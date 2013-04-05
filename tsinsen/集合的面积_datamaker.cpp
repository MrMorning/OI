#include <cstdio>
#include <cstdlib>
#define RANGE 100000000
int r, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &r, &seed);
	srand(seed);
	int n = r, m = r;//rand() % r + 1, m = rand() % r + 1;
	printf("%d %d\n", n, m);
	while ( n -- )
		printf("%d %d ", rand() % RANGE - rand() % RANGE, rand() % RANGE - rand() % RANGE);
	puts("");
	while ( m -- )
		printf("%d %d ", rand() % RANGE - rand() % RANGE, rand() % RANGE - rand() % RANGE);
}
