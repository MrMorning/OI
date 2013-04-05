#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD(x) (((x) % 1000000007 + 1000000007) % 1000000007)
typedef long long ll;

using namespace std;

const int D_MAX = 101;
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

	void read()
	{
		static char str[D_MAX + 10];
		scanf("%s", str);
		len = strlen(str);
		for(int i = 0; i < len; i ++)
			num[i] = str[len - i - 1] - '0';
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
}; 

int f[101][10][1001];
int pow[101];

inline void increase(int &a, int b)
{
	a = MOD(a + b);
}

void init(int x)
{
	f[0][0][0] = 1;
	for(int i = 0; i < 100; i ++)
		for(int j = 0; j < x; j ++)
			for(int k = 0; k <= 1000; k ++)
				if(f[i][j][k])
					for(int d = 0; d < 10; d ++)
					{
						if(k + d > 1000)
							continue;
						increase(f[i + 1][(10 * j + d) % x][k + d], f[i][j][k]);
					}
}

int solve(const BigInt &n, int x, int l, int r)
{
	int sumOfDigits = 0, modOfDigits = 0;
	int res = 0;
	for(int i = n.len - 1; i >= 0; i --)
	{
		for(int j = 0; j < n.num[i]; j ++)
		{
			int sd = sumOfDigits + j, sm = (modOfDigits * 10 + j) % x;
			for(int k = l; k <= r; k ++)
				if(k - sd >= 0)
					increase(res, f[i][(x - ((ll)pow[i] * sm % x)) % x][k - sd]);
		}
		sumOfDigits += n.num[i];
		modOfDigits = (modOfDigits * 10 + n.num[i]);
	}
	return res;
}

BigInt a, b;
int main()
{
	freopen("t.in", "r", stdin);
	pow[0] = 1;
	for(int i = 1; i <= 100; i ++)
		pow[i] = MOD((ll)pow[i - 1] * 10);
	a.read();
   	b.read();
	b += BigInt(1);
	int x, l, r;
	scanf("%d%d%d", &x, &l, &r);
	init(x);
//	solve(a, x, l, r);
	printf("%d\n", MOD(solve(b, x, l, r) - solve(a, x, l, r)));
}
