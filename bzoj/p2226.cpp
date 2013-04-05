#include <cstdio>
#include <cassert>
typedef long long bignum_t;
#define BIGNUM_T_FMT "%lld"

const int N_MAX = 2000000;

int prime[N_MAX + 1], n_prime, min_div[N_MAX + 1], div_cnt[N_MAX + 1];
bool not_prime[N_MAX + 1];
bignum_t f[N_MAX + 1];

bignum_t pow(int d, int a)
{
	bignum_t p = d;
	bignum_t ret = (a & 1) ? p : 1;
	a >>= 1;
	while(a)
	{
		p *= p;
		if(a & 1)
			ret *= p;
		a >>= 1;
	}
	return ret;
}
inline bignum_t calc(int p, int a)
{
	return (pow(p, 2 * a) - 1) / ((bignum_t)p * p - 1) * p * (p - 1) + 1;
}
void pre_work()
{
	f[1] = 1;
	for(int i = 2; i <= N_MAX; i ++)
	{
		if(! not_prime[i])
		{
			prime[n_prime ++] = i;
			f[i] = calc(i, 1);
			min_div[i] = i;
			div_cnt[i] = 1;
		}
		for(int j = 0, upperlim = N_MAX / i; prime[j] < upperlim; j ++)
		{
			int num = prime[j] * i;
			not_prime[num] = true;
			min_div[num] = prime[j];
			if(i % prime[j] == 0)
			{
				div_cnt[num] = div_cnt[i] + 1;
				f[num] = calc(prime[j], div_cnt[num]) * f[num / pow(prime[j], div_cnt[num])];
				break;
			}
			else
			{
				div_cnt[num] = 1;
				f[num] = calc(prime[j], div_cnt[num]) * f[num / pow(prime[j], div_cnt[num])];
			}
		}
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	pre_work();
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
	{
		int m;
		scanf("%d", &m);
		printf(BIGNUM_T_FMT "\n", (f[m] + 1) * m / 2);
	}
}
