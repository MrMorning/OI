#include <cstdio>
#include <cstdlib>
bool linked[101][101];
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	while(m --)
	{
		int u = rand() % n, v = rand() % n;
		linked[u][v] = linked[v][u] = true;
	}
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
			if(linked[i][j])
				printf("%d ", j + 1);
		printf("0\n");
	}
}
