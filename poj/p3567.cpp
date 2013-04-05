#include <cstdio>
#include <cstring>
#include <cassert>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

const int N_VTX_MAX = 50000;
const int N_EDGE_MAX = 100000 * 2;
const int INFINITY = 0x3f3f3f3f;

struct Edge
{
	int vtx;
	Edge *next, *inverse;
};

struct MonoQueue
{
	int queue[N_VTX_MAX][2];
	int head, tail;
	MonoQueue()
	{
		head = tail = 0;
	}
	int get_max()
	{
		if(head == tail)
			return -INFINITY;
		else
			return queue[head][1];
	}
	void update(int l)
	{
		while(head < tail && queue[head][0] < l)
			head ++;
	}
	void push(int i, int val)
	{
		while(head < tail && queue[tail - 1][1] <= val)
			tail --;
		queue[tail][0] = i, queue[tail][1] = val;
		tail ++;
		assert(tail < N_VTX_MAX);
	}
};

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];

int low[N_VTX_MAX], dfn[N_VTX_MAX];
int f[N_VTX_MAX];
int cycle[N_VTX_MAX];
int ans = 0;
int n_vtx, n_edge, dfn_idx;

Edge *make_edge(int u, int v);
void add_edge(int u, int v);
void read_data();
void dfs(int u, int p);
void find_BCC();
void work_on_cycle(int n, int &ret);

Edge *make_edge(int u, int v)
{
	Edge *e = &edge[n_edge ++];
	assert(n_edge < N_EDGE_MAX);
	e->vtx = v, e->next = begin[u], begin[u] = e;
	return e;
}
void add_edge(int u, int v)
{
	Edge *e1 = make_edge(u, v),
		 *e2 = make_edge(v, u);
	e1->inverse = e2, e2->inverse = e1;
}
void read_data()
{
	int m, k, u, v;
	scanf("%d%d", &n_vtx, &m);
	while(m --)
	{
		scanf("%d", &k);
		u = -1;
		while(k --)
		{
			scanf("%d", &v);
			v --;
			if(u != -1)
				add_edge(u, v);
			u = v;
		}
	}
}
void find_BCC()
{
	for(int i = 0; i < n_vtx; i ++)
		dfn[i] = -1, f[i] = 0;
	for(int i = 0; i < n_vtx; i ++)
		if(dfn[i] == -1)
			dfs(i, -1);
}
void dfs(int u, int p)
{
	static int stack[N_VTX_MAX];
	static int top = 0;
	stack[top ++] = u;
	dfn[u] = low[u] = dfn_idx ++;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(v == p)
			continue;
		if(dfn[v] != -1)
			low[u] = MIN(low[u], dfn[v]);
		else
		{
			dfs(v, u);
			low[u] = MIN(low[u], low[v]);
			if(low[v] >= dfn[u])
			{
				int cycle_cnt = 0;
				while(1)
				{
					assert(top);
					int w = stack[top - 1];
					cycle[cycle_cnt ++] = w;
					if(w == u)
						break;
					top --;
				}
				int tmp = 0;
				work_on_cycle(cycle_cnt, tmp);
				ans = MAX(ans, tmp + f[u]);
				f[u] = MAX(f[u], tmp);
			}
		}
	}
}
void work_on_cycle(int n, int &ret)
{
	MonoQueue MQ;
	for(int i = 0; i < n; i ++)
	{
		MQ.update(i - n / 2);
		ans = MAX(ans, MQ.get_max() + f[cycle[i]] + i);
		MQ.push(i, f[cycle[i]] - i);
	}
	MQ.update(n);//empty the queue
	assert(MQ.head == MQ.tail);
	for(int i = 0; i < n; i ++)
	{
		//no update
		ans = MAX(ans, MQ.get_max() + f[cycle[i]] + n - i);
		int j = i - n / 2;
		if(j >= 0)
			MQ.push(j, f[cycle[j]] + j);
	}
	for(int i = 0; i < n - 1; i ++)
		ret = MAX(ret, MIN(n - 1 - i, n - (n - 1 - i)) + f[cycle[i]]);
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	read_data();
	find_BCC();
	printf("%d\n", ans);
}
