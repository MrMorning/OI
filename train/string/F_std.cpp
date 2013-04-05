#include<stdio.h>
#include<string.h>
#define MAXD 200010
char b[MAXD];
int N, M, K, sa[MAXD], rank[MAXD], height[MAXD], r[MAXD], wa[MAXD], wb[MAXD], ws[MAXD], wv[MAXD];
int s[MAXD], num[MAXD];
void init()
{
	int i, j, k = 0;
	scanf("%s", b);
	for(i = 0; b[i]; i ++, k ++)
		r[k] = b[i];
	N = i;
	r[k ++] = '$';
	scanf("%s", b);
	for(i = 0; b[i]; i ++, k ++)
		r[k] = b[i];
	r[M = k] = 0;
}
int cmp(int *p, int x, int y, int l)
{
	return p[x] == p[y] && p[x + l] == p[y + l];
}
void da(int n, int m)
{
	int i, j, p, *x = wa, *y = wb, *t;
	for(i = 0; i < m; i ++)
		ws[i] = 0;
	for(i = 0; i < n; i ++)
		++ ws[x[i] = r[i]];
	for(i = 1; i < m; i ++)
		ws[i] += ws[i - 1];
	for(i = n - 1; i >= 0; i --)
		sa[-- ws[x[i]]] = i;
	for(j = p = 1; p < n; j *= 2, m = p)
	{
		for(p = 0, i = n - j; i < n; i ++)
			y[p ++] = i;
		for(i = 0; i < n; i ++)
			if(sa[i] >= j)
				y[p ++] = sa[i] - j;
		for(i = 0; i < n; i ++)
			wv[i] = x[y[i]];
		for(i = 0; i < m; i ++)
			ws[i] = 0;
		for(i = 0; i < n; i ++)
			++ ws[wv[i]];
		for(i = 1; i < m; i ++)
			ws[i] += ws[i - 1];
		for(i = n - 1; i >= 0; i --)
			sa[-- ws[wv[i]]] = y[i];
		for(t = x, x = y, y = t, x[sa[0]] = 0, i = p = 1; i < n; i ++)
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p ++;
	}
}
void calheight(int n)
{
	int i, j, k = 0;
	for(i = 1; i <= n; i ++)
		rank[sa[i]] = i;
	for(i = 0; i < n; height[rank[i ++]] = k)
		for(k ? -- k : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k ++);
}
void solve()
{
	int i, j, k, top = 0, n;
	long long int ans, t;
	da(M + 1, 128);
	calheight(M);
	ans = 0;
	for(i = 1; i <= M; i ++)
	{
		if(height[i] < K)
		{
			t = 0;
			top = -1;
		}
		else
		{
			if(sa[i - 1] < N)
			{
				n = 1;
				t += height[i] - K + 1;
			}
			else
				n = 0;
			while(top >= 0 && height[i] <= s[top])
			{
				if(num[top])
				{
					t -= (long long int)num[top] * (s[top] - K + 1);
					t += (long long int)num[top] * (height[i] - K + 1);
					n += num[top];
				}
				-- top;
			}
			s[++ top] = height[i];
			num[top] = n;
			if(sa[i] > N)
				ans += t;
		}
	}
	for(i = 1; i <= M; i ++)
	{
		if(height[i] < K)
		{
			t = 0;
			top = -1;
		}
		else
		{
			if(sa[i - 1] > N)
			{
				n = 1;
				t += height[i] - K + 1;
			}
			else
				n = 0;
			while(top >= 0 && height[i] <= s[top])
			{
				if(num[top])
				{
					t -= (long long int)num[top] * (s[top] - K + 1);
					t += (long long int)num[top] * (height[i] - K + 1);
					n += num[top];
				}
				-- top;
			}
			s[++ top] = height[i];
			num[top] = n;
			if(sa[i] < N)
				ans += t;
		}
	}
	printf("%lld\n", ans);
}
int main()
{
	freopen("t.in", "r", stdin);
	for(;;)
	{
		scanf("%d", &K);
		if(!K)
			break;
		init();
		solve();
	}
	return 0;
}
