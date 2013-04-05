#include <cstdio>
#include <algorithm>

using namespace std;

const int N_NODE_MAX = 100010;

#define SET 0
#define ADD 1

struct Edge
{
	int vtx, weight;
	Edge *next;
} edge[N_NODE_MAX * 2], *begin[N_NODE_MAX];
int edge_idx;

void add_edge(int u, int v, int w)
{
	Edge *e = &edge[edge_idx ++];
	e->vtx = v, e->weight = w, e->next = begin[u], begin[u] = e;
}

namespace sgt
{
	struct Node
	{
		Node *ch[2];
		int l, r;
		int max_val, add_val;
		bool is_set, is_add;
	} *null, node_pool[N_NODE_MAX * 4];
	int free_pos;

	void update(Node *x)
	{
		x->max_val = max(x->ch[0]->max_val, x->ch[1]->max_val);
	}

	void set(Node *x, int val)
	{
		x->add_val = 0, x->max_val = val;
		x->is_set = true, x->is_add = false;
	}

	void add(Node *x, int val)
	{
		x->max_val += val;
		if(! x->is_set)
		{	
			x->add_val += val;
			x->is_add = true;
		}
	}	

	void push_down(Node *x)
	{
		if(x->is_set)
		{
			set(x->ch[0], x->max_val);
			set(x->ch[1], x->max_val);
			x->is_set = false;
		}
		if(x->is_add)
		{
			add(x->ch[0], x->add_val);
			add(x->ch[1], x->add_val);
			x->is_add = false;
			x->add_val = 0;
		}
	}

	Node *build(int a, int b, int *val)
	{
		if(a > b)
			return null;
		Node *x = &node_pool[free_pos ++];
		x->l = a, x->r = b;
		x->ch[0] = x->ch[1] = null;
		if(a == b)
			x->max_val = val[a];
		else
		{
			int mid = (a + b) >> 1;
			x->ch[0] = build(a, mid, val);
			x->ch[1] = build(mid + 1, b, val);
			update(x);
		}
		return x;
	}

	void change(Node *x, int a, int b, int val, int type)
	{
		if(x->l > b || x->r < a)
			return;
		if(a <= x->l && x->r <= b)
		{
			if(type == SET)
				set(x, val);
			else
				add(x, val);
			return;
		}
		push_down(x);
		change(x->ch[0], a, b, val, type);
		change(x->ch[1], a, b, val, type);
		update(x);
	}

	int ask(Node *x, int a, int b)
	{
		if(x->l > b || x->r < a)
			return 0;
		if(a <= x->l && x->r <= b)
			return x->max_val;
		push_down(x);
		int res = max(ask(x->ch[0], a, b), ask(x->ch[1], a, b));
		update(x);
		return res;
	}
}

namespace chain_split
{
	struct Node
	{
		int depth, jump, hvst, pre, size, weight;
		sgt::Node *root;
		Node()
		{
			depth = -1;
			size = 0;
			hvst = -1;
			pre = -1;
			jump = -1;
		}
	} node[N_NODE_MAX];
	int seq[N_NODE_MAX];
	int n_seq;

	void work_forward()
	{
		static int queue[N_NODE_MAX];
		int qh = 0, qt = 0;
		queue[qt ++] = 0;
		node[0].depth = 0;
		while(qh < qt)
		{
			int u = queue[qh ++];
			seq[n_seq ++] = u;
			for(Edge *e = begin[u]; e; e = e->next)
			{
				int v = e->vtx;
				if(node[v].depth == -1)
				{
					node[v].pre = u;
					node[v].weight = e->weight;
					node[v].depth = node[u].depth + 1;
					queue[qt ++] = v;
				}
			}
		}
	}

	void work_backward()
	{
		for(int i = n_seq - 1; i >= 0; i --)
		{
			int u = seq[i];
			node[u].size ++;
			int p = node[u].pre;
			node[p].size += node[u].size;
			if(node[node[p].hvst].size < node[u].size)
				node[p].hvst = u;
		}
	}

