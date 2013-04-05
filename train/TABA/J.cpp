#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 30010;

struct Edge {
	int to;
	bool on;
	Edge *next, *inv;
} edge[N_MAX * 2], *begin[N_MAX];
int edge_cnt = 0;

Edge *make_edge(int u, int v) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], e->on = true;
	return begin[u] = e;
}

void add_edge(int u, int v) {
	Edge *e1 = make_edge(u, v),
		 *e2 = make_edge(v, u);
	e1->inv = e2, e2->inv = e1;
}

namespace dsu {
	int par[N_MAX], sz[N_MAX];
	int find(int x) {
		return par[x] == x ? x : par[x] = find(par[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		par[x] = y;
		sz[y] += sz[x];
	}
	void init(int n) {
		for ( int i = 0; i < n; i ++ ) {
			par[i] = i;
			sz[i] = 1;
		}
	}
}

struct Node {
	Node *ch[2], *pre;
	int sum, val;
	void clear(); 
} node[N_MAX], *id2ptr[N_MAX], *null;
int free_pos = 0;

void Node::clear() {
	ch[0] = ch[1] = pre = null;
	sum = val;
}

Node *alloc(int val) {
	Node *x = node + free_pos ++;
	x->val = x->sum = val;
	x->ch[0] = x->ch[1] = x->pre = null;
	return x;
}

void update(Node *x) {
	x->sum = x->ch[0]->sum + x->ch[1]->sum + x->val;
}

void rotate(Node *x, int dir) {
	Node *y = x->pre;
	x->pre = y->pre;
	if ( y == y->pre->ch[y == y->pre->ch[1]] )
		y->pre->ch[y == y->pre->ch[1]] = x;
	y->ch[!dir] = x->ch[dir];
	if ( x->ch[dir] != null )
		x->ch[dir]->pre = y;
	x->ch[dir] = y;
	y->pre = x;
	update(y);
}

void splay(Node *x) {
	while ( x == x->pre->ch[x == x->pre->ch[1]] ) {
		Node *y = x->pre, *z = y->pre;
		if ( y != z->ch[y == z->ch[1]] )
			rotate(x, x == x->pre->ch[0]);
		else {
			if ( y == z->ch[0] ) {
				if ( x == y->ch[0] )
					rotate(y, 1);
				else
					rotate(x, 0);
				rotate(x, 1);
			} else {
				if ( x == y->ch[1] )
					rotate(y, 0);
				else
					rotate(x, 1);
				rotate(x, 0);
			}
		}
	}
	update(x);
}

Node *expose(Node *x) {
	Node *y = null;
	while ( x != null ) {
		splay(x);
		x->ch[1] = y;
		update(x);
		y = x;
		x = x->pre;
	}
	return y;
}

void link(Node *src, Node *des) {
	expose(src);
	splay(src);
	src->pre = des;
	//update(des);
	expose(src);
}

int ask(Node *u, Node *v) {
	expose(u);
	Node *p = expose(v);
	splay(u);
	int res = u == p ? 0 : u->sum;
	splay(p);
	res += p->val + p->ch[1]->sum;
	return res;
}

int seq[N_MAX], seq_cnt, father[N_MAX];
void get_dfs_seq(int x) {
	seq[seq_cnt ++] = x;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			e->inv->on = false;
			int y = e->to;
			father[y] = x;
			get_dfs_seq(y);
			e->inv->on = true;
		}
}

void rebuild(int r) {
	seq_cnt = 0;
	get_dfs_seq(r);
	for ( int i = 0; i < seq_cnt; i ++ ) {
		int x = seq[i];
		id2ptr[x]->clear();
		if ( i != 0 )
			id2ptr[x]->pre = id2ptr[father[x]];
	}
}

int n_isl, n_query;
int main() {
	freopen("t.in", "r", stdin);
	null = alloc(0);
	scanf("%d", &n_isl);
	for ( int i = 0; i < n_isl; i ++ ) {
		int x;
		scanf("%d", &x);
		id2ptr[i] = alloc(x);
	}
	dsu::init(n_isl);
	scanf("%d", &n_query);
	for ( int query_idx = 0; query_idx < n_query; query_idx ++ ) {
		static char cmd[15];
		scanf("%s", cmd);
		if ( cmd[0] == 'b' ) {
			int u, v;
			scanf("%d%d", &u, &v);
			u --, v --;
			if ( dsu::find(u) == dsu::find(v) )
				printf("no\n");
			else {
				printf("yes\n");
				int p = dsu::find(u), q = dsu::find(v);
				if ( dsu::sz[p] > dsu::sz[q] )
					swap(u, v);
				rebuild(u);
				link(id2ptr[u], id2ptr[v]);
				add_edge(u, v);
				dsu::merge(u, v);
			}
		} else if ( cmd[0] == 'p' ) {
			int a, x;
			scanf("%d%d", &a, &x);
			a --;
			id2ptr[a]->val = x;
			expose(id2ptr[a]);
		} else {
			int u, v;
			scanf("%d%d", &u, &v);
			u --, v --;
			if ( dsu::find(u) != dsu::find(v) )
				printf("impossible\n");
			else
				printf("%d\n", ask(id2ptr[u], id2ptr[v]));
		}
	}
}
