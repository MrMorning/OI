#include <cstdio>
#include <cstring>
#define MAXN 400010
#define MAXM 400010
struct Edge
{
	int s, t, next;
	Edge(){};
	Edge(int _s, int _t, int _next):s(_s), t(_t), next(_next){};
}edge[MAXM];
int edgeCnt, begin[MAXN], destroy[MAXN], n, m, k;
int p[MAXN], rank[MAXN], ans[MAXN];
bool safe[MAXN];

void makeSet(int i)
{
	p[i] = i;
	rank[i] = 0;
}

int findSet(int i)
{
	if(i != p[i])
		p[i] = findSet(p[i]);
	return p[i];
}

void combine(int a, int b)
{
	a = findSet(a), b = findSet(b);
	if(a == b)
		return;
	if(rank[a] < rank[b])
		p[a] = b;
	else
	{
		p[b] = a;
		if(rank[a] == rank[b])
			rank[a] ++;
	}
}

void addEdge(int s, int t)
{
	edgeCnt ++;
	edge[edgeCnt] = Edge(s, t, begin[s]);
	begin[s] = edgeCnt;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d\n", &n, &m);
	for(int i = 1, a, b; i <= m; i ++)
	{
		scanf("%d%d\n", &a, &b);
		a ++, b ++;
		addEdge(a, b), addEdge(b, a);
	}
	scanf("%d\n", &k);
	memset(safe, 0xff, sizeof(safe));
	for(int i = 1; i <= k; i ++)
	{
		scanf("%d\n", &destroy[i]);
		destroy[i] ++;
		safe[destroy[i]] = false;
	}
	int connectCnt = 0;
	for(int i = 1; i <= n; i ++)
		if(safe[i])
			makeSet(i), connectCnt ++;
	for(int i = 1; i <= n; i ++)
		if(safe[i])
			for(int now = begin[i]; now; now = edge[now].next)
				if(safe[edge[now].t] && findSet(i) != findSet(edge[now].t))
					combine(i, edge[now].t), connectCnt --;
	ans[k + 1] = connectCnt;
	for(int i = k; i >= 1; i --)
	{
		int u = destroy[i];
		safe[u] = true;
		makeSet(u);
		connectCnt ++;
		for(int now = begin[u]; now; now = edge[now].next)
			if(safe[edge[now].t] && findSet(u) != findSet(edge[now].t))
				combine(u, edge[now].t), connectCnt --;
		ans[i] = connectCnt;
	}
	for(int i = 1; i <= k + 1; i ++)
		printf("%d\n", ans[i]);
}
