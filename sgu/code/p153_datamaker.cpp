#include <cstdio>
#include <cstdlib>
int _, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &_, &seed);
	srand(seed);
	printf("%d\n", _);
	for(int t = 0; t < _; t ++)
	{
		int m = rand() % 9;
		printf("%d %d\n", rand() % 10000 + 1, m);
		for(int i = 0; i < m; i ++)
			printf("%d ", rand() % 8 + 2);
		printf("\n");
	}
}
