#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int V_MAX = 100010;
const int E_MAX = 100010;

struct Edge {
	int to, id;
	Edge *next, *inv; 
} edge[2 * E_MAX], *begin[V_MAX];
int edge_cnt;

Edge *make_edge(int u, int v, int id) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], e->id = id;
	begin[u] = e;
	return e;
}

void add_edge(int u, int v, int id) {
	Edge *e1 = make_edge(u, v, id),
		 *e2 = make_edge(v, u, id);
	e1->inv = e2, e2->inv = e1;
}

struct Data {
	int u, v, w, id;
	bool operator< (const Data &t) const {
		return w < t.w;
	}
} data[E_MAX];
int fa[V_MAX], dfn[V_MAX], low[V_MAX];
int res[E_MAX];
int stamp;
map<int, int> conv;
Edge *pre[V_MAX];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	if ( find(x) == find(y) ) return;
	fa[find(x)] = find(y);
}

void tarjan(int x, Edge *p) {
	dfn[x] = low[x] = stamp ++;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( p == NULL || e != p->inv) {
			int y = e->to;
			if ( dfn[y] == -1 ) {
				tarjan(y, e);
				low[x] = min(low[x], low[y]);
			} else
				low[x] = min(low[x], dfn[y]);
			if ( low[y] > dfn[x] )
				res[e->id] = 1;
		}
}

int main() {
	//freopen("t.in", "r", stdin);
	int nv, ne;
	scanf("%d%d", &nv, &ne);
	for ( int i = 0; i < ne; i ++ ) {
		scanf("%d%d%d", &data[i].u, &data[i].v, &data[i].w);
		data[i].u --, data[i].v --;
		data[i].id = i;
	}
	sort(data, data + ne);
	for ( int i= 0; i < nv; i ++ )
		fa[i] = i;
	int prev_cnt = 0, comp_cnt = 0;
	for ( int i = 0; i < ne; i ++ ) {
		int st = i;
		while ( i + 1 < ne && data[i + 1].w == data[st].w )
			i ++;
		memset(begin, 0, sizeof(Edge*) * prev_cnt);
		edge_cnt = 0;
		conv.clear();
		comp_cnt = 0;
		for ( int k = st; k <= i; k ++ ) {
			int u = find(data[k].u), v = find(data[k].v);
			if ( !conv.count(u) )
				conv[u] = comp_cnt ++;
			if ( !conv.count(v) )
				conv[v] = comp_cnt ++;
			if ( u == v )
				res[data[k].id] = -1;
			else
				add_edge(conv[u], conv[v], data[k].id);
		}
		memset(dfn, -1, sizeof(int) * comp_cnt);
		memset(pre, 0, sizeof(Edge*) * comp_cnt);
		stamp = 0;
		for ( int x = 0; x < comp_cnt; x ++ )
			if ( dfn[x] == -1 )
				tarjan(x, NULL);
		prev_cnt = comp_cnt;
		for ( int k = st; k <= i; k ++ ) {
			int u = find(data[k].u), v = find(data[k].v);
			merge(u, v);
		}
	}

	for ( int i = 0; i < ne; i ++ )
		if ( res[i] == -1 )
			printf("none\n");
		else if ( res[i] == 0 )
			printf("at least one\n");
		else
			printf("any\n");
}
