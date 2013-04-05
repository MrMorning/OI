#include <cstdio>
#include <cstdlib>

int testNum, n, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &testNum, &n, &seed);
	srand(seed);
	while(testNum --)
	{
		printf("%d\n", n);
		for(int i = 1; i <= n; i ++)
			printf("%d %d\n", rand()%i, rand()%32768);
	}
}
