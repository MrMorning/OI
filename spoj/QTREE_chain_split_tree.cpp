#include <cstdio>
#include <cassert>
#include <cstring>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
inline void swap(int &a, int &b){int c = a; a = b, b = c;}

const int N_NODE_MAX = 20000;
const int N_EDGE_MAX = 2 * (N_NODE_MAX - 1);
const int INFINITY = 0x3f3f3f3f;

struct Edge
{
	int vtx, weight, idx;
	Edge *next;
};

struct Info
{
	int val;
	Info(int _val = -INFINITY): val(_val){}
};

struct Buffer
{
	int idx, w;
	Buffer(int _idx = -1, int _w = 0): idx(_idx), w(_w){}
};

Info operator+ (const Info &a, const Info &b)
{
	return Info(MAX(a.val, b.val));
}
namespace sgt
{
	struct Node
	{
		int l, r;
		Node *ch[2];
		Info info;
	};
	Node node_pool[N_NODE_MAX * 30];
	int node_idx;

	Node *node_alloc(int l, int r);
	Node *build(int l, int r, Buffer *buf);
	void change(Node *x, int pos, Info _info);
	Info ask(Node *x, int l, int r);
	void update(Node *x);
}

struct Node
{
	int pre, hvst, depth, size, jump;
	Edge *begin;
	sgt::Node *root;
	int pos;
};

namespace chain_split
{
	int weight[N_NODE_MAX];
	int seq[N_NODE_MAX];
	Buffer buf[N_NODE_MAX];
	int n_seq, n_buf;

	void init();
	void bfs();//process pre
	void work_forward();//process depth
	void work_backward();//process size && hvst
	void split_path();
}

namespace solve
{
	void init();
	void change(int i, int new_val);
	Info ask(int u, int v);
	void solve();
}

int edge_idx, n_node;
Edge edge[N_EDGE_MAX];
int linked[N_EDGE_MAX];
Node node[N_NODE_MAX];

Edge *make_edge(int u, int v, int idx, int weight)
{
	Edge *e = &edge[edge_idx ++];
	e->next = node[u].begin, e->vtx = v, e->idx = idx, e->weight = weight;
	return node[u].begin = e;
}

void add_edge(int u, int v, int idx, int weight)
{
	make_edge(u, v, idx, weight);
	make_edge(v, u, idx, weight);
}

sgt::Node *sgt::node_alloc(int l, int r)
{
	Node *x = &node_pool[node_idx ++];
	x->l = l, x->r = r;
	return x;
}

void sgt::update(Node *x)
{
	x->info = x->ch[0]->info + x->ch[1]->info;
}

sgt::Node *sgt::build(int l, int r, Buffer *buf)
{
	Node *x = node_alloc(l, r);
	if(l == r)
	{
		x->info = Info(buf[l].w);
		node[buf[l].idx].pos = l;
	}
	else
	{
		x->ch[0] = build(l, (l + r) >> 1, buf);
		x->ch[1] = build((l + r) / 2 + 1, r, buf);
		update(x);
	}
	return x;
}

void sgt::change(Node *x, int pos, Info _info)
{
	if(x->l > pos || x->r < pos)
		return;
	if(x->l == pos && x->r == pos)
	{
		x->info = _info;
		return;
	}
	change(x->ch[0], pos, _info);
	change(x->ch[1], pos, _info);
	update(x);
}

