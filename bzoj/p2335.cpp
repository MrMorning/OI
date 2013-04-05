#include <cstdio>
#include <cassert>

typedef long long bignum_t;
bignum_t a1, b1, c1, a2, b2, c2, a3, b3, c3, d1, d2, d3, k, m, x;

bool check3(bignum_t x)
{
	return 2 <= x && x <= 8 * k && x != 8 * k - 1;
}

bool check2(bignum_t x, int c)
{
	if(x == 0 && c == 0)
		return true;
	if(c)
		return 2 <= x && x <= 5 * k && x != 5 * k - 1;
	else
	{
		if(1 <= x && x <= 5 * k - 2)
			return true;
		if(x == 5 * k)
			return true;
		if(x >= 5 * k - 2 && x <= 6 * k && x % 3 == 0)
			return true;
	}
	return false;
}

bool check1(bignum_t x, int c)
{
	if(x == 0 && c == 0)
		return true;
	if(c)
		return 2 <= x && x <= 2 * k && x % 2 == 0;
	else
	{
		if(1 <= x && x <= k)
			return true;
		if(2 <= x && x <= 2 * k && x % 2 == 0)
			return true;
		if(3 <= x && x <= 3 * k && x % 3 == 0)
			return true;
	}
	return false;
}

bool judge()
{
	if(2 * m <= x && x <= 6 * m && x % m == 0)
		return true;
	if(check2(x - m, 1))
		return true;
	if(check2(x - 2 * m, 0))
		return true;
	if(check1(x - 3 * m, 0))
		return true;
	if(check1(x - 4 * m, 0))
		return true;
	return check3(x);
}

int main()
{

	int n_test;
	scanf("%d", &n_test);
	scanf("%lld%lld%lld%lld%lld", &a1, &b1, &c1, &d1, &k);
	scanf("%lld%lld%lld%lld%lld", &a2, &b2, &c2, &d2, &m);
	scanf("%lld%lld%lld%lld%lld", &a3, &b3, &c3, &d3, &x);
	int ans = 0;
	while(n_test --)
	{
		ans += judge();
		k = ((a1 * k) % d1 * k + b1 * k + c1) % d1 + 20;
		m = ((a2 * m) % d2 * m + b2 * m + c2) % d2 + 20;
		x = ((a3 * x) % d3 * x + b3 * x + c3) % d3 + 20;
	}
	printf("%d\n", ans);
}
