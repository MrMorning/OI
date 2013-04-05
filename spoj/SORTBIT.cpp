#include <cstdio>
#include <algorithm>
using namespace std;
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

int calc(uint n, int k)
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

int solve(uint l, uint r, int k)
{
	return calc(r, k) - calc(l - 1, k);
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
	{
		uint m, n; int k;
		scanf("%u%u%d", &m, &n, &k);
		if(m == 0)
		{
			if(k == 1)
			{
				printf("0\n");
				return 0;
			}
			m = 1, k --;
		}
		int one_cnt = -1;
		int acc = 0, pre = 0;
		for(; acc < k; pre = acc, acc += solve(m, n, ++ one_cnt));
		int rank = k - pre;//ERROR!
		uint lb = m - 1, rb = n;
		//(lb, rb]
		while(lb + 1 < rb)
		{
			uint mid = ((unsigned long long)lb + rb) / 2;
			if(solve(m, mid, one_cnt) < rank)
				lb = mid;
			else
				rb = mid;
		}
		printf("%d\n", (int)rb);
	}
}
