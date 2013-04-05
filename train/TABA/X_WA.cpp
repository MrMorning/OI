#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int V_MAX = 100010;
const int E_MAX = 2 * V_MAX;
const int inf = 0x3f3f3f3f;

struct Edge {
	int to, len, cost, id;
	Edge *next, *inv;
	bool on;
} edge[E_MAX], *begin[V_MAX];
int edge_cnt = 0;

vector<int> res;

Edge *make_edge(int id, int u, int v, int l, int c) {
	Edge *e = edge + edge_cnt ++;
	e->on = true;
	e->id = id;
	e->to = v, e->next = begin[u], e->cost = c, e->len = l;
	return begin[u] = e;
}

void add_edge(int id, int u, int v, int l, int c) {
	Edge *e1 = make_edge(id, u, v, l, c),
		 *e2 = make_edge(id, v, u, l, c);
	e1->inv = e2; e2->inv = e1;
}

struct Info {
	int dep, dia, f, g, dm[2];
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
	node[x].dm[0] = dep_max[0], node[x].dm[1] = dep_max[1];

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
			int best_fee = 0;
			for ( Edge *e = begin[x]; e; e = e->next ) 
				if ( e->on ) {
					int y = e->to;
					int tmp = node[y].dep + e->len;
					if ( tmp == dep_max[0] ) {
						int fee = min(e->cost, node[y].g == 0 ? inf : node[y].g);
						node[x].f += fee;
						if ( fee > best_fee ) 
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

void output_g(int);

void output_f(int x) {
	int dep_max[2];
	dep_max[0] = node[x].dm[0], dep_max[1] = node[x].dm[1];
	if ( dep_max[0] + dep_max[1] == node[x].dia ) {
		if ( dep_max[0] == dep_max[1] ) {
			//l_n = l_n-1 = l_n-2 = ...
			int best_fee = 0;
			for ( Edge *e = begin[x]; e; e = e->next ) 
				if ( e->on ) {
					int y = e->to;
					int tmp = node[y].dep + e->len;
					if ( tmp == dep_max[0] ) {
						int fee = min(e->cost, node[y].g == 0 ? inf : node[y].g);
						if ( fee > best_fee ) 
							best_fee = fee;
					}
				}
			for ( Edge *e = begin[x]; e; e = e->next )
				if ( e->on ) {
					int y = e->to;
					int tmp = node[y].dep + e->len;
					if ( tmp == dep_max[0] ) {
						int fee = min(e->cost, node[y].g == 0 ? inf : node[y].g);
						if ( fee == best_fee )
							best_fee = 0;
						else {
							if ( fee == e->cost )
								res.push_back(e->id);
							else
								output_g(y);
						}
					}
				}
		} else {
			//l_n > l_n-1 = l_n-2 = ...
			int f1 = 0, f2;
			Edge *te;
			for ( Edge *e = begin[x]; e; e = e->next ) 
				if ( e->on ) {
					int y = e->to;
					int tmp = node[y].dep + e->len;
					if ( tmp == dep_max[1] ) 
						f1 += min(e->cost, node[y].g == 0 ? inf : node[y].g);
					else if ( tmp == dep_max[0] ) {
						f2 = min(e->cost, node[y].g == 0 ? inf : node[y].g);
						te = e;
					}
				}
			if ( dep_max[1] == 0 || f1 > f2 ) { 
				//x has only one son 
				if ( f2 == te->cost )
					res.push_back(te->id);
				else
					output_g(te->to);
			} else {
				for ( Edge *e = begin[x]; e; e = e->next ) 
					if ( e->on ) {
						int y = e->to;
						int tmp = node[y].dep + e->len;
						if ( tmp == dep_max[1] ) {
							int fee = min(e->cost, node[y].g == 0 ? inf : node[y].g);
							if ( fee == e->cost ) 
								res.push_back(e->id);
							else
								output_g(y);
						}
					}
			}
		}
	} else 
		for ( Edge *e = begin[x]; e; e = e->next ) 
			if ( e->on ) {
				int y = e->to;
				if ( node[y].dia == node[x].dia )
					output_f(y);
			}
}

void output_g(int x) {
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			int y = e->to;
			int tmp = node[y].dep + e->len;
			if ( tmp == node[x].dep ) {
				int fee = min(e->cost, node[y].g == 0 ? inf : node[y].g);
				if ( fee == e->cost )
					res.push_back(e->id);
				else
					output_g(y);
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
		add_edge(i + 1, a, b, c, d);
	}
	int root = rand() % n_node + 1;
	work(root);
	printf("%d\n", node[root].f);
	output_f(root);
	printf("%d\n", (int)res.size());
	for ( int i = 0, sz = res.size();
			i < sz; i ++ )
		printf("%d ", res[i]);
}
