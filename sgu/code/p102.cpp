#include <cstdio>
#include <cmath>
#include <cassert>
int pow(int a, int n)
{
	int res = (n & 1) ? a : 1;
	for(n >>= 1; n; n >>= 1)
	{
		a *= a;
		if(n & 1)
			res *= a;
	}
	return res;
}

int phi(int x)
{
	int res = 1;
	for(int i = 2, upperlim = (int)sqrt(x); i <= upperlim; i ++)
		if(x % i == 0)
		{
			int cnt = 0;
			while(x % i == 0)
				x /= i, cnt ++;
			res *= (i - 1) * pow(i, cnt - 1);
		}
	if(x > 1)
		res *= x - 1;
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	printf("%d\n", phi(n));
}
