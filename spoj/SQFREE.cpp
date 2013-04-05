#include <cstdio>
#include <cstring>
#include <cmath>
typedef long long bignum_t;
#define BIGNUM_T_FMT "%I64d"
const int N_MAX = 10000011;
int prime[N_MAX], n_prime;
int coef[N_MAX];
void solve(bignum_t n)
{
	static bool not_prime[N_MAX];
	int m = (int)sqrt(n);
	memset(not_prime, 0, sizeof(bool) * (m + 1));
	bignum_t ret = n;
	for(int i = 2; i <= m; i ++)
	{
		if(! not_prime[i])
		{
			prime[n_prime ++] = i;
			coef[i] = -1;
		}
		ret += (bignum_t)coef[i] * (n / ((bignum_t)i * i));
		for(int j = 0, upperlim = m / i; prime[j] <= upperlim; j ++)
		{
			int k = i * prime[j];
			not_prime[k] = true;
			if(i % prime[j] == 0)
			{
				coef[k] = 0;
				break;
			}
			else
				coef[k] = coef[i] * -1;
		}
	}
	printf(BIGNUM_T_FMT "\n", ret);
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
	{
		bignum_t n;
		scanf(BIGNUM_T_FMT, &n);
		solve(n);
	}
}
