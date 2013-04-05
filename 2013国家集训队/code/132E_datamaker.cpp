#include <cstdio>
#include <cstdlib>
int n, m, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % 40 + 1);
}
