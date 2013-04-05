#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	while ( m -- )
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 1000 + 1);
}
