#include <cstdio>
#include <cstdlib>
int n, m, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ )
		printf("%c ", rand() % 26 + 'a');
	printf("\n");
	printf("%d\n", m);
	for ( int i = 0; i < m; i ++ ) {
		int l = rand() % 100000 + 1;
		printf("%d\n", l);
		while ( l -- )
			printf("%c ", rand() % 26 + 'a');
		puts("");
	}
}