	void split()
	{
		static bool used[N_NODE_MAX];
		static int idx[N_NODE_MAX], val[N_NODE_MAX];
		for(int i = 0; i < n_seq; i ++)
		{
			int u = seq[i];
			if(! used[u])
				if(node[u].hvst != -1)
				{
					used[u] = true;
					int p = node[u].pre;
					//u = node[u].hvst;
					int n_idx = 0;
					while(1)
					{
						idx[n_idx ++] = u;
						val[node[u].depth] = node[u].weight;
						used[u] = true;
						node[u].jump = p;
						if(node[u].hvst == -1)
							break;
						u = node[u].hvst;
					}
					sgt::Node *x = sgt::build(node[idx[0]].depth, node[idx[n_idx - 1]].depth, val);
					for(int i = 0; i < n_idx; i ++)
						node[idx[i]].root = x;
				}
		}
		for(int i = 1; i < n_seq; i ++)
		{
			int u = seq[i];
			if(! used[u])
			{
				val[node[u].depth] = node[u].weight;
				node[u].root = sgt::build(node[u].depth, node[u].depth, val);
				node[u].jump = node[u].pre;
			}
		}
	}

	int lca(int u, int v)
	{
		while(node[u].root != node[v].root)
		{
			int nu = node[u].jump, nv = node[v].jump;
			if(nu == -1 || node[nu].depth < node[nv].depth)
				swap(u, v), swap(nu, nv);
			u = nu;
		}
		if(node[u].depth > node[v].depth)
			swap(u, v);
		return u;
	}

	int ask(int u, int v)
	{
		int p = lca(u, v);
		int res = 0;
		while(node[u].root != node[p].root)
		{
			int nu = node[u].jump;
			res = max(res, sgt::ask(node[u].root, node[nu].depth + 1, node[u].depth));
			u = nu;
		}
		if(u != p)
			res = max(res, sgt::ask(node[u].root, node[p].depth + 1, node[u].depth));
		while(node[v].root != node[p].root)
		{
			int nv = node[v].jump;
			res = max(res, sgt::ask(node[v].root, node[nv].depth + 1, node[v].depth));
			v = nv;
		}
		if(v != p)
			res = max(res, sgt::ask(node[v].root, node[p].depth + 1, node[v].depth));
		return res;
	}

	void change(int u, int v, int val, int type)
	{
		int p = lca(u, v);
		while(node[u].root != node[p].root)
		{
			int nu = node[u].jump;
			sgt::change(node[u].root, node[nu].depth + 1, node[u].depth, val, type);
			u = nu;
		}
		if(u != p)
			sgt::change(node[u].root, node[p].depth + 1, node[u].depth, val, type);
		while(node[v].root != node[p].root)
		{
			int nv = node[v].jump;
			sgt::change(node[v].root, node[nv].depth + 1, node[v].depth, val, type);
			v = nv;
		}
		if(v != p)
			sgt::change(node[v].root, node[p].depth + 1, node[v].depth, val, type);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, u, v, w;
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i ++)
	{
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	chain_split::work_forward();
	chain_split::work_backward();
	chain_split::split();
	while(1)
	{
		static char cmd[10];
		scanf("%s", cmd);
		if(cmd[0] == 'S')
			break;
		if(cmd[0] == 'M')
		{
			scanf("%d%d", &u, &v);
			u --, v --;
			printf("%d\n", chain_split::ask(u, v));
		}
		else if(cmd[0] == 'C')
		{
			if(cmd[1] == 'o')
			{
				scanf("%d%d%d", &u, &v, &w);
				u --, v --;
				chain_split::change(u, v, w, SET);
			}
			else
			{
				scanf("%d%d", &u, &w);
				u --;
				chain_split::change(edge[2 * u].vtx, edge[2 * u + 1].vtx, w, SET);
			}
		}
		else
		{
			scanf("%d%d%d", &u, &v, &w);
			u --, v --;
			chain_split::change(u, v, w, ADD);
		}
	}
}
