#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <cassert>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C.end()); I++)
using namespace std;
const int kNMax = 610;

struct Node {
	int l, r, sum;
} node[kNMax*4], nodeCp[kNMax*4];

void update(int i) {
	node[i].sum = node[i*2].sum + node[i*2+1].sum;
}

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	if ( l == r ) node[i].sum = 1;
	else {
		int mid = (l + r) / 2;
		build(i*2,l,mid);
		build(i*2+1,mid+1,r);
		update(i);
	}
}

int find(int k) {
	int cur = 1;
	while ( node[cur].l != node[cur].r ) {
		if ( node[2*cur].sum >= k ) 
			cur = cur * 2;
		else {
			k -= node[2*cur].sum;
			cur = cur * 2 + 1;
		}
	}
	int ret = node[cur].l;
	node[cur].sum = 0;
	for ( cur >>= 1; cur; cur >>= 1 )
		update(cur);
	return ret;
}

int top[kNMax][kNMax], left[kNMax][kNMax], n;
int stk[kNMax*kNMax], ans[kNMax][kNMax], dgr[kNMax*kNMax];
vector<int> adj[kNMax*kNMax];
int val[kNMax], perm[kNMax];
int stop;

void addEdge(int i1, int j1, int i2, int j2) {
	int u = (i1-1)*n+j1,
		v = (i2-1)*n+j2;
	adj[u].pb(v);
	dgr[v]++;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) 
			scanf("%d", &top[i][j]);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) 
			scanf("%d", &left[i][j]);

	build(1, 1, n);
	memcpy(nodeCp, node, sizeof(node));
	for ( int i = 1; i <= n; i ++ ) {
	memcpy(node, nodeCp, sizeof(node));
		for ( int j = n; j >= 1; j -- ) {
			int w = j-left[i][j];
			if ( w <= 0 ) {
				puts("0");
				exit(0);
			}
			val[j] = find(w);
		}
		for ( int j = 1; j <= n; j ++ ) perm[val[j]] = j;
		for ( int j = 1; j < n; j ++ )
			addEdge(i, perm[j], i, perm[j+1]);
	}

	for ( int i = 1; i <= n; i ++ ) {
	memcpy(node, nodeCp, sizeof(node));
		for ( int j = n; j >= 1; j -- ) {
			int w = j-top[j][i];
			if ( w <= 0 ) {
				puts("0");
				exit(0);
			}
			val[j] = find(w);
		}
		for ( int j = 1; j <= n; j ++ ) perm[val[j]] = j;
		for ( int j = 1; j < n; j ++ )
			addEdge(perm[j], i, perm[j+1], i);
	}
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ )
			if ( dgr[(i-1)*n+j] == 0 )
				stk[stop++] = (i-1)*n+j;
	int stamp = 0;
	while ( stop ) {
		int u = stk[--stop];
		ans[(u-1)/n+1][(u-1)%n+1] = ++stamp;
		foreach(it, adj[u]) {
			assert(dgr[*it] != 0);
			dgr[*it]--;
			if ( dgr[*it] == 0 )
				stk[stop++] = *it;
		}
	}
	if ( stamp != n*n ) 
		puts("0");
	else {
		for ( int i = 1; i <= n; i ++, puts("") )
			for ( int j = 1; j <= n; j ++ )
				printf("%d ", ans[i][j]);
		for ( int i = 1; i <= n; i ++ )
			for ( int j = 1; j <= n; j ++ ) {
				int cnt = 0;
				for ( int k = 1; k <= j; k ++ )
					cnt += ans[i][k] > ans[i][j];
				assert(cnt == left[i][j]);
				cnt = 0;
				for ( int k = 1; k <= i; k ++ )
					cnt += ans[k][j] > ans[i][j];
				assert(cnt == top[i][j]);
			}
	}
}
