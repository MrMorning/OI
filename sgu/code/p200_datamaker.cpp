#include <cstdio>
#include <cstdlib>
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d %d\n", 100, n);
	for(int i = 0; i < n; i ++)
		printf("%d ", rand() % 20 + 1);
}