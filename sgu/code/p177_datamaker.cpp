#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 0; i < m; i ++)
	{
		printf("%d %d %d %d %c\n", rand() % n + 1, rand() % m + 1, rand() % n + 1, rand() % m + 1, rand() % 2 == 0 ? 'b' : 'w');
	}
}
