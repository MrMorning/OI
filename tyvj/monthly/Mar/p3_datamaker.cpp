#include <cstdio>
#include <cstdlib>
int n, m, q, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &q, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m ,q);
	for(int i = 0; i < m; i ++)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 1000000000 + 1);
	for(int i = 0; i < q; i ++)
		printf("%d\n", rand() % 1000000000 + 1);
}
