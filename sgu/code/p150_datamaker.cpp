#include <cstdio>
#include <cstdlib>
int seed;
int randval()
{
	return rand() % 500000;
}
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d %d %d %d\n", randval(), randval(), randval(), randval(), rand() % 100000 + 1);
}
