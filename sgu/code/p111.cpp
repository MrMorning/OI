#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int D_MAX = 1010;
struct BigInt
{
	int num[D_MAX], len;
	BigInt()
	{
		memset(num, 0, sizeof(num));
		len = 0;
	}
	BigInt(int x)
	{
		memset(num, 0, sizeof(num));
		len = 0;
		while(x)
			num[len ++] = x % 10, x /= 10;
	}
	void shl(int k)
	{
		len += k;
		for(int i = len - 1; i >= k; i --)
			num[i] = num[i - k];
		for(int i = k - 1; i >= 0; i --)
			num[i] = 0;
	}
};

BigInt plus(const BigInt &A, const BigInt &B)
{/*{{{*/
	static BigInt res;
	res = BigInt();
	res.len = max(A.len, B.len);
	for(int i = 0; i < res.len; i ++)
		res.num[i] = A.num[i] + B.num[i];
	for(int i = 0; i < res.len; i ++)
	{
		res.num[i + 1] += res.num[i] / 10;
		res.num[i] %= 10;
	}
	if(res.num[res.len])
		res.len ++;
	return res;
}/*}}}*/

BigInt minus(const BigInt &A, const BigInt &B)
{/*{{{*/
	static BigInt res;
	res = A;
	for(int i = 0; i < res.len; i ++)
		res.num[i] -= B.num[i];
	for(int i = 0; i < res.len - 1; i ++)
		if(res.num[i] < 0)
			res.num[i] += 10, res.num[i + 1] --;
	for(int i = res.len - 1; i >= 0; i --)
		if(res.num[i] == 0)
			res.len --;
		else
			break;
	if(res.len == 0)
		res.len = 1;
	return res;
}/*}}}*/

BigInt mul(const BigInt &A, int k)
{/*{{{*/
	static BigInt res;
	res = A;
	for(int i = 0; i < res.len; i ++)
		res.num[i] *= k;
	for(int i = 0; i < D_MAX - 1; i ++)
	{
		res.num[i + 1] += res.num[i] / 10;
		res.num[i] %= 10;	
	}
	bool flag = false;
	for(int i = D_MAX - 1; i >= 0; i --)
		if(res.num[i])
		{
			res.len = i + 1;
			flag = true;
			break;
		}
	if(!flag)
		res.len = 1;
	return res;
}/*}}}*/

int compare(const BigInt &A, const BigInt &B)
{/*{{{*/
	if(A.len != B.len)
	{
		if(A.len > B.len)
			return 1;
		else
			return -1;
	}
	else
	{
		for(int i = A.len - 1; i >= 0; i --)
			if(A.num[i] > B.num[i])
				return 1;
			else if(A.num[i] < B.num[i])
				return -1;
		return 0;
	}
}/*}}}*/

char str[1010];
BigInt X, Y, R, P, Q;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s", str);
	X.len = strlen(str);
	for(int i = 0; i < X.len; i ++)
		X.num[X.len - i - 1] = str[i] - '0';
	if(X.len & 1)
		X.len ++;
	int tmp = X.num[X.len - 1] * 10 + X.num[X.len - 2];
	Y.num[0] = (int)sqrt(tmp);
	Y.len = 1;
	R = BigInt(tmp - Y.num[0] * Y.num[0]);
	for(int i = X.len - 3; i > 0; i -= 2)
	{
		R.shl(2);
		R.num[1] = X.num[i], R.num[0] = X.num[i - 1];
		P = mul(Y, 2);
		P.shl(1);
		int t = 0;
		for(int d = 1; d <= 9; d ++)
		{
			P.num[0] = d;
			Q = mul(P, d);
			if(compare(Q, R) != 1)
				t = d;
			else
				break;
		}
		Y.shl(1); Y.num[0] = t;
		P.num[0] = t;
		R = minus(R, mul(P, t));
	}
	for(int i = Y.len - 1; i >= 0; i --)
		printf("%d", Y.num[i]);
}
