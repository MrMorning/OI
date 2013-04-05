#include <cstdio>
#include <cstdlib>
#define R 100
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ )
		printf("%d %d\n", rand() % R + 1, rand() % R + 1);
}
