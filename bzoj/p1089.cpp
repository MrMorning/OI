#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int D_MAX = 200;

struct BigInt
{
	int num[D_MAX];
	int len;
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
		for(int i = len - 1; i >= 0; i --)
			printf("%d", num[i]);
	}
};

int n, d, c[33], cur;
BigInt f[17];
void dfs(int i)
{
	if(i == n)
	{
		int tmp = 0;
		for(int j = 0; j < n; j ++)
			tmp = max(c[j], tmp);
		if(tmp == cur - 1)
		{
			static BigInt res;
			memset(res.num, 0, sizeof(res.num));
			res.len = 1, res.num[0] = 1;
			for(int j = 0; j < n; j ++)
				res *= f[c[j]];
			f[cur] += res;
		}
		return;
	}

	for(int j = 0; j < cur; j ++)
	{
		c[i] = j;
		dfs(i + 1);
		c[i] = -1;
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &d);
	f[0].len = 1, f[0].num[0] = 1;
	for(cur = 1; cur <= d; cur ++)
		dfs(0);
	f[d].output();
}
