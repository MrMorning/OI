#include <cstdio>
#include <cstdlib>
int seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d 10007\n", rand() % 1000000000 + 1, rand() % 500 + 1);
}
