#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int D_MAX = 10100;
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

BigInt mul(const BigInt &A, const BigInt &B)
{
	static BigInt res;
	res = BigInt();
	for(int i = 0; i < A.len; i ++)
		for(int j = 0; j < B.len; j ++)
			res.num[i + j] += A.num[i] * B.num[j];
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
}

BigInt pow(BigInt A, int n)
{
	static BigInt res;
	if(n & 1)
		res = A;
	else
	{
		res = BigInt();
		res.num[0] = 1;
		res.len = 1;
	}

	for(n >>= 1; n; n >>= 1)
	{
		A = mul(A, A);
		if(n & 1)
			res = mul(res, A);
	}
	return res;
}

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

BigInt A, B, res;
int a, b;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &a, &b);
	A = pow(BigInt(a), b), B = pow(BigInt(b), a);
	bool flag = false;
	if(compare(A, B) == -1)
		flag = true, swap(A, B);
	else if(compare(A, B) == 0)
	{
		printf("0\n");
		return 0;
	}
	res = minus(A, B);
	if(flag)
		printf("-");
	for(int i = res.len - 1; i >= 0; i --)
		printf("%d", res.num[i]);
}
