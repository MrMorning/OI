#include <cstdio>
#include <cstdlib>
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d %d\n", n, rand() % (n / 10 + 1) + 1);
	for(int i = 1; i < n; i ++)
		printf("%d %d\n", i + 1, i);
}
