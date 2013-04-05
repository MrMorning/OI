#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

int N, M;
int ed[111][111];
vector<int> adj[111];
bool marked[111], incycle[111], instk[111];
int dgr[111];
int low[111], dfn[111];
int size = 0;
bool vis2[111];

struct Edge {
	int to;
	bool isB;
	Edge *next, *inv;
} edge[2222], *begin[111];

Edge *makeEdge(int u, int v) {
	static int edgeCnt = 0;
	Edge *e = edge + edgeCnt ++;
	e->to = v, e->next = begin[u];
	e->isB = false;
	begin[u] = e;
	return e;
}

void addDoubleEdge(int u, int v) {
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inv = e2, e2->inv = e1;
}

void dfs(int i) {
	marked[i] = true;
	for ( int k = 0; k < (int)adj[i].size(); k ++ ) {
		int t = adj[i][k];
		if ( !marked[t] )
			dfs(t);
	}
}

void tarjan(int u, Edge *pe) {
	static int timeStamp = 0;
	low[u] = dfn[u] = ++ timeStamp;
	for ( Edge *e = begin[u]; e; e = e->next )
		if ( e->inv != pe ) {
			int v = e->to;
			if ( !dfn[v] ) {
				tarjan(v, e);
				low[u] = min(low[u], low[v]);
				if ( low[v] > dfn[u] ) 
					e->isB = e->inv->isB = true;
			} else if ( dfn[v] < dfn[u] ) {
				assert(dfn[v] < dfn[u]);
				low[u] = min(low[u], dfn[v]);
			}
		}
}

void dfs2(int u) {
	size ++;
	vis2[u] = true;
	for ( Edge *e = begin[u]; e; e = e->next )
		if ( !e->isB && !vis2[e->to])
			dfs2(e->to);
}

void topsort() {
	for ( int i = 1; i <= N; i ++ )
		incycle[i] = true;
	memset(dgr, 0, sizeof(dgr));
	memset(instk, 0, sizeof(instk));
	for ( int i = 1; i <= N; i ++ ) 
		dgr[i] = adj[i].size();

	static int stk[111];
	int top = 0;
	for ( int i = 1; i <= N; i ++ )
		if ( dgr[i] == 0 )
			incycle[i] = false;
		else if ( dgr[i] == 1 ) {
			stk[top ++] = i;
			instk[i] = true;
		}

	while ( top ) {
		int u = stk[-- top];
		incycle[u] = false;
		for ( int k = 0; k < (int)adj[u].size(); k ++ ) {
			int v = adj[u][k];
			dgr[v] --;
			if ( dgr[v] <= 1 && !instk[v] ) {
				instk[v] = true;
				stk[top ++] = v;
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for ( int i = 1; i <= M; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		if ( u > v )
			swap(u, v);
		ed[u][v] ++;
		adj[u].push_back(v);
		adj[v].push_back(u);
		addDoubleEdge(u, v);
	}
	dfs(1);
	tarjan(1, NULL);
	dfs2(1);
	if ( size != 2 ) {
		if ( size == 1 && adj[1].size() > 0)
			marked[1] = false;
		for ( int i = 1; i <= N; i ++ )
			if ( marked[i] )
			   printf("%d ", i);	
		return 0;
	}
	int t = 0;
	for ( int i = 2; i <= N; i ++ )
		if ( ed[1][i] > 1 ) {
			t = i;
			break;
		}
	assert(t != 0);
	if ( t != 0 ) {
		for ( int i = 0; i < (int)adj[1].size(); i ++ ) 
			if ( adj[1][i] == t ) {
				swap(adj[1][i], adj[1].back());
				adj[1].pop_back();
				i --;
			}
		for ( int i = 0; i < (int)adj[t].size(); i ++ ) 
			if ( adj[t][i] == 1 ) {
				swap(adj[t][i], adj[t].back());
				adj[t].pop_back();
				i --;
			}
		topsort();
		marked[1] = marked[t] = false;
		if ( incycle[t] || ed[1][t] % 2 == 1 )
			marked[t] = true;
		if ( incycle[t] || ed[1][t] % 2 == 0 )
			marked[1] = true;
	}
	for ( int i = 1; i <= N; i ++ )
		if ( marked[i] )
			printf("%d ", i);
}
