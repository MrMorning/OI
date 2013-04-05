#include <cstdio>
#include <cstdlib>
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	int a = rand() % 4 - 5,
		b = rand() % 5,
		c = rand() % 5;
	printf("%d %d %d\n", a, b, c);
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand() % 5 + 1);
}
