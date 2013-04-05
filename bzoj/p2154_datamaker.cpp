#include <cstdio>
#include <cstdlib>
int seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d\n", rand() % 2000 + 1, rand() % 2000 + 1);
}
