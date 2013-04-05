#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int kInf = 0x3f3f3f3f;
const int kVtxMax = 500;
const int kEdgeMax = kVtxMax * kVtxMax * 2;

struct Edge {
	int to, cap, cost;
	Edge *next, *inv;
} edge[kEdgeMax], *begin[kVtxMax], *prev[kVtxMax];
int edgeCnt = 0;
int dist[kVtxMax];
bool inQ[kVtxMax];
int Q[kVtxMax];
int src, sink, st, en, nVtx;

Edge *makeEdge(int u, int v, int c, int f) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->cost = f, e->cap = c;
	e->next = begin[u], begin[u] = e;
	return e;
}
void addEdge(int u, int v, int c, int f) {
	f *= -1;
	Edge *e1 = makeEdge(u, v, c, f),
		 *e2 = makeEdge(v, u, 0, -f);
	e1->inv = e2, e2->inv = e1;
}

bool spfa() {
	static int Q[kVtxMax];
	memset(prev, 0, sizeof(prev));
	memset(dist, 0x3f, sizeof(dist));
	memset(inQ, 0, sizeof(inQ));
	dist[src] = 0;
	inQ[src] = true;
	int qh = 0, qt = 0;
	Q[qt++] = src;
	while ( qh != qt ) {
		int u = Q[qh];
		qh = (qh + 1) % kVtxMax;
		inQ[u] = false;
		for ( Edge *e = begin[u]; e; e = e->next )
			if ( e->cap ) {
				int v = e->to;
				int tmp = e->cost + dist[u];
				if ( dist[v] > tmp ) {
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
	int ret = 0;
	while ( spfa() ) {
		int flow = kInf;
		for ( Edge *e = prev[sink]; e; e = prev[e->inv->to] ) 
			flow = min(flow, e->cap);
		ret += flow * dist[sink];
		for ( Edge *e = prev[sink]; e; e = prev[e->inv->to] ) {
			e->cap -= flow;
			e->inv->cap += flow;
		}
	}
	return ret;
}

int N, M, K, T;
int t[222][222], f[222][222];
struct Order {
	int a, b, c, s, t;
} order[222];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &K, &T);
	for ( int i = 0; i < N; i ++ )
		for ( int j = 0; j < N; j ++ )
			scanf("%d", &t[i][j]);
	for ( int i = 0; i < N; i ++ )
		for ( int j = 0; j < N; j ++ )
			scanf("%d", &f[i][j]);
	for ( int i = 0; i < M; i ++ ) {
		scanf("%d%d%d%d%d", &order[i].a, &order[i].b,
				&order[i].s, &order[i].t, &order[i].c);
	}
	nVtx = M;
	st = nVtx++, en = nVtx++;
	for ( int i = 0; i < M; i ++ ) {
		if ( t[0][order[i].a] <= order[i].s )
			addEdge(st, i, 1, order[i].c-f[0][order[i].a]);
		if ( order[i].t + t[order[i].b][0] <= T )
			addEdge(i, en, 1, -f[order[i].b][0]);
	}
	for ( int i = 0; i < M; i ++ )
		for ( int j = 0; j < M; j ++ )
			if ( order[j].s - order[i].t >= t[order[i].b][order[j].a] ) 
				addEdge(i, j, 1, order[j].c-f[order[i].b][order[j].a]);
	src = nVtx++, sink = en;
	addEdge(src, st, K, 0);

	printf("%d\n", -mcmf());
}
