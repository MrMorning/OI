#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, n - 1);
	for(int i = 2; i <= n; i ++)
		printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % 300000);
	printf("%d\n", m);
	while(m --)
		printf("%d %d %d %d\n", rand() % n, rand() % n, rand() % n, rand() % n);
}
