#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 0; i < n; i ++)
		printf("%d\n", rand() * rand() % 10000000);
	for(int i = 0; i < m; i ++)
	{
		int u = rand() % n + 1;
		int v = rand() % n + 1;
		printf("%d %d\n", u, v);
	}
}
