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

struct IndexTree {
	int ele[kVMax];
	void init() { 
		for ( int i = 0; i < kVMax; i ++ ) ele[i] = -kInf;
	}
	void add(int i, int v) {
		i = kVMax - 1 - i;
		for ( ; i < kVMax; i += i & -i )
			ele[i] = max(ele[i], v);
	}
	int ask(int i) {
		i = kVMax - 1 - i;
		int ret = -kInf;
		for ( ; i; i -= i & -i )
			ret = max(ret, ele[i]);
		return ret;
	}
	void clear(int i) {
		i = kVMax - 1 - i;
		for ( ; i < kVMax; i += i & -i )
			ele[i] = -kInf;
	}
} idt1, idt2;

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

void calcSize(int x) {
	cur[nCur++] = x;
	sz[x] = 1;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->ok && e->to != fa[x] ) {
			fa[e->to] = x;
			calcSize(e->to);
			sz[x] += sz[e->to];
		}
}

void dfs(int x, int a, int b, int p) {
	a = min(val[x], a);
	b ++;
	mem[nMem++] = make_pair(a, b);
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->ok && e->to != p )
			dfs(e->to, a, b, x);
}

void work(int r) {
	nCur = 0;
	fa[r] = -1;
	calcSize(r);
	int totSz = sz[r];
	int best = n + 1, core = -1;
	for ( int i = 0; i < nCur; i ++ ) {
		int x = cur[i], y = totSz - sz[x];
		for ( Edge *e = begin[x]; e; e = e->next )
			if ( e->ok && e->to != fa[x] )
				y = max(y, sz[e->to]);
		if ( y < best ) {
			best = y;
			core = x;
		}	
	}

	nSon = 0;
	for ( Edge *e = begin[core]; e; e = e->next )
		if ( e->ok ) {
			e->ok = e->inv->ok = false;
			son[nSon++] = e->to;
			e->ok = e->inv->ok = true;
		}

	for ( int i = 0; i < nSon; i ++ ) {
		int x = son[i];
		nMem = 0;
		dfs(x, val[core], 1, core);

		for ( int j = 0; j < nMem; j ++ ) {
			ans = max(ans, (ll)mem[j].first * mem[j].second);
			int t = idt1.ask(mem[j].first);
			ans = max(ans, (ll)mem[j].first * (t + mem[j].second - 1));
		}
		for ( int j = 0; j < nMem; j ++ ) 
			idt1.add(mem[j].first, mem[j].second);
	}
	for ( int i = nSon-1; i >= 0; i -- ) {
		int x = son[i];
		nMem = 0;
		dfs(x, val[core], 1, core);

		for ( int j = 0; j < nMem; j ++ ) {
			int t = idt2.ask(mem[j].first);
			ans = max(ans, (ll)mem[j].first * (t + mem[j].second - 1));
		}
		for ( int j = 0; j < nMem; j ++ ) 
			idt2.add(mem[j].first, mem[j].second);
	}
	for ( int i = 0; i < nSon; i ++ ) {
		int x = son[i];
		nMem = 0;
		dfs(x, val[core], 1, core);
		for ( int j = 0; j < nMem; j ++ ) 
			idt1.clear(mem[j].first), idt2.clear(mem[j].first);
	}

	for ( Edge *e = begin[core]; e; e = e->next )
		if ( e->ok ) {
			e->ok = e->inv->ok = false;
			work(e->to);
		}
}

int main() {
	freopen("t.in", "r", stdin);
	idt1.init(); idt2.init();
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
	work(0);
	printf("%lld\n", ans);
}
