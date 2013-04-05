#include <cstdio>
#include <cstdlib>
int n, m, seed, k;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, k);
	for ( int k = 0; k < 10; k ++ )
		for ( int i = 0; i < 100; i ++ )
			for ( int j = 0; j < 100; j ++ )
				printf("%d %d\n", i+1, j+1);
}
