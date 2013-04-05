#include <cstdio>
#include <cstdlib>
int seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d\n", rand() % 100000 + 1);
}
