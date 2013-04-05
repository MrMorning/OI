#include <cstdio>
#include <cstdlib>
int n, k, t, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &k ,&t, &seed);
	srand(seed);
	printf("%d %d %d\n", n, k, t);
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand()%t+1);
	printf("\n");
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand()%300+1);
	printf("\n");
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand()%k+1);
	printf("\n");
}

