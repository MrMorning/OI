#include <cstdio>
#include <cstdlib>

int P, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &P, &seed);
	srand(seed);
	printf("%d %d %d\n", P, rand() % 100000 + 2, rand() % P);
}
