#include <cstdio>
#include <cassert>
int n, m;
int solve(int s, int f, int t)
{
	int ans;
	int r = 2 * (m - 1);
	if(s == f)
		return t;
	int p = t / r; t = t % r;

	if(s - 1 < t)
	{
		if(t <= 2 * (m - s) + s - 1)
		{
			if(f <= s)
				ans = 2 * (m - s) + s - 1 + s - f;
			else
				ans = 2 * (m - s) + s - 1 + 2 * (s - 1) + f - s;
		}
		else
			return solve(s, f, r + 1) + r * p;
	}
	else
	{
		if(f >= s)
			ans = s - 1 + f - s;
		else
			ans = s - 1 + 2 * (m - s) + s - f;
	}
	return ans + r * p;
}
int main()
{
	scanf("%d%d", &n, &m);
	while(n --)
	{
		int s, f, t;
		scanf("%d%d%d", &s, &f, &t);
		printf("%d\n", solve(s, f, t));
	}
}
