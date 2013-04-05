#include <cstdio>
#include <cstdlib>
int n, p, b, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &p, &b, &seed);
	srand(seed);
	printf("%d %d %d\n", n, p, b);
	for(int i = 0; i < n; i ++)
		printf("%d ", rand() % 2000000000);
}
