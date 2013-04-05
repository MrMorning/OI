#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int NODE_MAX = 200010;
struct Edge {
	int to, w, id;
	Edge *next, *inv;
} edge[NODE_MAX * 2], *begin[NODE_MAX];
int edgeCnt = 0;
int father[NODE_MAX], depth[NODE_MAX];
int choose[NODE_MAX], maxNeed[NODE_MAX];
int n;

Edge *makeEdge(int u, int v, int w, int id) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], e->w = w;
	e->id = id;
	return begin[u] = e;
}
void addEdge(int u, int v, int w, int id) {
	Edge *e1 = makeEdge(u, v, w, id),
		 *e2 = makeEdge(v, u, w, id);
	e1->inv = e2, e2->inv = e1;
}

void dfs1(int x, int acc) {
	maxNeed[x] = (depth[x] + 1) / 2 - acc;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->to != father[x] ) {
			father[e->to] = x;
			depth[e->to] = depth[x] + 1;
			dfs1(e->to, acc + e->w);
			maxNeed[x] = max(maxNeed[x], maxNeed[e->to]);
		}
}

void dfs2(int x, int acc) {
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->to != father[x] ) {
			if ( e->w == 0 && maxNeed[e->to] - acc > 0 ) {
				choose[e->id] = true;
				dfs2(e->to, acc + 1);
			} else
				dfs2(e->to, acc);
		}
}

int main() {
	scanf("%d", &n);
	for ( int i = 0; i < n - 1; i ++ ) {
		static char ts[50];
		int a, b;
		scanf("%d%d", &a, &b);
		scanf("%s", ts);
		if ( ts[0] == 'a' ) {
			addEdge(a, b, 0, i);
			scanf("%s", ts);
		} else
			addEdge(a, b, 1, i);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	int ans = 0;
	for ( int i = 0; i < n - 1; i ++ )
		if ( choose[i] )
			ans ++;
	printf("%d\n", ans);
	for ( int i = 0; i < n - 1; i ++ )
		if ( choose[i] )
			printf("%d ", i + 1);
	
}
