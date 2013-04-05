#include <cstdio>
#include <cstdlib>
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("5\n");
	for(int i = 0; i < 5; i ++)
	{
		printf("%d", n);
		for(int j = 0; j < n; j ++)
			printf(" %d", rand() % 1000000000);
		printf("\n");
	}
}
