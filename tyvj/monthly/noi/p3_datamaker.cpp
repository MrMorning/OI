#include <cstdio>
#include <cstdlib>
int seed, n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", rand() % n + 1);
}
