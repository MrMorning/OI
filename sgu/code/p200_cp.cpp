#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

const int NUM_MAX = 31623;

int primeLim, numCnt;
int primeCnt;
int prime[100];
bool mat[100][101];
int freeCnt;
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
	for(int i = 0; i < primeLim; i ++)
	{
		int p;
		bool suc = false;
		while(j < numCnt)
		{
			for(p = i; p < primeLim; p ++)
				if(mat[p][j])
				{
					suc = true;
					break;
				}
			if(suc)
				break;
			j ++;
		}
		if(j >= numCnt)
			break;
		for(int k = 0; k < numCnt + 1; k ++)
			swap(mat[i][k], mat[p][k]);
		for(p = 0; p < primeLim; p ++)
			if(p != i && mat[p][j])
				for(int k = 0; k < numCnt + 1; k ++)
					mat[p][k] ^= mat[i][k];
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
	cout << (1LL << freeCnt) - 1;
}
