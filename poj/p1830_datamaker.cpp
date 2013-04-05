#include <cstdlib>
#include <cstdio>

int testNum, n, seed, m;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &testNum, &n, &seed);
	srand(seed);
	printf("%d\n", testNum);
	while(testNum --)
	{
		printf("%d\n", n);
		for(int i = 1; i <= n; i ++)
			printf("%d ", rand() % 2);
		printf("\n");
		for(int i = 1; i <= n; i ++)
			printf("%d ", rand() % 2);
		printf("\n");
		int m = rand() % (n * n);
		while(m --)
			printf("%d %d\n", rand() % n + 1, rand() % n + 1);
		printf("0 0\n");
	}
}
