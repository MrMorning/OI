#include <cstdio>
#include <cstdlib>
#define RANGE 60000
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 1; i < n; i ++)
		printf("%d %d\n", i, i + 1);
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand() % RANGE - RANGE / 2);
	printf("\n%d\n", m);
	while(m --)
	{
		int t = rand() % 3;
		if(t == 0)
			printf("CHANGE %d %d\n", rand() % n + 1, rand() % RANGE - RANGE / 2);
		else if(t == 1)
			printf("QSUM %d %d\n", rand() % n + 1, rand() % n + 1);
		else
			printf("QMAX %d %d\n", rand() % n + 1, rand() % n + 1);
	}
}
