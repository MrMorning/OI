#include <cstdio>
#include <cassert>
#include <cstdlib>
int n, seed, s;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &s, &seed);
	assert(n>=3);
	srand(seed);
	printf("%d %d\n", n, s);
	printf("3 4 5 ");
	for ( int i = 0; i < n-3; i ++ )
		printf("%d ", rand()%3+3);
}
