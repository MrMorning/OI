#include <cstdio>
#include <cstring>
#include <string>
#define MAX_LEN 10000
using std::string;
inline int max(int a, int b)
{
	return a > b ? a : b;
}

const int tenPow[4] = {1, 10, 100, 1000};

struct BigInt
{
	int num[MAX_LEN], len;
	BigInt()
	{
		memset(num, 0, sizeof(num));
		len = 0;
	};
	BigInt(const string &str)
	{
		memset(num, 0, sizeof(num));
		int tmpNum[100];
		int sLen = str.length();
		len = (sLen - 1) / 4 + 1;
		for(int i = 1; i <= sLen; i ++)
			tmpNum[i] = str[sLen - i] - '0';
		for(int i = 1; i <= sLen; i ++)
			num[1 + (i - 1) / 4] += tenPow[(i - 1) % 4] * tmpNum[i];
	}
	string toString()
	{
		int sLen = len * 4;
		string str(sLen, '0');
		for(int i = len; i >= 1; i --)
			for(int k = 0; k <= 3; k ++)
				str[sLen - ((i - 1) * 4 + k) - 1] = num[i] / tenPow[k] % 10 + '0';
		int i = 0;
		while(str[i] == '0' && i < str.length() - 1)
			i ++;
		return str.substr(i, sLen - i);
	}
};

BigInt operator+(const BigInt &a, const BigInt &b)
{
	BigInt c;
	c.len = max(a.len, b.len);
	for(int i = 1; i <= c.len; i ++)
		c.num[i] = a.num[i] + b.num[i];
	for(int i = 1; i <= c.len; i ++)
	{
		c.num[i + 1] += c.num[i] / 10000;
		c.num[i] %= 10000;
	}
	if(c.num[c.len + 1])
		c.len ++;
	return c;
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
	BigInt c;
	for(int i = 1; i <= a.len; i ++)
		for(int j = 1; j <= b.len; j ++)
		{
			c.num[i + j] += c.num[i + j - 1] / 10000;
			c.num[i + j - 1] %= 10000;
			c.num[i + j - 1] += a.num[i] * b.num[j];
		}
	for(int i = 1; i < MAX_LEN - 1; i ++)
	{
		c.num[i + 1] += c.num[i] / 10000;
		c.num[i] %= 10000;
	}
	for(int i = MAX_LEN; i >= 1; i --)
		if(c.num[i] != 0)
		{
			c.len = i;
			break;
		}
	if(c.len == 0)
		c.len = 1;
	return c;
}
BigInt mul(const BigInt &x, int k)
{
	BigInt y;
	for(int i = 1; i <= x.len; i ++)
	{
		long long tmp = (long long)x.num[i] * k;
		y.num[i + 1] += tmp / 10000;
		y.num[i] += tmp % 10000;
	}
	for(int i = 1; i < MAX_LEN - 1; i ++)
	{
		y.num[i + 1] += y.num[i] / 10000;
		y.num[i] %= 10000;
	}
	for(int i = MAX_LEN; i >= 1; i --)
		if(y.num[i] != 0)
		{
			y.len = i;
			break;
		}
	if(y.len == 0)
		y.len = 1;
	return y;
}

BigInt div(const BigInt &x, int k)
{
	int i = x.len, cnt = 0;
	BigInt ans;
	while(i > 0)
	{
		while(k > cnt)
		{
			cnt = cnt * 10000 + x.num[i];
			i --;
		}
		ans.num[i + 1] = cnt / k;
		cnt = cnt % k;
	}
	for(int i = MAX_LEN; i >= 1; i --)
		if(ans.num[i] != 0)
		{
			ans.len = i;
			break;
		}
	if(ans.len == 0)
		ans.len = 1;
	return ans;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, c[1001], k = 0;
	scanf("%d\n", &n);
	int left = n;
	for(int i = 1, t; i <= n; i ++)
	{
		scanf("%d\n", &t);
		if(t != -1)
			c[++ k] = t - 1, left -= t - 1;
	}
	left -= 2;
	n -= 2;
	
	BigInt ans("1");
	for(int i = left + 1; i <= n; i ++)
		ans = mul(ans, i);
	for(int i = 1; i <= k; i ++)
		for(int j = 2; j <= c[i]; j ++)
			ans = div(ans, j);
	for(int i = 1; i <= left; i ++)
		ans = mul(ans, n + 2 - k);
	printf("%s\n", ans.toString().c_str());
	/*int ans = 1;
	for(int i = left + 1; i <= n; i ++)
		ans *= i;
	for(int i = 1; i <= k; i ++)
		for(int j = 2; j <= c[i]; j ++)
			ans /= j;
	for(int i = 1; i <= left; i ++)
		ans *= n + 2 - k;
	printf("%d\n", ans);*/
}
