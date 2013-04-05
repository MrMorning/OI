#include <cstdio>
#include <cstdlib>
int seed;
double randval()
{
	return (double)(rand() % 10) + (double)rand() / RAND_MAX;
}
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("%.2lf %.2lf %.2lf\n", randval(), randval(), randval());
}
