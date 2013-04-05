#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int D_MAX = 70;
struct BigInt
{
	short num[D_MAX];
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
	void output()
	{
		if(len == 0)
			printf("0\n");
		else
			for(int i = len - 1; i >= 0; i --)
				printf("%d", num[i]);
	}
} f[2][21][21][21];

BigInt operator* (const BigInt &A, int k)
{
	static BigInt res;
	res = A;
	for(int i = 0; i < res.len; i ++)
		res.num[i] *= k;
	for(int i = 0; i < D_MAX - 1; i ++)
	{
		res.num[i + 1] += res.num[i] / 10;
		res.num[i] %= 10;
	}
	for(int i = D_MAX - 1; i >= 0; i --)
		if(res.num[i])
		{
			res.len = i + 1;
			return res;
		}
	res.len = 0;
	return res;
}

int n, m, w, h, lim;
BigInt res;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d%d", &n, &m, &w, &h, &lim);
	if(lim > n + m)
	{
		printf("0\n");
		return 0;
	}
	if(w == 0 && h == 0 && n < m)
		n = m;
	if(w + m <= n && h + m <= n)
		m = 0;
	if(w > n || h > n)
		w = h = n;
	f[0][0][0][0] = 1;
	if(w + m < n)
		w = n - m;
	if(h + m < n)
		h = n - m;
	for(int i = 1; i <= h + m; i ++)
	{
		if(i <= h + m - n)
			for(int j = 0; j < 1; j ++)
				for(int k = 0; k <= min(n - w, lim); k ++)
					for(int l = 0; l <= min(w + m - n, lim - k); l ++)
					{
						f[i & 1][j][k][l] = f[(i - 1) & 1][j][k][l];
						if(k)
							f[i & 1][j][k][l] += f[(i - 1) & 1][j][k - 1][l] * (n - w - (k - 1));
						if(l)
							f[i & 1][j][k][l] += f[(i - 1) & 1][j][k][l - 1] * (w + m - n - (l - 1));
					}
		else if(i <= m)
			for(int j = 0; j <= min(w, lim); j ++)
				for(int k = 0; k <= min(n - w, lim - j); k ++)
					for(int l = 0; l <= min(w + m - n, lim - j - k); l ++)
					{
						f[i & 1][j][k][l] = f[(i - 1) & 1][j][k][l];
						if(j)
							f[i & 1][j][k][l] += f[(i - 1) & 1][j - 1][k][l] * (w - (j - 1));
						if(k)
							f[i & 1][j][k][l] += f[(i - 1) & 1][j][k - 1][l] * (n - w - (k - 1));
						if(l)
							f[i & 1][j][k][l] += f[(i - 1) & 1][j][k][l - 1] * (w + m - n - (l - 1));
					}
		else
			for(int j = 0; j <= min(w, lim); j ++)
				for(int k = 0; k <= min(n - w, lim - j); k ++)
					for(int l = 0; l <= min(w + m - n, lim - j - k); l ++)
					{
						f[i & 1][j][k][l] = f[(i - 1) & 1][j][k][l];
						if(j)
							f[i & 1][j][k][l] += f[(i - 1) & 1][j - 1][k][l] * (w - (j - 1));
						if(k)
							f[i & 1][j][k][l] += f[(i - 1) & 1][j][k - 1][l] * (n - w - (k - 1));
					}
	}
	for(int j = 0; j <= min(w, lim); j ++)
		for(int k = 0; k <= min(n - w, lim - j); k ++)
			res += f[(m + h) & 1][j][k][lim - j - k];
	res.output();
}
