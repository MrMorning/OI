#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

bool e[5010][5010];
int nv;
int prev[5010];
int dfn[5010], low[5010];
int seq[5010], seqCnt;
int stk[5010];
int scc[5010], sccCnt;
int belong[5010];
int top;
bool vis[5010], inStk[5010];
bool found;

void dfs(int u, int term)
{
	if(found)
		return;
	vis[u] = true;
	for(int v = 0; v < nv; v ++)
		if(e[u][v])
		{
			prev[v] = u;
			if(!vis[v])
				dfs(v, term);
			else if(v == term)
			{
				found = true;
				return;
			}
		}
}

void tarjan(int u)
{
	static int idx = 0;
	dfn[u] = low[u] = idx ++;
	stk[top ++] = u;
	inStk[u] = true;
	for(int v = 0; v < nv; v ++)
		if(e[u][v])
		{
			if(dfn[v] == -1)
				tarjan(v), low[u] = min(low[u], low[v]);
			else if(inStk[v])
				low[u] = min(low[u], dfn[v]);
		}
	if(low[u] == dfn[u])
	{
		while(1)
		{
			int x = stk[-- top];
			inStk[x] = false;
			scc[sccCnt] ++;
			belong[x] = sccCnt;
			if(x == u)
				break;
		}
		sccCnt ++;
	}
}

int main()
{
//	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	for(int i = 0; i < nv; i ++)
	{
		static char str[5010];
		scanf("%s", str);
		for(int j = 0; j < nv; j ++)
			e[i][j] = str[j] == '1';
	}

	bool flag = false;
	int i;
	memset(dfn, -1, sizeof(dfn));
	for(i = 0; i < nv; i ++)
		if(dfn[i] == -1)
			tarjan(i);
	for(i = 0; i < nv; i ++)
		if(scc[belong[i]] > 1)
		{
			flag = true;
			break;
		}
	if(!flag)
		printf("-1\n");
	else
	{
		memset(prev, -1, sizeof(prev));
		dfs(i, i);
		assert(found);
		int j = i;
		while(1)
		{
			seq[seqCnt ++] = i;
			i = prev[i];
			if(i == j)
				break;
		}
		assert(seqCnt >= 3);
		for(int k = seqCnt - 1; k >= 2; k --)
		{
			if(e[i][seq[k]] && e[seq[k - 1]][i])
			{
				printf("%d %d %d\n", i + 1, seq[k] + 1, seq[k - 1] + 1);
				assert(e[seq[k]][seq[k - 1]]);
				return 0;
			}
		}
		assert(0);
	}
}
