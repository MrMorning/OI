#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;

const int V_MAX = 500010, E_MAX = 500010;
const int inf = 0x3f3f3f3f;

struct Edge {
	int to;
	Edge *next;
} edge[E_MAX], *begin[V_MAX];

int belong[V_MAX], low[V_MAX], dfn[V_MAX];
int tarStk[V_MAX];
bool inTarStk[V_MAX];
int tarStkTop = 0;

bool dpDone[V_MAX];
int dpMemo[V_MAX];
int nScc, sccWeight[V_MAX], crossWeight[V_MAX];
vector<int> sccFrom[V_MAX];
int center, nCross, nRoad, nBar;

void addEdge(int u, int v) {
	static int edgeCnt = 0;
	Edge *e = edge + edgeCnt ++;
	e->to = v, e->next = begin[u]; begin[u] = e;
}

void tarjan(int x) {
	static int timeStamp = 0;
	low[x] = dfn[x] = timeStamp ++;
	tarStk[tarStkTop ++] = x;
	inTarStk[x] = true;

	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( dfn[y] == -1 ) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if ( inTarStk[y] ) 
			low[x] = min(low[x], dfn[y]);
	}

	if ( low[x] == dfn[x] ) {
		while ( 1 ) {
			int t = tarStk[-- tarStkTop];
			inTarStk[t] = false;
			belong[t] = nScc;
			if ( t == x )
				break;
		}
		nScc ++;
	}
}

int dp(int x) {
	if ( dpDone[x] )
		return dpMemo[x];
	dpDone[x] = true;
	int &res = dpMemo[x] = -inf;

	if ( x == belong[center] )
		return res = sccWeight[x];

	FOREACH(it, sccFrom[x])
		res = max(res, dp(*it) + sccWeight[x]);
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nCross, &nRoad);
	while ( nRoad -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
	}
	for ( int i = 1; i <= nCross; i ++ )
		scanf("%d", &crossWeight[i]);
	memset(dfn, -1, sizeof(dfn));
	for ( int i = 1; i <= nCross; i ++ )
		if ( dfn[i] == -1 )
			tarjan(i);

	for ( int i = 1; i <= nCross; i ++ ) {
		sccWeight[belong[i]] += crossWeight[i];
		for ( Edge *e = begin[i]; e; e = e->next ) {
			if ( belong[e->to] != belong[i] ) 
				sccFrom[belong[e->to]].push_back(belong[i]);
		}
	}

	int ans = 0;

	scanf("%d%d", &center, &nBar);
	for ( int i = 0; i < nBar; i ++ ) {
		int bar;
		scanf("%d", &bar);
		ans = max(ans, dp(belong[bar]));
	}

	printf("%d\n", ans);
}
