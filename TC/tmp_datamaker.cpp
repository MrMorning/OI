#include <cstdio>
#include <cstdlib>
int seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d %d %d %d", rand() % 50, rand() % 50, rand() % 50, rand() % 50 + 1, rand() % 50 + 1);
}
