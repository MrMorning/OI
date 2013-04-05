#include <cstdio>
#include <cstring>
const int VTX_MAX = 505;
const int EDGE_MAX = 500010;
struct Edge {
	int to, id;
	bool used;
	Edge *next, *inv;
} edge[EDGE_MAX], *begin[VTX_MAX], *stk[EDGE_MAX];
int edgeCnt = 0;
bool vis[VTX_MAX];
int link[VTX_MAX][VTX_MAX];
int match[VTX_MAX];
int top;
int N, K;

Edge *makeEdge(int u, int v, int id) {
	Edge *e = edge + edgeCnt ++;
	e->to = v, e->id = id, e->next = begin[u];
	return begin[u] = e;
}

void addEdge(int u, int v, int id) {
	Edge *e1 = makeEdge(u, v, id),
		 *e2 = makeEdge(v, u, id);
	e1->inv = e2, e2->inv = e1;
}

void dfs(int x) {
	vis[x] = true;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( !e->used ) {
			e->used = e->inv->used = true;
			int y = e->to;
			dfs(y);
			stk[top++] = e;
		}
}

bool aug(int x) {
	for ( int y = 1; y <= N; y ++ ) 
		if ( link[x][y] && !vis[y] ) {
			vis[y] = true;
			if ( !match[y] || aug(match[y]) ) {
				match[y] = x;
				return true;
			}
		}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 1; i <= N * K / 2; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b, i);
	}
	for ( int i = 1; i <= N; i ++ )
		if ( !vis[i] ) 
			dfs(i);

	for ( int i = 0; i < top; i ++ ) 
		link[stk[i]->inv->to][stk[i]->to] = stk[i]->id;
	int matchCnt = 0;
	for ( int i = 1; i <= N; i ++ ) {
		memset(vis, 0, sizeof(vis));
		matchCnt += aug(i);
	}
	if ( matchCnt < N )
		printf("NO\n");
	else {
		printf("YES\n");
		for ( int i = 1; i <= N; i ++ )
			printf("%d\n", link[match[i]][i]);
	}
}
