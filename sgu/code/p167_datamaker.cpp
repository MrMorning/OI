#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, rand() % (n * m) + 1);
	for(int i = 0; i < n; i ++, printf("\n"))
		for(int j = 0; j < m; j ++)
			printf("%d ", rand() % 100000);
}
