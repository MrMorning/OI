#include <cstdio>

typedef long long bignum_t;
const int POW_MAX = 30;
const int INFINITY = 0x3f3f3f3f;
bignum_t f[POW_MAX + 1];
int k, m;
//f[i]: the sum of 1s in [0, 2 ^ i - 1]
void init()
{
	f[0] = 0;
	for(int i = 1; i <= POW_MAX; i ++)
		f[i] = (f[i - 1] << 1) + ((bignum_t)1 << i - 1);
}

bignum_t find(bignum_t x)
{
	bignum_t res = 0;
	for(int i = POW_MAX, one_cnt = 0; i >= 1; i --)
	{
		bignum_t tmp = f[i - 1] + one_cnt * (1 << i - 1);
		if(tmp + one_cnt + 1 <= x)
			x -= tmp, res |= (1 << i - 1), one_cnt ++;
	}
	return res;
}

bignum_t count(bignum_t x) //the sum of 1 in [0, x]
{
	int one_cnt = 0;
	bignum_t res = 0;
	for(int i = POW_MAX; i >= 1; i --)
		if(x & (1 << i - 1))
		{
			res += f[i - 1] + one_cnt * (1 << i - 1);
			one_cnt ++;
		}
	return res + one_cnt;
}

int check(bignum_t s)
{
	bignum_t a = 0, b, upperlim = (1 << k) - 1;
	int res = 0;
	while(a < upperlim)
	{
		b = find(s + count(a));
		res ++;
		if(a == b)
			return INFINITY;
		a = b;
	}
	return res;
}

void solve()
{
	scanf("%d%d", &k, &m);
	bignum_t lb = 0, rb = 1ll << POW_MAX, mid = (lb + rb) >> 1;
	while(lb + 1 < rb)
	{
		if(check(mid) <= m)
			rb = mid;
		else
			lb = mid;
		mid = (lb + rb) >> 1;
	}
	printf("%lld\n", rb);
}

int main()
{
	freopen("t.in", "r", stdin);
	init();
	solve();
//	check(4);
}
