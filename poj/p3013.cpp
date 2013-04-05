#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#define MAXN 50010
#define MAXM 100010
#define INF 4611686018427387904
using std::cout;
typedef long long ll;
class Queue
{
	int ele[MAXN], closed, open;
	public:
		Queue()
		{
			closed = open = 0;
			memset(ele, 0, sizeof(ele));
		}
		void push(int x)
		{
			closed = (closed + 1) % MAXN;
			ele[closed] = x;
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
}edge[MAXM];
int begin[MAXN], edgeCnt, weight[MAXN];
ll dist[MAXN];
bool inQueue[MAXN];
int testNum, n, m;
void addEdge(int s, int t, int w)
{
	edgeCnt ++;
	edge[edgeCnt].s = s, edge[edgeCnt].t = t, edge[edgeCnt].w = w;
	edge[edgeCnt].next = begin[s];
	begin[s] = edgeCnt;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &testNum);
	while(testNum --)
	{
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i ++)
			scanf("%d", &weight[i]);
		edgeCnt = 0;
		memset(begin, 0, sizeof(begin));
		for(int i = 1, a, b, c; i <= m; i ++)
		{
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
			addEdge(b, a, c);
		}
		Queue q;
		q.push(1);
		for(int i = 1; i <= n; i ++)
			dist[i] = INF;
		inQueue[1] = true;
		dist[1] = 0;
		while(! q.empty())
		{
			int u = q.pop();
			inQueue[u] = false;
			for(int now = begin[u]; now; now = edge[now].next)
			{
				int v = edge[now].t;
				ll tmp = edge[now].w + dist[u];
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
		ll ans = 0;
		bool failed = false;
		for(int i = 1; i <= n; i ++)
			if(dist[i] == INF)
			{
				printf("No Answer\n");
				failed = true;
				break;
			}
			else
				ans += dist[i] * weight[i];
		if(! failed)
			cout << ans << '\n';
	}
}
