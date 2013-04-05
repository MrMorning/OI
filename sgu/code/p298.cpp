#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
const int VTX_MAX = 10010;
const int EDGE_MAX = 160010;
struct Edge {
	int from, to, cost;
	Edge *next;
};

namespace prework {
	Edge edge[EDGE_MAX], *begin[VTX_MAX];
	int edgeCnt = 0;
	vector<int> scc[VTX_MAX];
	int nScc;
	int belong[VTX_MAX];
	int low[VTX_MAX], dfn[VTX_MAX];

	int nVtx, nEdge;

	void addEdge(int u, int v, int c) {
		Edge *e = edge + edgeCnt++;
		e->from = u, e->to = v, e->next = begin[u], e->cost = c;
		begin[u] = e;
	}

	void tarjan(int x) {
		static int timeStamp = 0;
		static int top = 0;
		static int stk[VTX_MAX];
		static bool inStk[VTX_MAX];

		low[x] = dfn[x] = ++timeStamp;
		stk[top ++] = x;
		inStk[x] = true;

		for ( Edge *e = begin[x]; e; e = e->next )
			if ( e->cost == 0 ) {
				int y = e->to;
				if ( !dfn[y] ) {
					tarjan(y);
					low[x] = min(low[x], low[y]);
				} else if ( inStk[y] ) 
					low[x] = min(low[x], dfn[y]);
			}

		if ( low[x] == dfn[x] ) {
			while ( 1 ) {
				int u = stk[-- top];
				belong[u] = nScc;
				scc[nScc].push_back(u);
				inStk[u] = false;
				if ( u == x )
					break;
			}
			nScc ++;
		}
	}

	void main() {
		scanf("%d%d", &nVtx, &nEdge);
		while ( nEdge -- ) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u --, v --;
			addEdge(v, u, w);
		}
		for ( int i = 0; i < nVtx; i ++ )
			if ( !dfn[i] )
				tarjan(i);
	}
}

namespace negaJudge {
	Edge edge[EDGE_MAX], *begin[VTX_MAX];
	int edgeCnt = 0;

	vector<int> scc[VTX_MAX];
	int nScc;
	int belong[VTX_MAX];
	int nVtx, nEdge;
	int low[VTX_MAX], dfn[VTX_MAX];

	void addEdge(int u, int v, int c) {
		Edge *e = edge + edgeCnt++;
		e->to = v, e->from = u, e->next = begin[u], e->cost = c;
		begin[u] = e;
	}

	void tarjan(int x) {
		static int timeStamp = 0;
		static int top = 0;
		static int stk[VTX_MAX];
		static bool inStk[VTX_MAX];

		low[x] = dfn[x] = ++timeStamp;
		stk[top ++] = x;
		inStk[x] = true;

		for ( Edge *e = begin[x]; e; e = e->next ) {
				int y = e->to;
				if ( !dfn[y] ) {
					tarjan(y);
					low[x] = min(low[x], low[y]);
				} else if ( inStk[y] ) 
					low[x] = min(low[x], dfn[y]);
			}

		if ( low[x] == dfn[x] ) {
			while ( 1 ) {
				int u = stk[-- top];
				belong[u] = nScc;
				scc[nScc].push_back(u);
				inStk[u] = false;
				if ( u == x )
					break;
			}
			nScc ++;
		}
	}

	void main() {
		nVtx = prework::nScc;
		for ( int i = 0; i < prework::edgeCnt; i ++ ) {
			Edge *e = &prework::edge[i];
			int u = prework::belong[e->from],
				v = prework::belong[e->to];
			if ( u != v )
				addEdge(u, v, e->cost);
		}
		for ( int i = 0; i < nVtx; i ++ )
			if ( !dfn[i] ) 
				tarjan(i);
		for ( int i = 0; i < nScc; i ++ )
			if ( scc[i].size() > 1 ) {
				puts("-1");
				exit(0);
			}
	}
}

namespace topsort {
	Edge edge[EDGE_MAX], *begin[VTX_MAX];
	int dist[VTX_MAX], dist2[VTX_MAX], inDgr[VTX_MAX];

	int nVtx, edgeCnt, src;
	int stk[VTX_MAX], top = 0;
	int que[VTX_MAX];
	vector<pair<int, int> > inv[VTX_MAX];

	void addEdge(int u, int v, int c) {
		Edge *e = edge + edgeCnt++;
		e->to = v, e->from = u, e->next = begin[u], e->cost = c;
		begin[u] = e;
	}

	void output() {
		for ( int i = 0; i < prework::nVtx; i ++ )
			printf("%d ", dist[prework::belong[i]]);
	}

	void generate() {
		memset(inDgr, 0, sizeof(inDgr));
		for ( int i = 0; i < edgeCnt; i ++ ) {
			Edge *e = edge + i;
			inv[e->to].push_back(make_pair(e->from, e->cost));
			inDgr[e->from] ++;
		}
		top = 0;
		memset(dist2, 0x3f, sizeof(dist2));
		for ( int i = 0; i < nVtx; i ++ ) 
			if ( inDgr[i] == 0 ) {
				stk[top ++] = i;
				dist2[i] = min(dist2[i], 10000);
			}
		while ( top ) {
			int u = stk[-- top];
			foreach(it, inv[u]) {
				int v = it->first;
				inDgr[v] --;
				dist2[v] = min(dist2[v], dist2[u] - it->second);
				if ( inDgr[v] == 0 ) 
					stk[top ++] = v;
			}
		}

		dist[prework::belong[0]] = dist2[prework::belong[0]];
		int qt = 0;
		que[qt ++] = prework::belong[0];
		for ( int qh = 0; qh < qt; qh ++ ) {
			int u = que[qh];
			for ( Edge *e = begin[u]; e; e = e->next ) {
				int v = e->to;
				dist[v] = max(dist[v], dist[u] + e->cost);
				que[qt ++] = v;
			}
		}
		output();
	}

	void main() {
		memcpy(edge, negaJudge::edge, sizeof(negaJudge::edge));
		memcpy(begin, negaJudge::begin, sizeof(negaJudge::begin));
		nVtx = negaJudge::nVtx;
		edgeCnt = negaJudge::edgeCnt;

		memset(dist, -0x3f, sizeof(dist));
		src = nVtx;
		dist[src] = -10000;
		for ( int i = 0; i < nVtx; i ++ )
			addEdge(src, i, 0);
		for ( int i = 0; i < edgeCnt; i ++ ) {
			Edge *e = edge + i;
			inDgr[e->to] ++;
		}

		stk[top ++] = src;
		while ( top ) {
			int u = stk[-- top];
			for ( Edge *e = begin[u]; e; e = e->next ) {
				int v = e->to;
				inDgr[v] --;
				dist[v] = max(dist[v], dist[u] + e->cost);
				if ( inDgr[v] == 0 ) 
					stk[top ++] = v;
			}
		}

		for ( int i = 0; i < nVtx; i ++ )
			if ( dist[i] > 10000 ) {
				puts("-1");
				exit(0);
			}

		generate();
	}
}

int main() {
	prework::main();
	negaJudge::main();
	topsort::main();
}
