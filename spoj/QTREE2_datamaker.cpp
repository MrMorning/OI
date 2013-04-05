#include <cstdio>
#include <cstdlib>
int n, m, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed ++);
	printf("%d\n", 25);
	for(int tmp = 0; tmp < 25; tmp ++)
	{
		printf("%d\n", n);
		for(int i = 1; i < n; i ++)
		{
			int p = rand() % i;
			printf("%d %d %d\n", p + 1, i + 1, rand() * rand() % 100000 + 1);
		}
		for(int k = 0; k < m; k ++)
		{
			int t = 1;// rand() % 2;
			if(t)
				printf("DIST %d %d\n", rand() % n + 1, rand() % n + 1);
			else
				printf("KTH %d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % n + 1);
		}
		printf("DONE\n");
	}
}
