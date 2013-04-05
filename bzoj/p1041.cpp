#include <cstdio>
#include <cmath>
#include <cassert>

typedef long long bignum_t;
#ifdef unix
#define BIGNUM_T_FMT "%lld"
#else
#define BIGNUM_T_FMT "%I64d"
#endif

bignum_t gcd(bignum_t a, bignum_t b)
{
	return b == 0 ? a : gcd(b, a % b);
}

bool is_sqr(bignum_t x)
{
	assert(x >= 0);
	bignum_t sqrt_x = (bignum_t)sqrt((double)x);
	return sqrt_x * sqrt_x == x;
}

int calc(bignum_t x)
{
	if((x & 1) == 0)
		return 0;
	int ret = 0;
	for(bignum_t s = 3; ; s += 2)
	{
		bignum_t sqr_t = x * 2 - s * s;
		if(sqr_t < 1)
			break;
		if((sqr_t & 1) && s * s > sqr_t && is_sqr(sqr_t))
		{
			bignum_t t = (int)sqrt(sqr_t);
			if(gcd(s, t) == 1)
				ret ++;
		}
	}
	return ret;
}

int bruce(bignum_t r)
{
	int ret = 0;
	for(bignum_t x = -r; x <= r; x ++)
		if(is_sqr(r * r - x * x))
		{
			ret += 2;
			//printf(BIGNUM_T_FMT " " BIGNUM_T_FMT "\n", x, (bignum_t)sqrt(r * r - x * x));
		}
	return ret - 2;
}

int solve(bignum_t r)
{
	int ans = 0;
	bignum_t x;
	for(x = 1; x * x < r; x ++)
		if(r % x == 0)
			ans += calc(x) + calc(r / x);
	if(x * x == r)
		ans += calc(x);
	return (ans * 2 + 1) * 4;
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	bignum_t r;
	scanf(BIGNUM_T_FMT, &r);
	printf("%d\n", solve(r));
}
