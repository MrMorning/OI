#include <cstdio>
#include <cstdlib>
int seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	int m = rand() % 10000000 + 2;
	printf("%d %d\n", 1, m);
	int s = rand() % m + 1, t = rand() % (m - s) + s;
	printf("%d %d %d\n", s, t, rand() % 100000000);
}
