#include <cstdio>
#include <cstdlib>
#include <ctime>
int main()
{
	freopen("t.in", "w", stdout);
	int n = 50, m = 50, p = 10;
	srand(time(NULL));
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= m; j ++)
			printf("%d ", rand() % 100 + 1);
		printf("\n");
	}
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= m; j ++)
			printf("%d ", rand() % 100 + 1);
		printf("\n");
	}
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= m; j ++)
			printf("%d ", rand() % 2000 + 1);
		printf("\n");
	}
	printf("%d %d %d\n", rand() % 100 + 1, rand() % 100 + 1, rand() % (1 << 30) + 1);
	printf("%d\n", p);
	for(int i = 1; i <= p; i ++)
		printf("%d %d %d\n", rand() % 100 + 1, rand() % 100 + 1, rand() % 2000 + 1);
}
