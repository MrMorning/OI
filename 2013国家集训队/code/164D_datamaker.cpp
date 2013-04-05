#include <cstdio>
#include <cstdlib>
const int kRange = 30000;
int n, k, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &k, &seed);
	srand(seed);
	printf("%d %d\n", n, k);
	for ( int i = 0; i < n; i ++ )
		printf("%d %d\n", rand()%kRange, rand()%kRange);
}
