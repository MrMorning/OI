#include <cstdio>
#include <cstdlib>
int n,m,seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	for(int k = 0; k < 10; k ++)
	{
		printf("%d %d\n", n, m);
		for(int i = 1; i <= n; i ++)
			printf("%d ", rand() % 100 + 1);
	}
	printf("\n0 0\n");
}
