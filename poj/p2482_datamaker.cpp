#include <cstdio>
#include <cstdlib>
const int RANGE = 100000;
const int MAXN = (1<<18);
int testNum, n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &testNum, &n, &seed);
	srand(seed);
	while(testNum --)
	{
		printf("%d %d %d\n", n, rand()%RANGE+1, rand()%RANGE+1);
		for(int i = 1; i <= n; i ++)
			printf("%d %d %d\n", rand()%(MAXN), rand()%(MAXN), rand()%100+1);
	}

}
