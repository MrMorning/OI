#include <cstdio>
#include <cstdlib>
int testNum, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &testNum, &seed);
	srand(seed);
	printf("%d\n", testNum);
	while(testNum --)
	{
		int n = rand() % 50000 + 1;
		int m = rand() % 50000 + 1;
		printf("%d %d\n", n, m);
		for(int i = 1; i <= n; i ++)
			printf("%d ", rand() % (1 << 16) + 1);
		printf("\n");
		for(int i = 1; i <= m; i ++)
		{
			printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % (1 << 16) + 1);
		}
	}
}
