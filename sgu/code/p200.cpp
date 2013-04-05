#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int NUM_MAX = 31623;

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
        void output()
        {
                for(int i = len - 1; i >= 0; i --)
                        printf("%d", num[i]);
        }
};

int primeLim, numCnt;
int primeCnt;
int prime[100];
bool mat[100][101];
int freeCnt;
BigInt res, tmp, one;
void initPrime()
{
	static bool notPrime[NUM_MAX];
	for(int x = 2; x < NUM_MAX; x ++)
		if(!notPrime[x])
		{
			prime[primeCnt ++] = x;
			if(primeCnt == primeLim)
				return;
			for(int y = x + x; y < NUM_MAX; y += x)
				notPrime[y] = true;
		}
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &primeLim, &numCnt);
	initPrime();
	for(int i = 0, t; i < numCnt; i ++)
	{
		scanf("%d", &t);
		for(int j = 0; j < primeLim; j ++)
			while(t % prime[j] == 0)
			{
				t /= prime[j];
				mat[j][i] ^= 1;
			}
	}

	int j = 0;
	for(int i = 0; i < numCnt; i ++)
	{
		int p = j;
		while(p < primeLim && mat[p][i] == 0)
			p ++;
		if(p == primeLim)
			continue;
		for(int k = 0; k < numCnt + 1; k ++)
			swap(mat[j][k], mat[p][k]);
		for(p = 0; p < primeLim; p ++)
			if(p != j && mat[p][i])
				for(int k = 0; k < numCnt + 1; k ++)
					mat[p][k] ^= mat[j][k];
		j ++;
		if(j == primeLim)
			break;
	}
	freeCnt = numCnt;
	for(int i = 0; i < primeLim; i ++)
		for(int j = 0; j < numCnt; j ++)
		{
			if(mat[i][j])
			{
				freeCnt --;
				break;
			}
		}
	res.len = 1, res.num[0] = 1;
	while(freeCnt --)
	{
		tmp = res;
		res += tmp;
	}
	one.len = 1, one.num[0] = 1;
	res -= one;
	res.output();
}
