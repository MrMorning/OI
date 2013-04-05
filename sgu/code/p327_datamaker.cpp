#include <cstdio>
#include <cstdlib>
int n, l, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &l, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ ) {
		int k = rand() % l + 1;
		while ( k -- )
			printf("%c", 'A' + rand() % 3);
		puts("");
	}
}
