#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	printf("%d\n", n);
	srand(seed);
	printf("%d", rand() % 9 + 1);
	for ( int i = 0; i < n - 1; i ++ )
		printf("%d", rand() % 10);
	puts("");
	printf("%d", rand() % 9 + 1);
	for ( int i = 0; i < n - 1; i ++ )
		printf("%d", rand() % 10);
	puts("");
}
