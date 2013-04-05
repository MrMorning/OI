#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#define pb(x) push_back(x);
#define mp(x, y) make_pair(x, y)
using namespace std;

const int kNMax = 4010;
const int kLMax = 20;

struct Info {
	//u-->v
	int u, v, w;
	bool operator< (const Info &T) const {
		return w < T.w || (w == T.w
				&& (u < T.u
					|| (u == T.u && v < T.v)));
	}
	Info(){}
	Info(int uu, int vv, int ww):
		u(uu), v(vv), w(ww){}
};

struct Node {
	Node *ch[2];
	Info val;
} *heap[kNMax];

int anc[kLMax][kNMax];
int dep[kNMax];
vector<pair<int, int> > memo[kNMax], adj[kNMax];
int n, m;
int ans[kNMax];
int Q[kNMax];
int father[kNMax], dist[kNMax];

Node *alloc(int u, int v, int w) {
	Node *x = new Node;
	x->val = Info(u, v, w);
	x->ch[0] = x->ch[1] = NULL;
	return x;
}

Node *merge(Node *p, Node *q) {
	if ( p == NULL ) return q;
	if ( q == NULL ) return p;
	if ( q->val < p->val ) swap(p, q);
	int t = rand()&1;
	p->ch[t] = merge(p->ch[t], q);
	return p;
}

void delMin(Node *&p) {
	p = merge(p->ch[0], p->ch[1]);
}

void dfs(int x) {
	if ( anc[0][x] ) 
		dep[x] = dep[anc[0][x]] + 1;
	for ( int k = 1; k < kLMax; k ++ )
		if ( anc[k-1][x] )
			anc[k][x] = anc[k-1][anc[k-1][x]];
	foreach(it, adj[x])
		if ( it->first != anc[0][x] ) {
			anc[0][it->first] = x;
			dfs(it->first);
		}
}

bool isAncestor(int a, int b) {
	int d = dep[b]-dep[a];
	if ( d < 0 ) return false;
	for ( int k = 0; k < kLMax; k ++ )
		if ( d & (1<<k) )
			b = anc[k][b];
	return a == b;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= m; i ++ ) {
		int a, b, l, t;
		scanf("%d%d%d%d", &a, &b, &l, &t);
		if ( t == 0 ) {
			memo[a].pb(mp(b, l));
			memo[b].pb(mp(a, l));
		} else {
			adj[a].pb(mp(b, l));
			adj[b].pb(mp(a, l));
		}
	}

	dfs(1);

	int qt = 0;
	Q[qt++] = 1;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		foreach(it, adj[u])
			if ( it->first != father[u] ) {
				Q[qt++] = it->first;
				father[it->first] = u;
				dist[it->first] = dist[u] + it->second;
			}
	}

	for ( int i = qt-1; i >= 0; i-- ) {
		int x = Q[i];
		foreach(it, memo[x]) {
			heap[x] = merge(heap[x], alloc(x, it->first, dist[x]+dist[it->first]+it->second));
		}
		while ( 1 ) {
			if ( heap[x] == NULL ) {
				ans[x] = -1;
				break;
			}
			Info info = heap[x]->val;
			assert(isAncestor(x, info.u));
			if ( isAncestor(x, info.v) )
				delMin(heap[x]);
			else {
				ans[x] = -dist[x] + info.w;
				break;
			}
		}
		if ( father[x] != -1 )
			heap[father[x]] = merge(heap[father[x]], heap[x]);
	}
	for ( int i = 2; i <= n; i ++ )
		printf("%d ", ans[i]);
}
