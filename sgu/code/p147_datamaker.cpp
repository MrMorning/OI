#include <cstdio>
#include <cstdlib>
int seed, n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	n = rand() % 1000000 + 1;
	printf("%d\n", n);
	printf("%d %d\n", rand() % n + 1, rand() % n + 1);
	printf("%d %d\n", rand() % n + 1, rand() % n + 1);
	printf("%d %d\n", rand() % n + 1, rand() % n + 1);
}
