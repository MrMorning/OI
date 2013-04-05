#include <cstdio>
#include <algorithm>
using namespace std;

const int V_MAX = 100010;
const int E_MAX = 2 * V_MAX;
const int inf = 0x3f3f3f3f;

struct Edge {
	int to, len, cost;
	Edge *next, *inv;
	bool on;
} edge[E_MAX], *begin[V_MAX];
int edge_cnt = 0;

Edge *make_edge(int u, int v, int l, int c) {
	Edge *e = edge + edge_cnt ++;
	e->on = true;
	e->to = v, e->next = begin[u], e->cost = c, e->len = l;
	return begin[u] = e;
}

void add_edge(int u, int v, int l, int c) {
	Edge *e1 = make_edge(u, v, l, c),
		 *e2 = make_edge(v, u, l, c);
	e1->inv = e2; e2->inv = e1;
}

struct Info {
	int dep, dia, f, g;
} node[V_MAX];

void work(int x) {
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			e->inv->on = false;
			work(e->to);
			e->inv->on = true;
		}
	//calc node[x].dia
	int dep_max[2];
	dep_max[0] = dep_max[1] = 0; // the two largest dep in sons
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			int y = e->to;
			node[x].dia = max(node[x].dia, node[y].dia);
			int tmp = node[y].dep + e->len;
			if ( tmp > dep_max[0] ) {
				dep_max[1] = dep_max[0];
				dep_max[0] = tmp;
			} else if ( tmp > dep_max[1] )
				dep_max[1] = tmp;
		}
	node[x].dia = max(node[x].dia, dep_max[0] + dep_max[1]);

	//calc node[x].dep
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) 
			node[x].dep = max(node[x].dep, node[e->to].dep + e->len);

	//calc node[x].g
	node[x].g = 0;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			int y = e->to;
			int tmp = node[y].dep + e->len;
			if ( tmp == node[x].dep ) 
				node[x].g += min(e->cost, node[y].g == 0 ? inf : node[y].g);
		}
	
	//calc node[x].f
	if ( dep_max[0] + dep_max[1] == node[x].dia ) {
		//the diameter go through x
		if ( dep_max[0] == dep_max[1] ) {
			//l_n = l_n-1 = l_n-2 = ...
			node[x].f = 0;
			int best_fee = inf;
			for ( Edge *e = begin[x]; e; e = e->next ) 
				if ( e->on ) {
					int y = e->to;
					int tmp = node[y].dep + e->len;
					if ( tmp == dep_max[0] ) {
						int fee = min(e->cost, node[y].g == 0 ? inf : node[y].g);
						node[x].f += fee;
						if ( fee < best_fee ) 
							best_fee = fee;
					}
				}
			node[x].f -= best_fee;
		} else {
			//l_n > l_n-1 = l_n-2 = ...
			node[x].f = 0;
			int f2;
			for ( Edge *e = begin[x]; e; e = e->next ) 
				if ( e->on ) {
					int y = e->to;
					int tmp = node[y].dep + e->len;
					if ( tmp == dep_max[1] ) 
						node[x].f += min(e->cost, node[y].g == 0 ? inf : node[y].g);
					else if ( tmp == dep_max[0] )
						f2 = min(e->cost, node[y].g == 0 ? inf : node[y].g);
				}
			if ( dep_max[1] == 0 ) //x has only one son
				node[x].f = f2;
			else
				node[x].f = min(node[x].f, f2);
		}
	} else {
		//the diameter is in sons' subtrees
		node[x].f = 0;
		for ( Edge *e = begin[x]; e; e = e->next ) 
			if ( e->on ) {
				int y = e->to;
				if ( node[y].dia == node[x].dia )
					node[x].f += node[y].f;
			}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int n_node;
	scanf("%d", &n_node);
	for ( int i = 0; i < n_node - 1; i ++ ) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		add_edge(a, b, c, d);
	}
	work(1);
	printf("%d\n", node[1].f);
}
