#include <cstdio>

int bino(int n, int k)
{
	static int f[32][32];
	static bool done[32][32];
	if(n < 0 || k < 0)
		return 0;
	if(n == 0)
		return k == 0;
	if(done[n][k])
		return f[n][k];
	done[n][k] = true;
	return f[n][k] = bino(n - 1, k) + bino(n - 1, k - 1);
}

int calc(int n, int k)
{
	int ret = 0;
	static int d[32];
	int nd = 0, now = 0;
	while(n)
		d[nd ++] = n & 1, n >>= 1;
	for(int i = nd - 1; i >= 0; i --)
		if(d[i])
			ret += bino(i, k - now), now ++;
	return ret + (k == now);
}

int solve(int l, int r, int k)
{
	if(l > r)
		return 0;
	return calc(r, k) - (l == 0 ? 0 : calc(l - 1, k));
}

int main()
{
	freopen("t.in", "r", stdin);
	int m, n, k;
	scanf("%d%d%d", &m, &n, &k);
	int one_cnt = -1, acc = 0, pre = 0;
	for(; acc < k; pre = acc, acc += solve(m, n, ++ one_cnt));
	int rank = k - pre, downlim = (1 << one_cnt) - 1;
	int lb = downlim - 1, rb = 10000, mid = (lb + rb) / 2;
	while(lb + 1 < rb)
	{
		if(solve(downlim, mid, one_cnt) < rank)
			lb = mid;
		else
			rb = mid;
		mid = (lb + rb) / 2;
	}
	printf("%d\n", rb);
}
