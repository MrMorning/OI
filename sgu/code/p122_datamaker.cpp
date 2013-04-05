#include <cstdio>
#include <cstdlib>
int n, seed;
bool linked[1000][1000];
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
	{
		int t = rand() % n + (n + 1) / 2;
		for(int j = 0; j < t; j ++)
		{
			int v = rand() % n;
			linked[i][v] = linked[v][i] = true;
		}
	}
	for(int i = 0; i < n; i ++, printf("\n"))
		for(int j = 0; j < n; j ++)
			if(linked[i][j])
				printf("%d ", j + 1);
}
