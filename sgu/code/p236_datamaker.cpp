#include <cstdio>
#include <cstdlib>
int n, seed, e[50][50], c[50][50], t[50][50];
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	for(int i = 0; i < n * n; i ++)
	{
		int u = rand() % n, v = rand() % n;
		if(u == v)
			continue;
		e[u][v] = true;
		c[u][v] = rand() % 10 + 1;
		t[u][v] = rand() % 10 + 1;
	}
	int cnt = 0;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(e[i][j])
				cnt ++;
	printf("%d %d\n", n, cnt);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(e[i][j])
				printf("%d %d %d %d\n", i + 1, j + 1, c[i][j], t[i][j]);
}
