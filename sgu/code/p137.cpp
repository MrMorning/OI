#include <cstdio>
#include <cstring>
int n, k, m, a[1000], b[1000];

void exGcd(int a, int b, int &x, int &y)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return;
	}
	else
	{
		int x0, y0;
		exGcd(b, a % b, x0, y0);
		x = y0, y = x0 - a / b * y0;
	}
}

int solve(int a, int b, int m)
{
	int x0, y0;
	exGcd(a, m, x0, y0);
	return (x0 * b % m + m) % m;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, k;
	scanf("%d%d", &n, &k);
	int m = k / n; k %= n;
	int p = solve(k, n - 1, n);
	a[n - 1] = b[0] = 1;
	for(int i = p, pre = 0; i != 0; pre = i, i = (i + p) % n)
		a[i] = b[pre], b[i] = (i == n - 1 ? 0 : a[i]);
	for(int i = 0; i < n; i ++)
		printf("%d ", a[i] + m);
}
