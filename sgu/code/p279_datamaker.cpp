#include <cstdio>
#include <cstdlib>
int n, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	n = rand() % 1000 + 1;
	printf("%d\n", n);
	for ( int i = 1;  i <= n; i ++ )
		printf(" %d", rand() % (n-i+1));
}
