#include <cstdio>
#include <cstdlib>
int T, n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &T, &n, &seed);
	srand(seed);
	printf("%d\n", T);
	for ( int rep = 0; rep < T; rep ++ ) {
		printf("%d\n", n);
		for ( int i = 1; i < n; i ++ )
			printf("%d %d\n", i + 1, rand() % i + 1);
		for ( int i = 1; i <= n; i ++ ) {
			int a = rand() % 101;
			printf("%d %d\n", a, rand() % (101 - a));
		}
	}
}
