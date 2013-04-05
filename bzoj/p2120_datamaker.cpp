#include <cstdio>
#include <cstdlib>
#define RANGE 1000000
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand() % RANGE + 1);
	printf("\n");
	for(int i = 1; i <= m; i ++)
	{
		int t = rand() % 4;
		if(t)
		{
			int l = rand() % n + 1,
				r = rand() % n + 1;
			if(l > r)
			{
				int tmp = l;
			   	l = r, r = tmp;
			}
			printf("Q %d %d\n", l, r);
		}
		else
			printf("R %d %d\n", rand() % n + 1, rand() % RANGE + 1);
	}
}
