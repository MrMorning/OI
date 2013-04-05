#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef unix
	#define LL_FMT "%lld"
#else 
	#define LL_FMT "%I64d"
#endif
typedef long long ll;
using namespace std;
const int D_MAX = 200;

struct BigInt
{
	int num[D_MAX];
	int len;

	BigInt()
	{
		len = 0;
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
		if(len == 0)
			printf("0\n");
		else
			for(int i = len - 1; i >= 0; i --)
				printf("%d", num[i]);
	}
}; 

BigInt operator+ (const BigInt &a, const BigInt &b)
{
	BigInt res = a;
	res += b;
	return res;
}

BigInt operator* (const BigInt &a, const BigInt &b)
{
	BigInt res = a;
	res *= b;
	return res;
}
int n, k;
BigInt f[55][55], g[55][55], res;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &k);
	f[0][0] = g[0][0] = 1;
	for(int i = 1; i <= n; i ++)
	{
		int t = 2 * ((i + 1) / 2) - 1;
		for(int j = 0; j <= t; j ++)
		{
			f[i][j] += f[i - 1][j];
			if(j)
				f[i][j] += BigInt(t - j + 1) * f[i - 1][j - 1];
		}
	}
	for(int i = 1; i <= n; i ++)
	{
		int t = 2 * ((i + 1) / 2);
		for(int j = 0; j <= t; j ++)
		{
			g[i][j] += g[i - 1][j];
			if(j)
				g[i][j] += BigInt(t - j + 1) * g[i - 1][j - 1];
		}
	}
	for(int i = 0; i <= k; i ++)
		if(i <= n && k - i <= n)
			res += f[n][i] * g[n - 1][k - i];
	res.output();
}
