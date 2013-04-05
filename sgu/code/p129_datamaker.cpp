#include <cstdio>
#include <cstdlib>
#define RANGE 10
int m, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &m, &seed);
	srand(seed);
	printf("%d\n", 3);
	for(int i = 0; i < 3; i ++)
		printf("%d %d\n", rand() % RANGE, rand() % RANGE);
	printf("%d\n", m);
	for(int i = 0; i < m; i ++)
		printf("%d %d %d %d\n", rand() % RANGE, rand() % RANGE, rand() % RANGE, rand() % RANGE);
}
