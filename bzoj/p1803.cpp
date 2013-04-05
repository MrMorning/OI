#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
const int N_MAX = 100010;
namespace split_tree {
	const int DEPTH_MAX = 25;
	const int ELE_MAX = N_MAX;

	int val[DEPTH_MAX][ELE_MAX], toleft[DEPTH_MAX][ELE_MAX];
	int sorted[ELE_MAX], n;
	void build(int l, int r, int dep) {
		if ( l == r ) return;
		int mid = (l + r) / 2,
			lsame = mid - l + 1;
		for ( int k = l; k <= r; k ++ ) 
			if ( val[dep][k] < sorted[mid] ) lsame --;
		for ( int k = l, lpos = l, rpos = mid + 1; k <= r; k ++ ) {
			int cur = val[dep][k];
			toleft[dep][k] = k == l ? 0 : toleft[dep][k - 1];
			if ( cur < sorted[mid] ||
					( cur == sorted[mid] && lsame) ) {
				val[dep + 1][lpos ++] = cur;
				toleft[dep][k] ++;
				if ( cur == sorted[mid] ) lsame --;
			} else 
				val[dep + 1][rpos ++] = cur;
		}
		build(l, mid, dep + 1);
		build(mid + 1, r, dep + 1);
	}
	int query(int l, int r, int p, int q, int k, int dep) {
		if ( p == q ) return val[dep][p];
		int mid = (l + r) / 2;
		int tlp = p == l ? 0 : toleft[dep][p - 1];
		int lcnt = toleft[dep][q] - tlp;
		if ( k <= lcnt )
			return query(l, mid, l + tlp, l - 1 + toleft[dep][q], k, dep + 1);
		else
			return query(mid + 1, r, mid + p - l - tlp + 1, mid + q - l + 1 - toleft[dep][q], k - lcnt, dep + 1);
	}
	void build(int _n, int a[]) {
		n = _n;
		for ( int i = 1; i <= n; i ++ ) 
			val[0][i] = sorted[i] = a[i];
		sort(sorted + 1, sorted + n + 1);
		build(1, n, 0);
	}
	int query(int p, int q, int k) {
		return query(1, n, p, q, k, 0);
	}
}
struct Edge {
	int to;
	Edge *next;
} edge[N_MAX * 2], *begin[N_MAX];
void add_edge(int u, int v) {
	static int edge_cnt = 0;
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], begin[u] = e;
}
int n, m, a[N_MAX], st[N_MAX], en[N_MAX], lab[N_MAX], seq_len;
map<int, int> conv;
void dfs(int x) {
	st[x] = ++ seq_len;
	a[seq_len] = lab[x];
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( !st[y] )
			dfs(y);
	}
	en[x] = seq_len;
}
int main() {
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &lab[i]);
		conv[lab[i]] = i;
	}
	split_tree::build(n, a);
	for ( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1);
	split_tree::build(n, a);
	scanf("%d", &m);
	while ( m -- ) {
		int x, k;
		scanf("%d%d", &x, &k);
		printf("%d\n", conv[split_tree::query(st[x], en[x], k)]);
	}
}
