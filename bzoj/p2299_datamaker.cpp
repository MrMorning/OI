#include <cstdio>
#include <cstdlib>
const int RANGE = 100000000;
int seed, n_test;
int randval()
{
	return rand() % RANGE + 1;
}
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n_test, &seed);
	srand(seed);
	printf("%d\n", n_test);
	while(n_test --)
		printf("%d %d %d %d\n", randval(), randval(), randval(), randval());
}
