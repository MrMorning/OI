#include <cstdio>
#include <cstdlib>
int T, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &T, &seed);
	srand(seed);
	while ( T -- )
		printf("%d\n", rand() % 10000 + 1);
	printf("0\n");
}
