#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 1; i < n; i ++ )
		printf("%d %d %s", i + 1, rand() % i + 1, rand() & 1 ? "almost protected\n": "protected\n");
}
