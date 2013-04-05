#include <cstdio>
#include <cstring>
#include <cstdlib>
int n, l, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &l, &seed);
	printf("%d %d\n", n, l);
	srand(seed);
	for(int i = 1; i <= n; i ++)
		printf("%d\n", rand() % 100 + 1);
}
