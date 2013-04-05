#include <cstdio>
const int N_MAX = 40001;
bool is_prime[N_MAX];
int f[N_MAX], g[N_MAX], euler[N_MAX], prime[N_MAX];
int n_prime;

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	n --;
	for(int i = 1; i <= n; i ++)
		is_prime[i] = true;
	f[1] = 1;
	for(int i = 2; i <= n; i ++)
	{
		if(is_prime[i])
			prime[n_prime ++] = i;
		for(int j = 0; j < n_prime; j ++)
		{
			if(prime[j] * i <= n)
				is_prime[prime[j] * i] = false;
			if(i % prime[j] == 0)
			{
				g[i] = prime[j];
				if(g[i / prime[j]] == g[i])
					f[i] = f[i / prime[j]] * prime[j];
				else
					f[i] = prime[j];
				break;
			}
		}
	}
	euler[1] = 1;
	int cnt = 0;
	for(int i = 2; i <= n; i ++)
	{
		euler[i] = euler[i / f[i]] * (f[i] - f[i] / g[i]); 
		cnt += euler[i];
	}
	printf("%d\n", cnt * 2 + 1 + 2);
}
