/*
 * Date: Fri Feb  4 23:10:52 CST 2011
 * Author: csimstu
 * Problem: poj2356
 * Algorithm: Pigeonhole Principle
 */
#include <cstdio>

int n, l, r;
int hash[10000], a[10001], s[10001];
bool suc = false;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d\n", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	for(int i = 1; i <= n; i ++)
	{
		if(s[i] % n == 0)
		{
			suc = true;
			l = 1, r = i;
			break;
		}
		int tmp = s[i] % n;
		if(hash[tmp] != 0)
		{
			suc = true;
			l = hash[tmp] + 1, r = i;
			break;
		}
		else
			hash[tmp] = i;
	}
	if(suc)
	{
		printf("%d\n", r - l + 1);
		for(int i = l; i <= r; i ++)
			printf("%d\n", a[i]);
	}
}
