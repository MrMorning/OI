#include <cstdio>
#include <cstdlib>
#define MK_RAND (rand() % 1000000)
const int N_MAX = 10000;
int used[N_MAX];
int n_used, n, n_query, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &n_query, &seed);
	srand(seed);
	used[n_used ++] = 0;
	printf("1\n\n%d\n", n);
	for(int i = 1; i < n; i ++)
	{
		int u = MK_RAND % n_used;
		used[n_used ++] = i + 1;
		printf("%d %d %d\n", i + 1, u + 1, rand() % 1000000);
	}
	for(int i = 0; i < n_query; i ++)
	{
		int t = 1;//rand() % 2;
		if(t)
		{
			int u = MK_RAND % n;
			int v = MK_RAND % n;
			if(u != v)
				printf("QUERY %d %d\n", u + 1, v + 1);
		}
		else
		{
			int i = MK_RAND % (n - 1);
			printf("CHANGE %d %d\n", i + 1, rand() % 100000);
		}
	}
	printf("DONE");
}
