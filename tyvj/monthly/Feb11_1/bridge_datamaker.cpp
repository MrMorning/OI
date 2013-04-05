#include <cstdio>
#include <cstdlib>
int seed, n;

int main()
{
	freopen("bridge.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	printf("%d\n", n);
	srand(seed);
	for(int i = 1; i < n; i ++)
		printf("%d ", rand() % 100 + 1);
	printf("\n");
	for(int i = 1; i < n; i ++)
		printf("%d ", rand() % 100 + 1);
	printf("\n");
	for(int i = 1; i < n; i ++)
		printf("%d ", rand() % 100 + 1);
	printf("\n");
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand() % 100 + 1);
	printf("\n");
}
