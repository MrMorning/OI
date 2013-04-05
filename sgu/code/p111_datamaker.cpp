#include <cstdio>
#include <cstdlib>
int seed, n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d", rand() % 9 + 1);
	for(int i = 0; i < n - 1; i ++)
		printf("%d", rand() % 10);
}
