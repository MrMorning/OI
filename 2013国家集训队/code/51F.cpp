#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kEdgeMax = 100010, kVtxMax = 2010;

struct Edge {
	int to;
	bool mk;
	Edge *next, *inv;
} edge[kEdgeMax * 2], *begin[kVtxMax];
int edgeCnt = 0;
vector<int> adj[kVtxMax];
int low[kVtxMax], dfn[kVtxMax];
int belong[kVtxMax];
int mem[kVtxMax], nMem;
int size[kVtxMax], nLeaf[kVtxMax];
bool vis[kVtxMax];
int n, m;

Edge *makeEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
	return e;
}

void addEdge(int u, int v) {
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inv = e2, e2->inv = e1;
}


void tarjan(int x, Edge *pe) {
	static int timeStamp = 1;
	dfn[x] = low[x] = timeStamp++;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->inv != pe ) {
			int y = e->to;
			if ( !dfn[y] ) {
				tarjan(y, e);
				low[x] = min(low[x], low[y]);
				if ( low[y] > dfn[x] )
					e->mk = e->inv->mk = true;
			} else {
				low[x] = min(low[x], dfn[y]);
			}
		}
}

void findComp(int x) {
	vis[x] = true;
	mem[nMem++] = x;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( !e->mk && !vis[e->to] )
			findComp(e->to);	
}
void findComp2(int x) {
	vis[x] = true;
	mem[nMem++] = x;
	foreach( it, adj[x] )
		if ( !vis[*it] )
			findComp2(*it);	
}

void prepare(int x, int fa) {
	size[x] = 1;
	if ( !adj[x].size() || (adj[x].size()==1 && adj[x][0] == fa) )
		nLeaf[x] = 1;
	else nLeaf[x] = 0;

	foreach ( it, adj[x] ) 
		if ( *it != fa ) {
			prepare(*it, x);
			size[x] += size[*it];
			nLeaf[x] += nLeaf[*it];
		}
}

void statAns(int x, int fa, int acc, int &res ) {
	if ( nLeaf[x] == size[x] ) {
		res = min(res, acc);
		return;
	}
	foreach ( it, adj[x] )
		if ( *it != fa ) 
			acc += size[*it] - nLeaf[*it];
	foreach ( it, adj[x] )
		if ( *it != fa ) 
			statAns(*it, x, acc-(size[*it]-nLeaf[*it]), res);
}

int workOnTree(int rt) {
	prepare(rt, 0);
	int res = n;
	statAns(rt, 0, 0, res);
	return res;
}

int solve(int rt) {
	nMem = 0;
	findComp2(rt);
	int tmp = n;
	for ( int i = 0; i < nMem; i ++ )
		tmp = min(tmp, workOnTree(mem[i]));
	return tmp;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= m; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( dfn[i] == 0 )
			tarjan(i, NULL);
	}

	int ans = 0;
	for ( int i = 1; i <= n; i ++ ) 
		if ( !vis[i] ) {
			nMem = 0;
			findComp(i);
			for ( int t = 0; t < nMem; t ++ ) 
				belong[mem[t]] = i;
			ans += nMem - 1;
		}
	for ( int i = 0; i < edgeCnt; i += 2 ) {
		Edge *e1 = edge + i,
			 *e2 = edge + i + 1;
		if ( e1->mk ) {
			adj[belong[e1->to]].push_back(belong[e2->to]);
			adj[belong[e2->to]].push_back(belong[e1->to]);
		}
	}

	memset(vis, 0, sizeof(vis));
	for ( int i = 1; i <= n; i ++ )
		if ( belong[i] == i && !vis[i] ) {
			ans += solve(i);
			ans++;
		}
	ans--;
	printf("%d\n", ans);
}
