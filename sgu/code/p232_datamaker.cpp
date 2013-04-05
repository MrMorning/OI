#include <cstdio>
#include <cstdlib>
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d %d\n", n, rand() % n);
	while(n --)
		printf("%d", rand() % 10);
}
