#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	while (n --)
		printf("%d %d %d\n", rand() % 10, rand() % 10, rand() % 10);
}
