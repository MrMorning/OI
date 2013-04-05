#include <cstdio>
#include <cstdlib>
#define RANGE 100000000
int seed, n;
double randval()
{
	return (double)(rand() % (2 * RANGE) - RANGE) / 1000;
}
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < 5; j ++)
			printf("%.6lf ", randval());
		printf("\n");
	}
}
