#include <cstdio>
#include <cstdlib>
int seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d %d %d %d %d\n", rand() % 10000 + 1,
			rand() % 101, rand() % 101, rand() % 101,
			rand() % 1000 + 1, rand() % 100);
}
