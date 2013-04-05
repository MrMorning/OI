#include <cstdio>
#include <cstdlib>
int N, M, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &N, &M, &seed);
	srand(seed);
	printf("%d %d %d\n", N, M, rand() % 20000 + 1);
	while ( N -- )
		printf("%d ", rand() % 20000 + 1);
	puts("");
	while ( M -- )
		printf("%d ", rand() % 20000 + 1);
}
