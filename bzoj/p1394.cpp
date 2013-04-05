#include <cstdio>
#include <cmath>
long long n;
int main()
{
	scanf("%lld", &n);
	printf("%d\n", (int)std::sqrt((long double)n - 1) + 1);
}
