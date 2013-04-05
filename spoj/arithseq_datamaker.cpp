#include <cstdio>
#include <cstdlib>
int seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d %d %d\n", rand() % 1000000000 + 1, rand() % 20000 + 1,
			rand() % 100000 + 1, 0);
}
