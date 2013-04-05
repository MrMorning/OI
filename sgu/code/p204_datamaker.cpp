#include <cstdio>
#include <cstdlib>
#include <cmath>
int seed;
double randval()
{
	return rand() % 500 + (double)rand() / RAND_MAX;
}

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	double b1 = randval(), b2 =randval();
	double t1 = b1 + randval(), t2 = b2 + randval();
	printf("%.4lf %.4lf %.4lf %.4lf %.4lf %.4lf %.4lf %.4lf\n", b1, t1, b2, t2, randval(), randval(), randval(), randval());
}

