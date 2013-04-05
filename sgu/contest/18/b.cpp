#include <cstdio>
int hit[11], score[11], n, m;
int main() {
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		hit[i] = 100, score[i] = 0;
	while ( m -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		if ( hit[a] > 0 ) {
			if ( hit[b] > 0 )
				score[a] += 3;
			hit[b] -= 8;
		}
	}
	for ( int i = 1; i <= n; i ++ )
		if ( hit[i] > 0 )
			score[i] += hit[i] / 2;
	for ( int i = 1; i <= n; i ++ )
		printf("%d %d\n", hit[i], score[i]);
}
