#include <cstdio>
#include <cstdlib>
const char CH[3] = {'B', 'S'};
int P, O, S, N, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d%d", &P, &O, &S, &N, &seed);
	srand(seed);
	printf("%d %d %d\n", P, O, S);
	printf("%d\n", N);
	while ( N -- )
		printf("%c%c%c\n", CH[rand() % 2], CH[rand() % 2], CH[rand() % 2]);
}
