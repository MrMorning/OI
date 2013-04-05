#include <cstdio>
#include <cstdlib>
int seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d %d %d\n", rand() % 3 + 1, rand() % 3 + 1, rand() % 7 - 3, rand() % 20);
}
