#include <cstdio>
#include <cstdlib>
int seed, n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 1; i < n; i ++)
		printf("%d ", rand() % i + 1);
}
