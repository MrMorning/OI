#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
typedef set<int>::iterator itr_t;

const int kNMax = 100010;
const int kLogMax = 20;

ll dist[kNMax];
int seq[kNMax], nSeq;
int anc[kNMax][kLogMax];
int pos[kNMax];
int dep[kNMax];

struct Edge {
	int to, len;
	Edge *next;
} edge[kNMax*2], *begin[kNMax];
int edgeCnt = 0;

void addEdge(int u, int v, int c) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->len = c, e->next = begin[u];
	begin[u] = e;
}

struct cmpPos {
	bool operator() (int i, int j) const {
		return pos[i] < pos[j];
	}
};
set<int, cmpPos> S;

void dfs(int i, int p) {
	anc[i][0] = p;
	for ( int k = 1; k < kLogMax; k ++ )
		if ( anc[i][k-1] )
			anc[i][k] = anc[anc[i][k-1]][k-1];
	seq[++nSeq] = i;
	for ( Edge *e = begin[i]; e; e = e->next ) 
		if ( e->to != p ) {
			dist[e->to] = dist[i] + e->len;
			dep[e->to] = dep[i] + 1;
			dfs(e->to, i);
		}
}

int lca(int u, int v) {
	if ( dep[u] < dep[v] ) swap(u, v);
	int d = dep[u] - dep[v];
	for ( int k = 0; k < kLogMax; k++ )
		if ( d & (1 << k) )
			u = anc[u][k];
	if ( u == v ) return u;
	for ( int k = kLogMax-1; k >= 0; k -- )
		if ( anc[u][k] != anc[v][k] )
			u = anc[u][k], v = anc[v][k];
	return anc[u][0];
}

ll eval(int a, int b) {
	int p = lca(a, b);
	return dist[b]-dist[p];
}

itr_t getNext(itr_t it) {
	it ++;
	if ( it == S.end() ) return S.begin();
	return it;
}

itr_t getPrev(itr_t it) {
	if ( it == S.begin() ) return --S.end();
	return --it;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, q;
	scanf("%d", &n);
	for ( int i = 0; i < n-1; i ++ ) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	dfs(1, 0);
	for ( int i = 1; i <= n; i ++ )
		pos[seq[i]] = i;
	scanf("%d", &q);
	ll ans = 0;
	while ( q -- ) {
		char cmd[3];
		scanf("%s", cmd);
		if ( cmd[0] == '+' ) {
			int x;
			scanf("%d", &x);
			if ( S.size() == 0 ) 
				S.insert(x);
			else {
				itr_t nxt = S.lower_bound(x), pre;
				if ( nxt == S.end() ) nxt = S.begin();
				pre = getPrev(nxt);
				ans -= eval(*pre, *nxt);
				ans += eval(*pre, x);
				ans += eval(x, *nxt);
				S.insert(x);
			}
		} else if ( cmd[0] == '-' ) {
			int x;
			scanf("%d", &x);
			if ( S.size() == 1 ) 
				S.clear(); 
			else {
				itr_t cur = S.lower_bound(x),
					  nxt = getNext(cur), pre = getPrev(cur);
				ans -= eval(*pre, *cur);
				ans -= eval(*cur, *nxt);
				ans += eval(*pre, *nxt);
				S.erase(cur);
			}
		} else 
			printf(LL_FMT "\n", ans);
	}
}
