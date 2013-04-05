#include <cstdio>
#include <cstdlib>
int n, seed, range;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &range, &seed);
	srand(seed);
	n = rand() % range + 1;
	printf("%d\n", n);
	for ( int i = 0; i < 2 * n - 1; i ++ ) 
		printf("%c", rand() % 2 == 0 ? 'Q' : 'C');
}
