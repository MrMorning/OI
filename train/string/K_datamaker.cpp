#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	int first = rand() % 20000000 + 1;
	n --;
	printf("%d\n", first);
	while ( n -- )
		printf("%d\n", rand() % first);
}
