#include <cstdlib>
#include <cstdio>
int t, n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &t, &n, &seed);
	srand(seed);
	while(t --)
	{
		printf("%d\n", n);
		for(int i = 0; i < n; i ++)
			printf("%d %d %d\n", rand() % 10000, rand() % 10000, rand() % 10000000);
	}
	printf("0\n");
}
