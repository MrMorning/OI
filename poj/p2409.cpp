/*
 * Date: Sat Feb  5 22:14:38 CST 2011
 * Author: csimstu
 * Problem: poj2409
 * Algorithm: Polya Counting
 */
#include <cstdio>

int fac[33];

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
	while(1)
	{
		int c, n;
		scanf("%d %d\n", &c, &n);
		if(c == 0 && n == 0)
			break;
		fac[0] = 1;
		for(int i = 1; i <= n; i ++)
			fac[i] = fac[i - 1] * c;
		int ans = 0;
		for(int i = 0; i <= n - 1; i ++)
			ans += fac[gcd(i, n)];
		if(n & 1)
			ans += n * fac[(n - 1) / 2 + 1];
		else
			ans += n / 2 * (fac[n / 2] + fac[n / 2 + 1]);
		printf("%d\n", ans / (2 * n));
	}
}