Info sgt::ask(Node *x, int l, int r)
{
	if(x->l > r || x->r < l)
		return Info(- INFINITY);
	if(l <= x->l && x->r <= r)
		return x->info;
	assert(x != NULL);
	return ask(x->ch[0], l, r) + ask(x->ch[1], l, r);
}
void chain_split::init()
{
	for(int i = 0; i < n_node; i ++)
	{
		node[i].pre = node[i].hvst = node[i].jump = node[i].depth = -1;
		node[i].size = 0;
	}
}
void chain_split::bfs()
{
	static int queue[N_NODE_MAX];
	static bool vis[N_NODE_MAX];
	memset(vis, 0, sizeof(bool) * n_node);
	int head = 0, tail = 0;
	queue[tail ++] = 0, vis[0] = true;
	n_seq = 0;
	while(head != tail)
	{
		int u = queue[head ++];
		seq[n_seq ++] = u;
		for(Edge *e = node[u].begin; e; e = e->next)
		{
			int v = e->vtx;
			if(vis[v])
				continue;
			vis[v] = true;
			weight[v] = e->weight;
			linked[e->idx] = v;
			queue[tail ++] = v;
			node[v].pre = u;
		}
	}
}

void chain_split::work_forward()
{
	node[0].depth = 0;
	for(int i = 0; i < n_seq; i ++)
	{
		int u = seq[i], p = node[u].pre;
		if(node[p].depth != -1)
			node[u].depth = node[p].depth + 1;
	}
}

void chain_split::work_backward()
{
	for(int i = n_seq - 1; i >= 0; i --)
	{
		int u = seq[i], p = node[u].pre;
		node[u].size ++;
		if(p != -1)
		{
			node[p].size += node[u].size;
			int &v = node[p].hvst;
			if(v == -1 || node[u].size > node[v].size)
				v = u;
		}
	}
}

void chain_split::split_path()
{
	static bool vis[N_NODE_MAX];
	memset(vis, 0, sizeof(bool) * n_node);
	for(int i = 0; i < n_seq; i ++)
	{
		int u = seq[i], p = u;
		int n_buf = 0;
		if(! vis[u])
		{
			while(1)
			{
				if(node[u].hvst == -1)
					break;
				u = node[u].hvst;
				vis[u] = true;
				buf[n_buf ++] = Buffer(u, weight[u]);
				node[u].jump = p;
			}
		}
		if(n_buf)
		{
			sgt::Node *x = sgt::build(0, n_buf - 1, buf);
			for(int i = 0; i < n_buf; i ++)
				node[buf[i].idx].root = x;
		}
	}
	for(int i = 0; i < n_seq; i ++)
	{
		int u = seq[i];
		if(! vis[u])
		{
			int p = node[u].pre;
			node[u].jump = p;
			node[u].pos = 0;
			buf[0] = Buffer(u, weight[u]);
			node[u].root = sgt::build(0, 0, buf);
		}
	}
}

void solve::change(int i, int new_val)
{
	int u = linked[i];
	sgt::change(node[u].root, node[u].pos, Info(new_val));
}

Info solve::ask(int u, int v)
{
	Info ret;
	while(1)
	{
		if(node[u].root == node[v].root)
			break;
		if(node[node[u].jump].depth < node[node[v].jump].depth)
			swap(u, v);
		ret = ret + sgt::ask(node[u].root, 0, node[u].pos);
		u = node[u].jump;
	}
	if(node[u].depth > node[v].depth)
		swap(u, v);
	if(node[u].pos < node[v].pos)
		ret = ret + sgt::ask(node[u].root, node[u].pos + 1, node[v].pos);
	return ret;
}

void solve::init()
{
	edge_idx = 0;
	sgt::node_idx = 0;
	memset(node, 0, sizeof(Node) * n_node);
}

void solve::solve()
{
	int u, v, w, i;
	scanf("%d", &n_node);
	init();
	for(int i = 1; i < n_node; i ++)
	{
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		add_edge(u, v, i, w);
	}
	chain_split::init();
	chain_split::bfs();
	chain_split::work_forward();
	chain_split::work_backward();
	chain_split::split_path();
	while(1)
	{
		char cmd[10];
		scanf("%s", cmd);
		if(cmd[0] == 'D')
			break;
		if(cmd[0] == 'Q')
		{
			scanf("%d%d", &u, &v);
			u --, v --;
			printf("%d\n", ask(u, v).val);
		}
		else
		{
			scanf("%d%d", &i, &w);
			change(i, w);
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
		solve::solve();
}
