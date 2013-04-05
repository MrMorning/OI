#include <cstdio>
#include <cstdlib>
int n, k, p, r, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d%d", &n, &k, &p, &r, &seed);
	srand(seed);
	printf("%d %d %d\n", n, k, p);
	for ( int i = 0; i < k; i ++ )
		printf("%d ", rand() % r + 1);
	printf("\n");
	for ( int i = 0; i < n; i ++ )
		printf("%d %d\n", rand() % r + 1, rand() % k + 1);
}
