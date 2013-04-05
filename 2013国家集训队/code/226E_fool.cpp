#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kVtxMax = 100010;
const int kLogMax = 20;
const int kEventMax = 2 * kVtxMax;
const int kIdtLen = 2 * kVtxMax;

struct Event {
	int a, b, k, y, id, type;
	bool operator< (const Event &T) const {
		return y < T.y || (y == T.y && type < T.type);
	}
} ev[kEventMax];
int nev, nquery, seqL;
vector<int> son[kVtxMax];
int ans[kVtxMax], val[kVtxMax], stamp[kVtxMax];
int depth[kVtxMax], father[kVtxMax];
int pos[kVtxMax][2];
int anc[kVtxMax][kLogMax];

struct IndexTree {
	int ele[kIdtLen];
	int sum(int i) {
		int res = 0;
		for ( ; i; i -= i & -i )
			res += ele[i];
		return res;
	}
	void add(int i, int val) {
		for ( ; i < kIdtLen; i += i & -i )
			ele[i] += val;
	}
} idt;

int askSum(int u, int p) {
	return idt.sum(pos[u][0]) - idt.sum(pos[p][0]) + val[p];
}

int getKth(int u, int k) {
	for ( int d = kLogMax-1; d >= 0; d -- ) 
		if ( anc[u][d] ) {
			int tmp = askSum(u, anc[u][d]) - val[anc[u][d]];
			if ( tmp < k ) {
				k -= tmp;
				u = anc[u][d];
			}
		}
	assert(k == 1);
	return u;
}

int getLCA(int u, int v) {
	if ( depth[u] < depth[v] ) swap(u, v);
	int d = depth[u] - depth[v];
	for ( int k = kLogMax-1; k>= 0; k--)
		if ( d & (1<<k) ) 
			u = anc[u][k];
	if ( u == v ) return u;
	for ( int k = kLogMax-1; k >= 0; k -- )
		if ( anc[u][k] != anc[v][k] )
			u = anc[u][k], v = anc[v][k];
	return anc[u][0];
}

void dfs(int x, int f) {
	anc[x][0] = f;
	if ( f ) depth[x] = depth[f]+1;
	for ( int k = 1; k < kLogMax; k ++ )
		if ( anc[x][k-1] )
			anc[x][k] = anc[anc[x][k-1]][k-1];
	pos[x][0] = ++seqL;
	foreach(it, son[x])
		dfs(*it, x);
	pos[x][1] = ++seqL;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m, root;
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &father[i]);
		if ( father[i] == 0 ) root = i;
		else son[father[i]].pb(i);
	}
	dfs(root, 0);
	scanf("%d", &m);
	for ( int i = 1; i <= m; i ++ ) {
		int t;
		scanf("%d", &t);
		if ( t == 1 ) {
			int c;
			scanf("%d", &c);
			stamp[c] = i;
		}
		else {
			ev[nev].type = 2;
			scanf("%d%d%d%d", &ev[nev].a, &ev[nev].b, &ev[nev].k, &ev[nev].y);
			ev[nev].id = nquery++;
			nev++;
		}
	}
	for ( int i = 1; i <= n; i ++ ) {
		ev[nev].type = 1;
		ev[nev].y = stamp[i];
		ev[nev].a = i;
		nev++;
	}
	sort(ev, ev + nev);
	for ( int i = 0; i < nev; i ++ ) {
		if ( ev[i].type == 1 ) {
			int a = ev[i].a;
			idt.add(pos[a][0], -1); idt.add(pos[a][1], 1);
			val[a] = 1;
		} else {
			int u = ev[i].a, v = ev[i].b, k = ev[i].k;
			int p = getLCA(u, v);
			int tot = askSum(u, p) + askSum(v, p) - askSum(p, p);
			tot -= val[u]; tot -= val[v];
			if ( k > tot ) {
				ans[ev[i].id] = -1;
				continue;
			}
			if ( depth[u] < depth[v] ) {
				swap(u, v);
				k = tot - k + 1;
			}
			if ( v == p ) {
				if ( v == father[u] ) ans[ev[i].id] = -1;
				else {
					u = father[u];
					ans[ev[i].id] = getKth(u, k);
				}
			} else {
				u = father[u], v = father[v];
				int t = askSum(u, p);
				if ( t <= k ) ans[ev[i].id] = getKth(u, k);
				else ans[ev[i].id] = getKth(v, tot-t-(k-t)+1);
			}
		}
	}
	for ( int i = 0; i < nquery; i ++ )
		printf("%d\n", ans[i]);
}
