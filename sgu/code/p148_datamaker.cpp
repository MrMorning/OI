#include <cstdio>
#include <cstdlib>
#define RANGE 100000
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
	{
		int t = rand() % (RANGE / 2 + 1);
		printf("%d %d %d\n", t, t + rand() % (RANGE - t), rand() % RANGE);
	}
}
