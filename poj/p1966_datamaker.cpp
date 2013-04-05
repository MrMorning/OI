#include <cstdio>
#include <cstdlib>
int testNum, n, m, seed;
int a[51][51];
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &testNum, &n, &m, &seed);
	srand(seed);
	while(testNum --)
	{
		printf("%d", n);
		for(int i = 1; i <= m; i ++)
		{
			int s = rand() % n, t = rand() % n;
				a[s][t] = a[t][s] = true;
		}
		int cnt = 0;
		for(int i = 0; i < n; i ++)
			for(int j = i + 1; j < n; j ++)
				if(a[i][j])
					cnt ++;
		printf(" %d", cnt);
		for(int i = 0; i < n; i ++)
			for(int j = i + 1; j < n; j ++)
				if(a[i][j])
					printf(" (%d,%d) ", i, j);
		printf("\n");
	}
}
