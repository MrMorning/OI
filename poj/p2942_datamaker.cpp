#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	printf("%d %d\n", n, m);
	srand(seed);
	while(m --)
		printf("%d %d\n", rand() % n + 1, rand() % n + 1);
	printf("0 0\n");
}
