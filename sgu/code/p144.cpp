#include <cstdio>
int l, r;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &l, &r);
	double L = 60 * (r - l), Z;
	scanf("%lf", &Z);
	printf("%.7lf\n", 1 - (L - Z) * (L - Z) / (L * L));
}
