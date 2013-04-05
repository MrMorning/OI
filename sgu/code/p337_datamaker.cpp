#include <cstdio>
#include <cstdlib>
int n, k, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &k, &n, &seed);
	srand(seed);
	printf("%d\n", k);
	while ( n -- )
		printf("%c", rand() % 3 + 'a');
}
