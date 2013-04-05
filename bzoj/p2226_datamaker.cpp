#include <cstdio>
#include <cstdlib>

int seed, n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
		printf("%d\n", rand() % 700000 + 1);
}
