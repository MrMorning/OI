#include <cstdio>
#include <cstdlib>
int n, q, seed;
int rval() {
	return rand() % 1000000000;
}
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &q, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ )
		printf("%d\n", rval());
	printf("%d\n", q);
	while ( q -- ) 
		printf("%d %d %d %d\n", rval(), rval(), rval(), rval());
}
