#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 20;

const int D_MAX = 250;

struct BigInt
{
	int num[D_MAX];
	int len;

	BigInt()
	{
		len = 1;
		memset(num, 0, sizeof(num));
	}
	BigInt(int x)
	{
		len = 0;
		memset(num, 0, sizeof(num));
		while(x)
			num[len ++] = x % 10, x /= 10;
	}

	void operator+= (const BigInt &x)
	{
		len = max(len, x.len);
		for(int i = 0; i < len; i ++)
			num[i] += x.num[i];
		for(int i = 0; i < len; i ++)
			num[i + 1] += num[i] / 10, num[i] %= 10;
		if(num[len])
			len ++;
	}
	void operator-= (const BigInt &x) //assume *this > x
	{
		for(int i = 0; i < len; i ++)
		{
			num[i] -= x.num[i];
			if(num[i] < 0)
				num[i] += 10, num[i + 1] --;
		}
		for(int i = len - 1; i >= 0; i --)
			if(num[i])
			{
				len = i + 1;
				break;
			}
	}
	void operator*= (const BigInt &x)
	{
		static int tmp[D_MAX];
		memset(tmp, 0, sizeof(tmp));
		for(int i = 0; i < len; i ++)
			for(int j = 0; j < x.len; j ++)
				tmp[i + j] += num[i] * x.num[j];
		int upperlim = len + x.len;
		for(int i = 0; i < upperlim; i ++)
			tmp[i + 1] += tmp[i] / 10, tmp[i] %= 10;
		len = 0;
		for(int i = 0; i < upperlim; i ++)
			if(tmp[i])
				len = i + 1;
		memcpy(num, tmp, sizeof(int) * len);
	}

	void operator/= (int k)
	{
		static BigInt res;
		static int tmp[D_MAX];

		memset(tmp, 0, sizeof(tmp));
		int nt = 0;

		res.len = 0;
		memset(res.num, 0, sizeof(res.num));
		int r = 0;
		for(int i = len - 1; i >= 0; i --)
		{
			r = r * 10 + num[i];
			if(r < k)
			{
				tmp[nt ++] = 0;
				continue;
			}
			tmp[nt ++] = r / k;
			r %= k;
		}
		res.len = nt;
		for(int i = res.len - 1; i >= 0; i --)
			res.num[i] = tmp[res.len - 1 - i];
		for(int i = res.len - 1; i >= 0 && res.num[i] == 0; i --)
			res.len = i;

		*this = res;
	}

	void output()
	{
		for(int i = len - 1; i >= 0; i --)
			printf("%d", num[i]);
	}
} res, pow2[N_MAX * N_MAX + 1];

int f[N_MAX * N_MAX], g[N_MAX * N_MAX];
int n, m;
bool vis[N_MAX * N_MAX];

int f1(int x)
{
	int i = x / m, j = x % m;
	return (i + 1) % n * m + j;
}

int f2(int x)
{
	int i = x / m, j = x % m;
	return i * m + (j + 1) % m;
}

int f3(int x)
{
	int i = x / m, j = x % m;
	return (n - 1 - i) * m + m - 1 - j;
}

int f4(int x)
{
	int i = x / m, j = x % m;
	return j * m + m - 1 - i;
}

void transfer(int a[], int (*f)(int))
{
	static int b[N_MAX * N_MAX];
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
		{
			int t = i * m + j;
			b[t] = a[f(t)];
		}
	memcpy(a, b, sizeof(b));
}

void dfs(int x)
{
	vis[x] = true;
	if(!vis[g[x]])
		dfs(g[x]);
}

void perform(int t1, int t2, int t3, int t4)
{
	memcpy(g, f, sizeof(g));
	for(int i1 = 0; i1 < t1; i1 ++)
		transfer(g, f1);
	for(int i2 = 0; i2 < t2; i2 ++)
		transfer(g, f2);
	for(int i3 = 0; i3 < t3; i3 ++)
		transfer(g, f3);
	for(int i4 = 0; i4 < t4; i4 ++)
		transfer(g, f4);

	int cnt = 0;
	memset(vis, 0, sizeof(vis));
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
		{
			int x = i * m + j;
			if(!vis[x])
			{
				cnt ++;
				dfs(x);
			}
		}
	res += pow2[cnt];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	pow2[0].len = 1, pow2[0].num[0] = 1;
	for(int i = 1; i <= n * m; i ++)
	{
		static BigInt tmp;
		tmp = pow2[i - 1];
		tmp += pow2[i - 1];
		pow2[i] += tmp;
	}
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			f[i * m + j] = i * m + j;
	res = 0;
	for(int t1 = 0; t1 < n; t1 ++)
		for(int t2 = 0; t2 < m; t2 ++)
		{
			if(n != m)
				for(int t3 = 0; t3 < 2; t3 ++)
					perform(t1, t2, t3, 0);
			else
				for(int t4 = 0; t4 < 4; t4 ++)
					perform(t1, t2, 0, t4);

		}
	if(n == m)
		res /= 4 * n * m;
	else
		res /= 2 * n * m;
	res.output();
}
