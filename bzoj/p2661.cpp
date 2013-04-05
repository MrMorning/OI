
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}

const int V_MAX = 2000;
const int E_MAX = 100000;
const int inf = 0x3f3f3f3f;

struct Edge {
	int cap, cost, vtx;
	Edge *next, *inv;
};

Edge edge[E_MAX], *begin[V_MAX], *prev[V_MAX];
int n_edge, n_vtx, s_vtx, t_vtx;

int dist[V_MAX];
vector<int> adj[V_MAX];

Edge *make_edge(int u, int v, int cap, int cost) {
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], e->cap = cap, e->cost = cost;
	return begin[u] = e;
}

void add_edge(int u, int v, int cap, int cost) {
	Edge *e1 = make_edge(u, v, cap, cost),
		 *e2 = make_edge(v, u, 0, -cost);
	e1->inv = e2, e2->inv = e1;
}

bool spfa(int s_vtx, int t_vtx) {
	static int queue[V_MAX];
	static bool in_q[V_MAX];
	for(int i = 0; i < n_vtx; i ++)
		dist[i] = inf;
	dist[s_vtx] = 0;
	memset(in_q, 0, sizeof(in_q));
	memset(prev, 0, sizeof(Edge *) * n_vtx);
	int qt = 0, qh = 0;

	queue[qt ++] = s_vtx, in_q[s_vtx] = true;
	while(qt != qh) {
		int u = queue[qh];
		in_q[u] = false;
		qh = (qh + 1) % n_vtx;
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap) {
				int v = e->vtx;
				if(dist[v] > dist[u] + e->cost) {
					dist[v] = dist[u] + e->cost;
					prev[v] = e;
					if(! in_q[v]) {
						in_q[v] = true;
						queue[qt] = v;
						qt = (qt + 1) % n_vtx;
					}
				}
			}
	}
	return dist[t_vtx] != inf;
}

pair<int, int> mcmf(int s_vtx, int t_vtx) {
	int min_cost = 0, max_flow = 0;
	while(spfa(s_vtx, t_vtx)) {
		int u = t_vtx;
		int flow = 0x3f3f3f3f;
		while(1) {
			if(prev[u] == NULL)
				break;
			flow = std::min(flow, prev[u]->cap);
			u = prev[u]->inv->vtx;
		}
		max_flow += flow;
		u = t_vtx;
		while(1) {
			if(prev[u] == NULL)
				break;
			Edge *e = prev[u];
			e->cap -= flow, e->inv->cap += flow;
			min_cost += e->cost * flow;
			u = prev[u]->inv->vtx;
		}
	}
	return make_pair(max_flow, min_cost);
}

int L, R;
int color[V_MAX];

void paint(int x, int c) {
	color[x] = c;
	FOREACH(it, adj[x]) {
		int y = *it;
		if ( color[y] != -1 )
			continue;
		paint(y, !c);
	}
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d", &L, &R);
	for ( int x = L; x <= R; x ++ )
		for ( int y = L; y < x; y ++ ) {
			int z2 = x * x - y * y,
				z = (int)sqrt(z2);
			if ( z2 == z * z && gcd(y, z) == 1 ) {
				adj[x].push_back(y);
				adj[y].push_back(x);
			}
		}
	memset(color, -1, sizeof(color));
	for ( int x = L; x <= R; x ++ )
		if ( color[x] == -1 )
			paint(x, 0);
	s_vtx = R + 1, t_vtx = R + 2;
	n_vtx = R + 3;
	for ( int x = L; x <= R; x ++ ) {
		if ( color[x] == 0 ) {
			add_edge(s_vtx, x, 1, 0);
			FOREACH(it, adj[x]) {
				int y = *it;
				add_edge(x, y, 1, -(x + y));
			}
		} else
			add_edge(x, t_vtx, 1, 0);
	}
	pair<int, int> res = mcmf(s_vtx, t_vtx);
	printf("%d %d\n", res.first, -res.second);
}
