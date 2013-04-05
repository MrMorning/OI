#include <cstdio>
#include <cstring>
#include <queue>
#define MAX_VAL 20000
#define MAX_VERTEX_NUM 50011
#define MAX_EDGE_NUM 100011

using std::queue;

inline int min(int a, int b)
{
	return a < b ? a : b;
}

struct Edge
{
	int s, t, w, next;
	Edge(){};
	Edge(int _s, int _t, int _w, int _next):s(_s), t(_t), w(_w), next(_next){};
} edge[MAX_EDGE_NUM];
int edgeCnt = 0;

int n, m, f[MAX_VERTEX_NUM], begin[MAX_VERTEX_NUM];
bool inQ[MAX_VERTEX_NUM];

void addEdge(int a, int b, int c)
{
	edgeCnt ++;
	edge[edgeCnt] = Edge(a, b, c, begin[a]);
	begin[a] = edgeCnt;
}

bool spfa(int initVal)
{
	queue<int> q;
	memset(f, -0x3f, sizeof(f));
	memset(inQ, 0, sizeof(inQ));
	f[1] = initVal;
	q.push(1);
	inQ[1] = true;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		inQ[u] = false;
		for(int now = begin[u]; now; now = edge[now].next)
		{
			int v = edge[now].t;
			int tmp = min(MAX_VAL, f[u] * 2 + edge[now].w);
			if(tmp > 0 && tmp > f[v])
			{
				f[v] = tmp;
				if(! inQ[v])
					q.push(v), inQ[v] = true;
			}
		}
	}
	return f[n] > 0;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	for(int i = 1, a, b, c; i <= m; i ++)
	{
		scanf("%d %d %d\n", &a, &b, &c);
		addEdge(a, b, c);
	}
	int l = 1, r = MAX_VAL, mid = (l + r) / 2;
	while(l < r)
	{
		if(spfa(mid))
			r = mid;
		else
			l = mid + 1;
		mid = (l + r) / 2;
	}
	printf("%d\n", l);
}
