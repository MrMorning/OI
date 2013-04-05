#include <cstdio>
#include <cstdlib>
int n, m, k, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, k);
	while (m --)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 1000 + 1);
	printf("0\n");
}
