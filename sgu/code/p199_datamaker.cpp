#include <cstdio>
#include <cstdlib>
int seed, n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
		printf("%d %d\n", rand() % 10 + 1, rand() % 10 + 1);
}
