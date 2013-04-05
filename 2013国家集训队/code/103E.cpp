#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kVMax = 333;
const int kEMax = kVMax*kVMax*2;
const int kInf = 0x3f3f3f3f;

struct Edge {
	int to, cap;
	Edge *next, *inv;
} edge[kEMax], *begin[kVMax];
int edgeCnt = 0;
int src, sink;

Edge *makeEdge(int u, int v, int cap) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->cap = cap, e->next = begin[u];
	return begin[u] = e;
}

void addEdge(int u, int v, int cap) {
	Edge *e1 = makeEdge(u, v, cap),
		 *e2 = makeEdge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
}

int dist[kVMax];
vector<int> adj[kVMax];
int match[kVMax];
bool vis[kVMax];

bool prelable() {
	static int Q[kVMax];
	int qt = 0;
	Q[qt++] = src;
	memset(dist, -1, sizeof(dist));
	dist[src] = 0;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		for ( Edge *e = begin[u]; e; e = e->next ) 
			if ( e->cap ) {
				int v = e->to;
				if ( dist[v] != -1 ) continue;
				dist[v] = dist[u] + 1;
				Q[qt++] = v;
			}
	}
	return dist[sink] != -1;
}

int findAug(int cur, int flow) {
	if ( cur == sink ) return flow;
	Edge *e;
	int res = 0;
	for ( e = begin[cur]; e; e = e->next ) 
		if ( e->cap && dist[e->to] == dist[cur] + 1 ) {
			int tmp = findAug(e->to, min(e->cap, flow));
			flow -= tmp;
			res += tmp;
			e->cap -= tmp, e->inv->cap += tmp;
			if ( !flow ) break;
		}
	if ( !e ) 
		dist[cur] = -1;
	return res;
}

int dinic() {
	int res = 0;
	while ( prelable() )
		res += findAug(src, kInf);
	return res;
}

bool dfs(int x) {
	foreach(it, adj[x]) {
		int y = *it;
		if ( !vis[y] ) {
			vis[y] = true;
			if ( match[y] == -1 || dfs(match[y]) ) {
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}

int n, m[kVMax][kVMax], val[kVMax];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &m[i][0]);
		for ( int j = 1; j <= m[i][0]; j ++ ) {
			scanf("%d", &m[i][j]);
			adj[i].push_back(m[i][j]);
		}
	}
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &val[i]);
		val[i] *= -1;
	}
	memset(match, -1, sizeof(match));
	for ( int i = 1; i <= n; i ++ ) {
		memset(vis, 0, sizeof(vis));
		dfs(i);
	}

	for ( int i = 1; i <= n; i ++ ) {
		for ( int j = 1; j <= m[i][0]; j ++ )
			if ( match[m[i][j]] != i ) 
				addEdge(i, match[m[i][j]], kInf);
	}
	src = n+1, sink = n+2;
	int ans = 0;
	for ( int i = 1; i <= n; i ++ ) {
		if ( val[i] < 0 )
			addEdge(i, sink, -val[i]);
		else if ( val[i] > 0 ) {
			addEdge(src, i, val[i]);
			ans += val[i];
		}
	}
	ans -= dinic();
	printf("%d\n", -ans);
}
