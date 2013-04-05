#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 1; i <= n; i ++ )
		printf("%d\n", rand()%n+1);
}

