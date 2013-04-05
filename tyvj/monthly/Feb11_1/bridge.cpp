#include <cstdio>
#include <cstring>
#define MAXN 1000010
#define MAXM 4 * MAXN
class Queue
{
	private:
		int ele[MAXN], closed, open;
	public:
		Queue()
		{
			memset(ele, 0, sizeof(ele));
			closed = open = 0;
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
} q;

struct Edge
{
	int s, t, w, next;
	Edge(){};
	Edge(int _s, int _t, int _w, int _next): s(_s), t(_t), w(_w), next(_next){};
} edge[MAXM];
int edgeCnt, begin[MAXN], dist[MAXN];
int n, st, en;
bool inQueue[MAXN];

void addEdge(int s, int t , int w)
{
	edgeCnt ++;
	edge[edgeCnt] = Edge(s, t, w, begin[s]);
	begin[s] = edgeCnt;
	edgeCnt ++;
	edge[edgeCnt] = Edge(t, s, 0, begin[t]);
	begin[t] = edgeCnt;
}

int spfa()
{
	memset(dist, 0x3f, sizeof(dist));
	dist[st] = 0;
	inQueue[st] = true;
	q.push(st);
	while(! q.empty())
	{
		int u = q.pop();
		inQueue[u] = false;
		for(int now = begin[u]; now; now = edge[now].next)
		{
			int v = edge[now].t;
			int tmp = dist[u] + edge[now].w;
			if(tmp < dist[v])
			{
				dist[v] = tmp;
				if(! inQueue[v])
					q.push(v), inQueue[v] = true;
			}
		}
	}
	return dist[en];
}

int main()
{
	freopen("bridge.in", "r", stdin);
	//freopen("bridge.out", "w", stdout);
	scanf("%d\n", &n);
	n --;
	st = 2 * n + 1, en = st + 1; 
	for(int i = 1, t; i <= n; i ++)
	{
		scanf("%d", &t);
		addEdge(2 * i - 1, en, t);
	}
	for(int i = 1, t; i <= n; i ++)
	{
		scanf("%d", &t);
		addEdge(st, 2 * i, t);
	}
	for(int i = 1, t; i <= n; i ++)
	{
		scanf("%d", &t);
		addEdge(2 * i, 2 * i - 1, t);
	}
	int t;
	scanf("%d", &t); 
	addEdge(st, 2, t);
	for(int i = 1, t; i < n; i ++)
	{
		scanf("%d", &t);
		addEdge(2 * i - 1, 2 * i - 1 + n + 1, t);
	}
	scanf("%d", &t);
	addEdge(2 * n - 1, en, t);
	printf("%d\n", spfa());
}
