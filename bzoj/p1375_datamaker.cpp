#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	int sVtx = rand() % n + 1, tVtx = rand() % n + 1;
	printf("%d %d %d %d\n", n, m, sVtx, tVtx);
	for(int i = 1; i <= m; i ++)
	{
		int a = rand() % n + 1;
		int b = rand() % n + 1;
		printf("%d %d %d %d\n", a, b, rand() % 100 + 1, rand() % 100 + 1);
	}
}
