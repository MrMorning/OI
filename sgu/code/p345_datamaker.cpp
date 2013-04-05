#include <cstdio>
#include <cstdlib>
const int kRange = 10;
int n, m, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ )
		printf("%d %d\n", rand()%kRange, rand()%kRange);
	printf("%d\n", m);
	for ( int i = 0; i < m; i ++ ){
		printf("%d %d %d %d\n", rand()%kRange, rand()%kRange, rand()%kRange, rand()%kRange);
	}
}
