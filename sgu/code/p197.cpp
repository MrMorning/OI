#include <cstdio>
#include <cstdio>
#include <cstring>
#include <cassert>
const int D_MAX = 110;
int modNum;

struct Matrix
{
	int ele[32][32], n, m;
};

Matrix mul(const Matrix &A, const Matrix &B)
{
	static Matrix res;
	memset(res.ele, 0, sizeof(res.ele));
	assert(A.m == B.n);
	res.n = A.n, res.m = B.m;
	for(int i = 0; i < res.n; i ++)
		for(int j = 0; j < res.m; j ++)
			for(int k = 0; k < A.m; k ++)
				res.ele[i][j] = (res.ele[i][j] + A.ele[i][k] * B.ele[k][j]) % modNum;
	return res;
}

struct BigInt
{
	int num[D_MAX];
	void read()
	{
		static char str[300];
		scanf("%s", str);
		int len = strlen(str);
		for(int i = 0; i < len; i ++)
			num[len - i - 1] = str[i] - '0';
	}
	void div2()
	{
		for(int i = D_MAX - 1, r = 0; i >= 0; i --)
			if(num[i] != 0)
			{
				for(int j = i; j >= 0; j --)
				{
					r += num[j];
					num[j] = r >> 1;
					r = (r - num[j] * 2) * 10;
				}
				return;
			}
	}
	bool isZero()
	{
		for(int i = 0; i < D_MAX; i ++)
			if(num[i])
				return false;
		return true;
	}

	bool odd()
	{
		return num[0] & 1;
	}

	void minus1()
	{
		for(int i = D_MAX - 1; i >= 0; i --)
			if(num[i] != 0)
			{
				num[0] -= 1;
				for(int j = 0; j < i; j ++)
				{
					if(num[j] < 0)
					{
						num[j + 1] --;
						num[j] += 10;
					}
				}
				return;
			}
	}
};

BigInt n;
Matrix transMat, resMat, baseMat;
int m;
int main()
{
	freopen("t.in", "r", stdin);
	n.read();
	n.minus1();
	scanf("%d%d", &m, &modNum);
	int upperlim = 1 << m;
	transMat.n = transMat.m = upperlim;
	for(int i = 0; i < upperlim; i ++)
		for(int j = 0; j < upperlim; j ++)
		{
			bool suc = true;
			for(int k = 0; k < m - 1; k ++)
			{
				int t = (i & (1 << k)) > 0;
				suc &= !((((i & (1 << (k + 1))) > 0) == t) 
						&& (((j & (1 << k)) > 0) == t) &&
						(((j & (1 << (k + 1))) > 0) == t));
			}
			transMat.ele[i][j] = suc;
		}
	baseMat.n = upperlim, baseMat.m = 1;
	for(int i = 0; i < upperlim; i ++)
		baseMat.ele[i][0] = 1;


	if(n.odd())
		resMat = transMat;
	else
	{
		resMat.n = resMat.m = upperlim;
		for(int i = 0; i < upperlim; i ++)
			resMat.ele[i][i] = 1;
	}

	n.div2();
	while(!n.isZero())
	{
		transMat = mul(transMat, transMat);
		if(n.odd())
			resMat = mul(resMat, transMat);
		n.div2();
	}

	baseMat = mul(resMat, baseMat);
	int ans = 0;
	for(int i = 0; i < upperlim; i ++)
		ans = (ans + baseMat.ele[i][0]) % modNum;
	printf("%d\n", ans);
}
