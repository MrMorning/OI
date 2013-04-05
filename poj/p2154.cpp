/*
 * Date: Sun Feb  6 10:57:06 CST 2011
 * Author: csimstu
 * Prob: poj2154
 * Sol: Polya Counting + Euler Function + expMod
 */
#include <cstdio>

int n, modNum;
int binFac[32];

int expMod(int x, int n)
{
	int cnt = 1;
	while(n)
	{
		if(n & 1)
			cnt = (x % modNum) * (cnt % modNum) % modNum;
		n >>= 1;
		x = (x % modNum) * (x % modNum) % modNum;
	}
	return cnt;
}

int euler(int n)
{
	int ans = 1;
	for(int i = 2; i * i <= n; i ++)
	{
		if(n % i == 0)
		{
			ans *= i - 1;
			n /= i;
			while(n % i == 0)
			{
				ans *= i;
				n /= i;
			
			}
		}
	}
	if(n > 1)
		ans *= n - 1;
	return ans;
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
	{
		int ans = 0;
		scanf("%d %d\n", &n, &modNum);
		for(int i = 1; i * i <= n; i ++)
		{
			if(n % i == 0)
			{
				ans = (ans + euler(n / i) % modNum * expMod(n, i - 1)) % modNum;
				if(i * i != n)
					ans = (ans + euler(i) % modNum * expMod(n, n / i - 1)) % modNum;
			}
		}
		printf("%d\n", ans);
	}
}
