#include <cstdio>
#include <cstdlib>

int n, m, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	printf("%d\n", n);
	srand(seed);
	for(int i = 1; i < n; i ++)
		printf("1 %d\n", i + 1);
	printf("%d\n", m);
	for(int i = 1; i <= m; i ++)
	{
		int t = rand() % 2;
		if(t)
			printf("C %d\n", rand()%n+1);
		else
			printf("Q %d\n", rand()%n+1);

	}
}
