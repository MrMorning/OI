#include <cstdio>
#include <cstdlib>
int n, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	while (n --)
		printf("%d", rand() % 9 + 1);
}
