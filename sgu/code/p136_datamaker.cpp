#include <cstdio>
#include <cstdlib>
int n, seed;
double randval()
{
	return (double)rand() + (double)rand() / RAND_MAX;
}
int main()
{
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
		printf("%.3lf %.3lf\n", randval(), randval());
}
