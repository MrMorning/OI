#include <cstdlib>
#include <cstdio>
int n, seed;
int a[201][201];
inline int min(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d %d %d\n", n, rand() % n + 1, rand() % n + 1);
	int cnt = min(5000, rand() % (n * n) + 1);
	for(int i = 1; i <= cnt; i ++)
	{
		int x = rand() % n + 1;
		int y = rand() % n + 1;
		a[x][y] = 1;
	}
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= n; j ++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}
