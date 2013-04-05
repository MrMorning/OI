#include <cstring>
#include <cstdio>
#include <algorithm>

const int BUFFER_LEN = 1024 * 1024 * 5;
static char buffer[BUFFER_LEN];
char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
{ \
	ptr ++; \
	if (ptr == buf_end) \
	{ \
		ptr = buffer; \
		buf_end = buffer + fread(buffer, 1, BUFFER_LEN, stdin); \
	} \
}
#define READ_INT(_x_) \
{ \
	while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
	PTR_NEXT(); \
	bool _nega_ = false; \
	if (*ptr == '-') \
	{ \
		_nega_ = true; \
		PTR_NEXT(); \
	} \
	int register _n_ = 0; \
	while (*ptr >= '0' && *ptr <= '9') \
	{ \
		_n_ = _n_ * 10 + *ptr - '0'; \
		PTR_NEXT(); \
	} \
	if (_nega_) \
	_n_ = - _n_; \
	(_x_) = (_n_); \
}

using namespace std;

const int N_VTX_MAX = 100000;
const int N_EDGE_MAX = 1000000;

struct Edge
{
	int vtx, from;
	Edge *next;
};

int mod_num;

namespace pre_work
{
	int n_vtx, n_edge, n_scc;
	int low[N_VTX_MAX], dfn[N_VTX_MAX];
	int cap[N_VTX_MAX];
	int belong[N_VTX_MAX];
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];

	void add_edge(int u, int v);
	void read_data();
	void dfs(int u);
	void main();
}

namespace solve
{
	int n_vtx, n_edge;
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
	bool f_done[N_VTX_MAX];
	int f[N_VTX_MAX], g[N_VTX_MAX];
	int weight[N_VTX_MAX];

	pair<int, int> ep[N_EDGE_MAX];
	int n_ep;

	void add_edge(int u, int v);
	void init();
	int dfs(int u);
	void main();
}
void solve::add_edge(int u, int v)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}
void solve::init()
{
	n_vtx = pre_work::n_scc;
	for(int i = 0; i < pre_work::n_edge; i ++)
	{
		int u = pre_work::edge[i].from,
			v = pre_work::edge[i].vtx;
		if(pre_work::belong[u] != pre_work::belong[v])
			ep[n_ep ++] = make_pair(pre_work::belong[u], pre_work::belong[v]);
	}
	sort(ep, ep + n_ep);
	for(int i = 0; i < n_ep; i ++)
		if(i == 0 || ep[i] != ep[i - 1])
			add_edge(ep[i].first, ep[i].second);
	for(int i = 0; i < n_vtx; i ++)
		weight[i] = pre_work::cap[i];
}

int solve::dfs(int u)
{
	if(f_done[u])
		return f[u];
	f_done[u] = true;
	if(! begin[u])
	{
		f[u] = weight[u];
		g[u] = 1;
	}
	else
	{
		f[u] = 0;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->vtx;
			int tmp = dfs(v) + weight[u];
			if(tmp > f[u])
			{
				f[u] = tmp;
				g[u] = g[v];
			}
			else if(tmp == f[u])
				g[u] = (g[u] + g[v]) % mod_num;
		}
	}
	return f[u];
}

void solve::main()
{
	init();
	int ans = 0, cnt = 0;
	for(int i = 0; i < n_vtx; i ++)
		if(! f_done[i])
			ans = max(ans, dfs(i));
	for(int i = 0; i < n_vtx; i ++)
		if(f[i] == ans)
			cnt = (cnt + g[i]) % mod_num;
	printf("%d\n%d\n", ans, cnt);
}

void pre_work::add_edge(int u, int v)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e, e->from = u;
}

void pre_work::read_data()
{
	int m;
	READ_INT(n_vtx); READ_INT(m); READ_INT(mod_num);
	while(m --)
	{
		int a, b;
		READ_INT(a); READ_INT(b)
		a --, b --;
		add_edge(a, b);
	}
	memset(dfn, -1, sizeof(int) * n_vtx);
	memset(low, -1, sizeof(int) * n_vtx);
}

void pre_work::dfs(int u)
{
	static int idx = 0;
	static int top = 0;
	static int stack[N_VTX_MAX];
	static bool in_stack[N_VTX_MAX];

	dfn[u] = low[u] = idx ++;
	stack[top ++] = u;
	in_stack[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(dfn[v] == -1)
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if(in_stack[v])
			low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		while(1)
		{
			int v = stack[-- top];
			in_stack[v] = false;
			belong[v] = n_scc;
			cap[n_scc] ++;
			if(v == u)
				break;
		}
		n_scc ++;
	}
}

void pre_work::main()
{
	read_data();
	for(int i = 0; i < n_vtx; i ++)
		if(dfn[i] == -1)
			dfs(i);
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	pre_work::main();
	solve::main();
}
