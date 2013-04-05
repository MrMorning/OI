#include <cstdio>
#include <cstdlib>
int n, k, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &k, &seed);
	printf("%d %d\n", n, k);
	srand(seed);
	for(int i = 1; i <= n ;i ++)
		printf("%d\n", rand() % 2000 + 1);
}
