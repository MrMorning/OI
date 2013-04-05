#include <cstdio>
#include <cstdlib>

int n, c, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &c, &seed);
	srand(seed);
	printf("%d %d\n", n, c);
	for ( int i = 0; i < n; i ++ )
		printf("%d\n", rand() % 10 + 1);
}
