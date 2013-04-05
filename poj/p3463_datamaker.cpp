#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("1\n");
	printf("%d %d\n", n, m);
	for(int i = 1; i <= m; i ++)
	{
		int u = rand() % n + 1, v = rand() % n + 1;
		printf("%d %d %d\n", u, v, rand() % 10 + 1);
	}
	printf("%d %d\n", 1, n);
}
