#include <cstdio>
#include <cstdlib>

int n, seed;

int randVal() {
	return rand() % 65536;
}

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", randVal());
	puts("");
	for ( int i = 1; i < n; i ++ )
		printf("%d %d\n", i + 1, i);
}
