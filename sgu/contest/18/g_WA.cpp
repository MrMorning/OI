#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int NODE_MAX = 200010;
struct Edge {
	int to, w;
	Edge *next, *inv;
} edge[NODE_MAX * 2], *begin[NODE_MAX];
int edgeCnt = 0;
int f[NODE_MAX], father[NODE_MAX], depth[NODE_MAX];
int Q[NODE_MAX];
int n;

Edge *makeEdge(int u, int v, int w) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], e->w = w;
	return begin[u] = e;
}
void addEdge(int u, int v, int w) {
	Edge *e1 = makeEdge(u, v, w),
		 *e2 = makeEdge(v, u, w);
	e1->inv = e2, e2->inv = e1;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n - 1; i ++ ) {
		static char ts[50];
		int a, b;
		scanf("%d%d", &a, &b);
		scanf("%s", ts);
		if ( ts[0] == 'a' ) {
			addEdge(a, b, 0);
			scanf("%*s");
		} else
			addEdge(a, b, 1);
	}
	int qt = 0;
	Q[qt ++] = 1;
	memset(father, 0, sizeof(father));
	memset(f, 0, sizeof(f));
	memset(depth, 0, sizeof(depth));
	int ans = 0;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		assert(f[u] * 2 >= depth[u]);
		for ( Edge *e = begin[u]; e; e = e->next )
			if ( e->to != father[u] ) {
				int v = e->to;
				depth[v] = depth[u] + 1;
				father[v] = u;
				if ( (f[u] + e->w) * 2 >= depth[v] ) 
					f[v] = f[u] + e->w;
				else {
					if ( depth[v] == 1 ) 
						f[v] = 1;
					else {
						f[u] ++;
						f[v] = f[u] + e->w;
					}
					ans ++;
				}
				assert(f[v] * 2 >= depth[v]);
				Q[qt ++] = v;
			}
	}
	printf("%d\n", ans);
	for ( int i = 0; i < edgeCnt; i += 2 ) {
		int id = i / 2 + 1;
		int u = (edge + i)->to,
			v = (edge + i)->inv->to;
		if ( father[u] == v )
			swap(u, v);
		assert(father[v] == u);
		if ( !(edge + i)->w )
			if ( f[u] != f[v] )
				printf("%d ", id);	
	}
}
