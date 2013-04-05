#include <cstdio>
#include <stack>
using std::stack;
stack<int> stackTmp;
struct Edge
{
	int s, t, next;
} edge[50010];

int dfn[10010], low[10010], begin[10010], index = 0;
int n, m, edgeCnt, compCnt, comp[10010], belong[10010], inDegree[10010];
bool inStack[10010];

inline int min(int a, int b)
{
	return a < b ? a : b;
}

void addEdge(int s, int t)
{
	edgeCnt ++;
	edge[edgeCnt].next = begin[s];
	begin[s] = edgeCnt;
	edge[edgeCnt].s = s;
	edge[edgeCnt].t = t;
}

void dfs(int u)
{
	dfn[u] = low[u] = ++ index;
	stackTmp.push(u);
	inStack[u] = true;
	for(int now = begin[u]; now; now = edge[now].next)
	{
		int v = edge[now].t;
		if(! dfn[v])
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if(inStack[v])
			low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u])
	{
		compCnt ++;
		int v;
		do
		{
			v = stackTmp.top(), stackTmp.pop();
			inStack[v] = false;
			belong[v] = compCnt;
			comp[compCnt] ++;
		}while(v != u);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	for(int i = 1, a, b; i <= m; i ++)
	{
		scanf("%d %d\n", &a, &b);
		addEdge(b, a);
	}
	for(int i = 1; i <= n; i ++)
		if(! dfn[i])
			dfs(i);
	for(int i = 1; i <= edgeCnt; i ++)
		if(belong[edge[i].s] != belong[edge[i].t])
			inDegree[belong[edge[i].t]] ++;
	int j, cnt = 0;
	for(int i = 1; i <= compCnt; i ++)
		if(inDegree[i] == 0)
		{
			cnt ++;
			j = i;
		}
	if(cnt == 1)
		printf("%d\n", comp[j]);
	else
		printf("0\n");
}
