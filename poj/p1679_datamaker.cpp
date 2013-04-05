#include <cstdio>
#include <cstdlib>
int n, m, seed;
int t;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &t, &n, &m, &seed);
	srand(seed);
	printf("%d\n", t);
	while(t --)
	{
		printf("%d %d\n", n, m);
	for(int i = 0; i < m; i ++)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 1000);
	}
}
