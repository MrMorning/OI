#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int V_MAX = 100;
const int oo = 0x3f3f3f3f;
int match[V_MAX], next[V_MAX], lx[V_MAX], ly[V_MAX];
bool visX[V_MAX], visY[V_MAX], isHead[V_MAX];
int cost[V_MAX][V_MAX];
int slack[V_MAX];
int nVtx, nEdge, nTmp, tmp[V_MAX];

bool aug(int u)
{
	visX[u] = true;
	for(int v = 0; v < nVtx; v ++)
		if(!visY[v])
		{
			int t = lx[u] + ly[v] - cost[u][v];
			if(t == 0)
			{
				visY[v] = true;
				if(match[v] == -1 || aug(match[v]))
				{
					match[v] = u;
					return true;
				}
			}
			else
				slack[v] = min(slack[v], t);
		}
	return false;
}

void KM()
{
	memset(match, -1, sizeof(match));
	memset(ly, 0, sizeof(ly));
	for(int i = 0; i < nVtx; i ++)
	{
		lx[i] = -oo;
		for(int j = 0; j < nVtx; j ++)
			if(cost[i][j] > lx[i])
				lx[i] = cost[i][j];
	}

	for(int u = 0; u < nVtx; u ++)
	{
		for(int v = 0; v < nVtx; v ++)
			slack[v] = oo;
		while(1)
		{
			memset(visX, 0, sizeof(visX));
			memset(visY, 0, sizeof(visY));
			if(aug(u))
				break;
			int delta = oo;
			for(int i = 0; i < nVtx; i ++)
				if(!visY[i])
					delta = min(delta, slack[i]);
			for(int i = 0; i < nVtx; i ++)
			{
				if(visX[i])
					lx[i] -= delta;
				if(visY[i])
					ly[i] += delta;
				else
					slack[i] -= delta;
			}
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nVtx, &nEdge);
	for(int i = 0; i < nVtx; i ++)
		for(int j = 0; j < nVtx; j ++)
			cost[i][j] = -oo;
	for(int i = 0; i < nEdge; i ++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		cost[-- u][-- v] = -w;
	}

	KM();
	int pathCover = 0, totalCost = 0;
	memset(next, -1, sizeof(next));
	memset(isHead, -1, sizeof(isHead));
	for(int i = 0; i < nVtx; i ++)
		if(lx[match[i]] + ly[i] == -oo)
			pathCover ++;
		else
		{
			totalCost += -(lx[match[i]] + ly[i]), next[match[i]] = i;
			isHead[i] = false;
		}
	printf("%d %d\n", pathCover, totalCost);
	for(int i = 0; i < nVtx; i ++)
		if(isHead[i])
		{
			nTmp = 0;
			for(int x = i; x != -1; x = next[x])
				tmp[nTmp ++] = x;
			printf("%d", nTmp);
			for(int j = 0; j < nTmp; j ++)
				printf(" %d", tmp[j] + 1);
			printf("\n");
		}
}
