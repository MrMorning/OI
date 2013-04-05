#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kNMax = 50010;
const int kVMax = 66666;
const int kInf = 0x3f3f3f3f;

struct Edge {
	int to;
	bool ok;
	Edge *next, *inv;
} edge[kNMax * 2], *begin[kNMax];
int edgeCnt = 0;
int n;
int val[kNMax];
int sz[kNMax], fa[kNMax];
int cur[kNMax], nCur;
int son[kNMax], nSon;
pair<int, int> mem[kNMax];
int nMem;
ll ans = 0;

Edge *makeEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], e->ok = true;
	return begin[u] = e;
}

void addEdge(int u, int v) {
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inv = e2, e2->inv = e1;
}

void dfs(int x, int a, int b, int p) {
	a = min(val[x], a);
	b ++;
	ans = max(ans, (ll)a * b);
	if ( (ll)a * n < ans ) return;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->ok && e->to != p )
			dfs(e->to, a, b, x);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d", &val[i]);
		ans = max(ans, (ll)val[i]);
	}
	for ( int i = 0; i < n-1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;
		addEdge(a, b);
	}
	for ( int i = 0; i < n; i ++ )
		dfs(i, kInf, 0, -1);
	printf("%lld\n", ans);
}
