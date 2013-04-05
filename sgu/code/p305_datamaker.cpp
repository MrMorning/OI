#include <cstdio>
#include <cstdlib>
#define RANGE 10
int n, m, seed;
int randVal() {
	return rand() % RANGE - rand() % RANGE;
}
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ )
		printf("%d %d\n", randVal(), randVal());
}
