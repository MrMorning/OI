#include <cstdio>
#include <cstdlib>
int n, m, k, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, k);
	for ( int i = 0; i < n; i ++, puts("") )
		for ( int j = 0; j < m; j ++ ) 
			printf("%d", rand() % 10);
}
