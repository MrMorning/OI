/*
 * Date: Mon Jan 31 17:59:39 CST 2011
 * Author: csimstu
 * Problem: poj3613(the shortest path with exactly k edges)
 * Algorithm: DP + Matrix optimalization
 */
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#define INF 0x3f3f3f3f
#define MAXL 201
using std::vector;
using std::map;

struct Matrix
{
	int ele[MAXL][MAXL];
	Matrix()
	{
		memset(ele, 0x3f, sizeof(ele));
	}
} facMatrix[21];
int n;

inline int min(int a, int b)
{
	return a < b ? a : b;
}

Matrix operator* (const Matrix &a, const Matrix &b)
{
	Matrix c;
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				c.ele[i][j] = min(c.ele[i][j], a.ele[i][k] + b.ele[k][j]);
	return c;
}

int main()
{
	freopen("t.in", "r", stdin);
	int k, m, st, en;
	scanf("%d %d %d %d\n", &k, &m, &st, &en);	
	Matrix basicMatrix;
	int idx = 0;
	map<int, int> mapTmp;
	mapTmp.clear();
	for(int i = 1, a, b, len; i <= m; i ++)
	{
		scanf("%d %d %d\n", &len, &a, &b);
		if(mapTmp.find(a) == mapTmp.end())
			mapTmp[a] = ++ idx;
		if(mapTmp.find(b) == mapTmp.end())
			mapTmp[b] = ++ idx;
		basicMatrix.ele[mapTmp[a]][mapTmp[b]] = basicMatrix.ele[mapTmp[b]][mapTmp[a]] = len;
	}
	n = idx;
	facMatrix[1] = basicMatrix;
	for(int i = 2; i <= 20; i ++)
		facMatrix[i] = facMatrix[i - 1] * facMatrix[i - 1];
	int cnt = 0;
	Matrix ansMatrix;
	bool first = true;
	while(k > 0)
	{
		cnt ++;
		if(k & 1)
		{
			if(first)
			{
				ansMatrix = facMatrix[cnt];
				first = false;
			}
			else
				ansMatrix = ansMatrix * facMatrix[cnt];
		}
		k >>= 1;
	}
	printf("%d\n", ansMatrix.ele[mapTmp[st]][mapTmp[en]]);
}
