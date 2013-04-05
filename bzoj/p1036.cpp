#include <cstdio>
#define INLINE __attribute__((always_inline))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int N_VTX_MAX = 30000, N_EDGE_MAX = 2 * (N_VTX_MAX - 1);

inline void swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

struct Edge
{
	int vtx;
	Edge *next;
};

struct Info
{
	int max, sum;
	bool e;
	Info(bool _e = true): e(_e){};
	Info(int _max, int _sum) : max(_max), sum(_sum)
	{
		e = true;
	};
	Info operator+ (const Info &x) const;
};
struct Buffer
{
	int idx, w;
	Buffer(int _idx = -1, int _w = -1): idx(_idx), w(_w){};
};
namespace sgt
{
	struct Node
	{
		Node *ch[2];
		int l, r;
		Info info;
	};

	Node node_pool[N_VTX_MAX * 30];
	int node_idx;

	Node *node_alloc(int l, int r) INLINE;
	void update(Node *x) INLINE;
	Node *build(Buffer *buffer, int l, int r);
	void change(Node *x, int pos, int new_w);
	Info ask(Node *x, int l, int r);
};
struct Node
{
	int pre, hvst;
	Edge *begin;
	int depth, size;
	int jump;

	sgt::Node *root;
	int pos;
};

Node node[N_VTX_MAX];
Buffer buffer[N_VTX_MAX];
Edge edge[N_EDGE_MAX];
int edge_idx, n_vtx;
int input_w[N_VTX_MAX];

namespace chain_split
{
	int seq[N_VTX_MAX], n_seq;
	void make_seq();
	void work_foreward();
	void work_backward();
	void split_path();
}

void add_edge(int u, int v)
{
	Edge *e = &edge[edge_idx ++];
	e->vtx = v, e->next = node[u].begin, node[u].begin = e;
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
sgt::Node *sgt::build(Buffer *buffer, int l, int r)
{
	Node *x = node_alloc(l, r);
	if(l == r)
	{
		x->info = Info(buffer[l].w, buffer[l].w);
		node[buffer[l].idx].pos = l;
	}
	else
	{
		x->ch[0] = build(buffer, l, (l + r) / 2);
		x->ch[1] = build(buffer, (l + r) / 2 + 1, r);
		update(x);
	}
	return x;
}
void sgt::change(Node *x, int pos, int new_w)
{
	if(x->l > pos || x->r < pos)
		return;
	if(x->l == pos && x->r == pos)
	{
		x->info = Info(new_w, new_w);
		return;
	}
	change(x->ch[0], pos, new_w), change(x->ch[1], pos, new_w);
	update(x);
}
Info sgt::ask(Node *x, int l, int r)
{
	if(x->l > r || x->r < l)
		return Info(false);
	if(l <= x->l && x->r <= r)
		return x->info;
	return ask(x->ch[0], l, r) + ask(x->ch[1], l, r);
}

Info Info::operator+ (const Info &x) const
{
	if(! e)
		return x;
	if(! x.e)
		return *this;
	Info ret = *this;
	ret.sum += x.sum;
	ret.max = MAX(ret.max, x.max);
	return ret;
}

void chain_split::make_seq()
{
	static int queue[N_VTX_MAX];
	static bool vis[N_VTX_MAX];

	for(int i = 0; i < n_vtx; i ++)
		node[i].pre = node[i].hvst = node[i].depth = node[i].jump = -1;
	int head = 0, tail = 0;
	queue[tail ++] = 0, vis[0] = true;
	while(head != tail)
	{
		int u = queue[head ++];
		seq[n_seq ++] = u;
		for(Edge *e = node[u].begin; e; e = e->next)
		{
			int v = e->vtx;
			if(! vis[v])
			{
				vis[v] = true;
				queue[tail ++] = v;
				node[v].pre = u;
			}
		}
	}
}
void chain_split::work_foreward()
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
			if(v == -1 || node[v].size < node[u].size)
				v = u;
		}
	}
}

void chain_split::split_path()
{
	static bool vis[N_VTX_MAX];
	for(int i = 0; i < n_seq; i ++)
	{
		int u = seq[i], p = u;
		int n_buffer = 0;
		if(! vis[u])
		{
			while(1)
			{
				if(node[u].hvst == -1)
					break;
				u = node[u].hvst;
				vis[u] = true;
				buffer[n_buffer ++] = Buffer(u, input_w[u]);

				node[u].jump = p;
			}
		}
		if(n_buffer)
		{
			sgt::Node *x = sgt::build(buffer, 0, n_buffer - 1);
			for(int i = 0; i < n_buffer; i ++)
				node[buffer[i].idx].root = x;
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
			buffer[0] = Buffer(u, input_w[u]);
			node[u].root = sgt::build(buffer, 0, 0);
		}
	}
}

Info ask(int u, int v)
{
	Info ret = Info(false);
	while(1)
	{
		if(node[u].root == node[v].root)
			break;
		int next_u = node[u].jump,
			next_v = node[v].jump;
		if(node[next_u].depth < node[next_v].depth)
			swap(u, v), swap(next_u, next_v);
		ret = ret + sgt::ask(node[u].root, 0, node[u].pos);
		u = next_u;
	}
	if(node[u].depth < node[v].depth)
		swap(u, v);
	ret = ret + sgt::ask(node[u].root, node[v].pos, node[u].pos);
	return ret;
}

void change(int u, int w)
{
	sgt::change(node[u].root, node[u].pos, w);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n_vtx);
	for(int i = 0, a, b; i < n_vtx - 1; i ++)
	{
		scanf("%d%d", &a, &b);
		a --, b --;
		add_edge(a, b), add_edge(b, a);
	}
	for(int i = 0; i < n_vtx; i ++)
		scanf("%d", &input_w[i]);
	chain_split::make_seq();
	chain_split::work_foreward();
	chain_split::work_backward();
	chain_split::split_path();
	int n_cmd;
	scanf("%d", &n_cmd);
	while(n_cmd --)
	{
		char cmd[10];
		int u, v;
		scanf("%s%d%d", cmd, &u, &v);
		u --, v --;
		if(cmd[0] == 'C')
			change(u, ++ v);
		else
		{
			Info tmp = ask(u, v);
			if(cmd[1] == 'M')
				printf("%d\n", tmp.max);
			else
				printf("%d\n", tmp.sum);
		}
	}
}
