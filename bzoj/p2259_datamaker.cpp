#include <cstdio>
#include <cstdlib>
int main()
{
	freopen("t.in", "w", stdout);
	int n, seed;
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand() % 1000000);
}
