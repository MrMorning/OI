#include <cstdio>
#include <queue>
#include <cstring>
#define MAXN 1010
#define MAXM 10010
using std::priority_queue;
struct Vertex
{
	int idx, dist;
	bool operator< (const Vertex& x) const
	{
		return dist > x.dist;
	}
	Vertex(int _idx, int _dist):idx(_idx), dist(_dist){};
};

struct Edge
{
	int s, t, w, next;
	Edge(){};
	Edge(int _s, int _t, int _w, int _next):s(_s), t(_t), w(_w), next(_next){};
} edge[MAXM];
int edgeCnt, n, m, begin[MAXN], st, en;
int cnt[MAXN][2], phi[MAXN];
bool inQueue[MAXN][2];

void addEdge(int s, int t, int w)
{
	edgeCnt ++;
	edge[edgeCnt] = Edge(s, t, w, begin[s]);
	begin[s] = edgeCnt;
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
	{
		scanf("%d %d\n", &n, &m);
		edgeCnt = 0;
		memset(begin, 0, sizeof(begin));
		for(int i = 1, a, b, l; i <= m; i++)
		{
			scanf("%d %d %d\n", &a, &b, &l);
			addEdge(a, b, l);
		}
		scanf("%d %d\n", &st, &en);
		memset(phi, 0x3f, sizeof(phi));
		priority_queue<Vertex> q;
		q.push(Vertex(st, 0));
		phi[st] = 0;
		while(q.size())
		{
			Vertex u = q.top(); q.pop();
			for(int now = begin[u.idx]; now; now = edge[now].next)
			{
				int v = edge[now].t;
				if(phi[v] > phi[u.idx] + edge[now].w)
				{
					phi[v] = phi[u.idx] + edge[now].w;
					q.push(Vertex(v, phi[v]));
				}
			}
		}
		memset(inQueue, 0, sizeof(inQueue));
		memset(cnt, 0, sizeof(cnt));
		q.push(Vertex(st, 0));
		inQueue[st][0] = true;
		cnt[st][0] = 1;
		while(q.size())
		{
			Vertex u = q.top(); q.pop();
			int uLevel = u.dist - phi[u.idx];
			inQueue[u.idx][uLevel] = false;
			for(int now = begin[u.idx]; now; now = edge[now].next)
			{
				int v = edge[now].t;
				int len = u.dist + edge[now].w;
				int vLevel = len - phi[v];
				if(vLevel <= 1)
				{
					cnt[v][vLevel] += cnt[u.idx][uLevel];
					if(! inQueue[v][vLevel])
						q.push(Vertex(v, len)), inQueue[v][vLevel] = true;
				}
			}
		}
		printf("%d\n", cnt[en][0] + cnt[en][1]);
	}
}
