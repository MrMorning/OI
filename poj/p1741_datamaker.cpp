#include <cstdio>
#include <cstdlib>
int _, n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &_, &n, &seed);
	srand(seed);
	while(_ --)
	{
		printf("%d %d\n", n, rand() % 5000 + 1);
		for(int i = 1; i < n; i ++)
			printf("%d %d %d\n", i + 1, i, rand() % 1000 + 1);
	}
	printf("0 0\n");
}
