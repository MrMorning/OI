#include <cstdio>
#include <cstring>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
const int N_PRIME_MAX = 39, N_RANGE_MAX = 170;
struct Int_by_factor
{
	int factor[N_PRIME_MAX];
	static int prime[N_PRIME_MAX];
	Int_by_factor(int base)
	{
		memset(factor, 0, sizeof(factor));
		for(int i = 0; i < N_PRIME_MAX; i ++)
			while(base % prime[i] == 0)
				base /= prime[i], factor[i] ++;
	};
	void mul(Int_by_factor &x)
	{
		for(int i = 0; i < N_PRIME_MAX; i ++)
			factor[i] += x.factor[i];
	}
	void print()
	{
		double x = 1;
		for(int i = 0; i < N_PRIME_MAX; i ++)
			for(int j = 0; j < factor[i]; j ++)
				x *= prime[i];
		printf("%.0lf", x);
	}
};
int Int_by_factor::prime[N_PRIME_MAX];
int n_prime;

void init_prime()
{
	static bool hash[N_RANGE_MAX];
	memset(hash, 1, sizeof(hash));
	for(int i = 2; i < N_RANGE_MAX; i ++)
		if(hash[i])
		{
			Int_by_factor::prime[n_prime ++] = i;
			for(int j = i + i; j < N_RANGE_MAX; j += i)
				hash[j] = false;
		}
}

int main()
{
	int n_test;
	freopen("t.in", "r", stdin);
	init_prime();
	scanf("%d", &n_test);
	while(n_test --)
	{
		int n, k;
		scanf("%d %d\n", &n, &k);
		if(n > k)
			printf("%d %d\n", 0, 1);
		else
		{
			Int_by_factor x(n + 1 - k);
			Int_by_factor kplus1(k + 1);
			for(int i = 0; i < n - 1; i ++)
				x.mul(kplus1);
			Int_by_factor down(1);
			Int_by_factor theK(k);
			for(int i = 0; i < n; i ++)
				down.mul(theK);
			for(int i = 0; i < N_PRIME_MAX; i ++)
			{
				int tmp = MIN(x.factor[i], down.factor[i]);
				x.factor[i] -= tmp;
				down.factor[i] -= tmp;
			}
			x.print();
			printf(" ");
			down.print();
			printf("\n");
		}
	}
}
