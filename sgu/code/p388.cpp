#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;

const int kInf = 0x3f3f3f3f;

struct Edge {
	int from, to, cap, cost, flow, id;
	Edge *inv, *next;
};

namespace solve2 {
	const int kVtxMax = 444;
	const int kEdgeMax = kVtxMax*kVtxMax;
	Edge edge[kEdgeMax], *begin[kVtxMax], *prev[kVtxMax];
	int dist[kVtxMax];
	int edgeCnt = 0;
	int src, sink;

	Edge *makeEdge(int u, int v, int cap, int cost, int id) {
		Edge *e = edge+edgeCnt++;
		e->to = v, e->next = begin[u], e->cap = cap, e->cost = cost, e->id = id;
		return begin[u] = e;
	}

	void addEdge(int u, int v, int cap, int cost, int id) {
		Edge *e1 = makeEdge(u, v, cap, cost, id),
			 *e2 = makeEdge(v, u, 0, -cost, id);
		e1->inv = e2; e2->inv = e1;
	}

	bool spfa() {
		static int Q[kVtxMax];
		static bool inQ[kVtxMax];
		int qh = 0, qt = 0;
		Q[qt++] = src;
		memset(inQ, 0, sizeof(inQ));
		memset(dist, 0x3f, sizeof(dist));
		memset(prev, 0, sizeof(prev));
		dist[src] = 0;
		inQ[src] = true;

		while ( qh != qt ) {
			int u = Q[qh];
			qh = (qh + 1) % kVtxMax;
			inQ[u] = false;

			for ( Edge *e = begin[u]; e; e = e->next ) 
				if ( e->cap ) {
					int v = e->to;
					int tmp = dist[u] + e->cost;
					if ( tmp < dist[v] ) {
						dist[v] = tmp;
						prev[v] = e;
						if ( !inQ[v] ) {
							inQ[v] = true;
							Q[qt] = v;
							qt = (qt + 1) % kVtxMax;
						}
					}
				}
		}

		return dist[sink] != kInf;
	}

	int mcmf() {
		int res = 0;
		while ( spfa() ) {
			int flow = kInf;
			for ( Edge *e = prev[sink]; e; e = prev[e->inv->to] )
				flow = min(flow, e->cap);
			for ( Edge *e = prev[sink]; e; e = prev[e->inv->to] ) {
				e->cap -= flow;
				e->inv->cap += flow;
				res += e->cost * flow;
			}
		}
		return res;
	}
}

namespace solve1 {
	const int kVtxMax = 222;
	const int kEdgeMax = kVtxMax * kVtxMax;
	Edge edge[kEdgeMax];
	int edgeCnt;

	void addEdge(int u, int v, int cap, int cost, int id) {
		Edge *e = &edge[edgeCnt];
		e->to = v, e->cap = cap, e->from = u, e->cost = cost, e->id = id;
		edgeCnt++;
	}

	void main(int n) {
#define IV(x) (x)
#define OV(x) ((x)+(n))
		int src = 2*n+1, sink = 2*n+2;
		solve2::src = src, solve2::sink = sink;
		for ( int i = 1; i <= n; i ++ ) {
			solve2::addEdge(src, IV(i), kInf, 0, -1);
			solve2::addEdge(IV(i), OV(i), kInf, 0, -1);
			solve2::addEdge(OV(i), sink, kInf, 0, -1);
		}
		for ( int i = 0; i < edgeCnt; i ++ ) {
			Edge *e = edge+i;
			solve2::addEdge(IV(e->from), OV(e->to), e->cap, e->cost, i);
		}	
		solve2::mcmf();
		for ( int i = 0; i < solve2::edgeCnt; i += 2 ) {
			Edge *e1 = solve2::edge + i,
				 *e2 = e1 + 1;
			assert(e1->inv == e2 && e2->inv == e1);
			if ( e1->id != -1 ) {
				edge[e1->id].flow = e2->cap;
			}
		}
#undef IV
#undef OV
	}
}

struct Player {
	int a, b;
} player1[11111], player2[11111];
vector<int> adj[111];
int color[111];
int n, m1, m2;
pair<int, int> ans1[111], ans2[111];
int nAns1, nAns2;

void dfs(int x, int c) {
	color[x] = c;
	foreach(it, adj[x])
		if ( color[*it] == -1 )
			dfs(*it, !c);
}

int main() {
#define IV(x) (x)
#define OV(x) ((x)+(n))
#define RET(x) ((x)>(n)?((x)-(n)):(x))
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m1, &m2);
	for ( int i = 1; i <= m1; i ++ ) {
		scanf("%d%d", &player1[i].a, &player1[i].b);
		adj[player1[i].a].pb(player1[i].b);
		adj[player1[i].b].pb(player1[i].a);
	}
	for ( int i = 1; i <= m2; i ++ ) {
		scanf("%d%d", &player2[i].a, &player2[i].b);
		adj[player2[i].a].pb(player2[i].b);
		adj[player2[i].b].pb(player2[i].a);
	}

	memset(color, -1, sizeof(color));
	for ( int i = 1; i <= n; i ++ )
		if ( color[i] == -1 ) 
			dfs(i, 0);
	for ( int i = 1; i <= m1; i ++ ) {
		if ( color[player1[i].a] == 1 )
			swap(player1[i].a, player1[i].b);
		int a = player1[i].a, b = player1[i].b;
		solve1::addEdge(OV(a), IV(b), 1, -1, i);
	}
	for ( int i = 1; i <= m2; i ++ ) {
		if ( color[player2[i].a] == 1 )
			swap(player2[i].a, player2[i].b);
		int a = player2[i].a, b = player2[i].b;
		solve1::addEdge(OV(b), IV(a), 1, -1, m1+i);
	}
	for ( int i = 1; i <= n; i ++ )
		solve1::addEdge(IV(i), OV(i), 1, 0, -1);

	solve1::main(2*n);
	for ( int i = 0; i < solve1::edgeCnt; i ++ ) {
		Edge *e = solve1::edge + i;
		if ( e->flow ) {
			int u = e->from, v = e->to;
			if ( e->id != -1 ) {
				if ( e->id <= m1 ) 
					ans1[nAns1++] = mp(RET(u), RET(v));
				else if ( e->id <= m1+m2 )
					ans2[nAns2++] = mp(RET(u), RET(v));
			}
		}
	}
	assert(nAns1 == nAns2);
	printf("%d\n", nAns1);
	for ( int i = 0; i < nAns1; i ++ )
		printf("%d %d\n", ans1[i].first, ans1[i].second);
	for ( int i = 0; i < nAns2; i ++ )
		printf("%d %d\n", ans2[i].first, ans2[i].second);
#undef IV
#undef OV
#undef RET
}
