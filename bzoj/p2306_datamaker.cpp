#include <cstdio>
#include <cstdlib>
int n, m, s_vtx, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 0; i < n; i ++)
		printf("%.1lf ", (double) rand() / rand());
	int s_vtx = rand() % n + 1;
	printf("\n%d\n", s_vtx);
	printf("%.6lf\n", (double)(rand() % 10000) / 10000 - 10E-6);
	while(m --)
	{
		int u = rand() % n + 1,
			v = rand() % n + 1;
		printf("%d %d\n", u, v);
	}
}
