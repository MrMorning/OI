#include <cstdio>
#include <cstring>
#define MAXN 21
#define MAXM MAXN * MAXN * 2
#define INF 0x3f3f3f3f

inline int min(int a, int b)
{
	return a < b ? a : b;
}
class Queue
{
	int ele[MAXN], open, closed;
	public:
		Queue()
		{
			open = closed = 0;
			memset(ele, 0, sizeof(ele));
		}
		void push(int u)
		{
			closed = (closed + 1) % MAXN;
			ele[closed] = u;
		}
		int pop()
		{
			open = (open + 1) % MAXN;
			return ele[open];
		}
		bool empty()
		{
			return open == closed;
		}
};

struct Edge
{
	int s, t, w, next;
	Edge(){};
	Edge(int _s, int _t, int _w, int _next):s(_s), t(_t), w(_w), next(_next){};
}edge[MAXM];
int begin[MAXN], edgeCnt;
int n, m, dayNum, f[101], changeFee;
bool inQueue[MAXN], legal[MAXN], fine[MAXN][101];
int dist[MAXN];

void addEdge(int s, int t ,int w)
{
	edgeCnt ++;
	edge[edgeCnt] = Edge(s, t, w, begin[s]);
	begin[s] = edgeCnt;
}

int spfa()
{
	memset(dist, 0x3f, sizeof(dist));
	memset(inQueue, 0, sizeof(inQueue));
	Queue q;
	q.push(1);
	inQueue[1] = true;
	dist[1] = 0;
	while(! q.empty())
	{
		int u = q.pop();
		inQueue[u] = false;
		for(int now = begin[u]; now; now = edge[now].next)
		{
			int v = edge[now].t;
			if(! legal[v])
				continue;
			int tmp = dist[u] + edge[now].w;
			if(tmp < dist[v])
			{
				dist[v] = tmp;
				if(! inQueue[v])
				{
					q.push(v);
					inQueue[v] = true;
				}
			}
		}
	}
	return dist[n];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d\n", &dayNum, &n, &changeFee, &m);
	for(int i = 1, a, b, c; i <= m; i ++)
	{
		scanf("%d%d%d\n", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	memset(fine, 1, sizeof(fine));
	int d;
	scanf("%d\n", &d);
	for(int i = 1, l, r, u; i <= d; i ++)
	{
		scanf("%d%d%d\n", &u, &l, &r);
		for(int j = l; j <= r; j ++)
			fine[u][j] = false;
	}
	memset(f, 0x3f, sizeof(f));
	f[0] = - changeFee;
	for(int i = 1; i <= dayNum; i ++)
		for(int j = 0; j < i; j ++)
		{
			memset(legal, 1, sizeof(legal));
			for(int u = 1; u <= n; u ++)
				for(int k = j + 1; k <= i; k ++)
					if(! fine[u][k])
					{
						legal[u] = false;
						break;
					}
			int tmp = spfa();
			if(tmp != INF)
				f[i] = min(f[i], f[j] + spfa() * (i - j) + changeFee);
		}
	printf("%d\n", f[dayNum]);
}
