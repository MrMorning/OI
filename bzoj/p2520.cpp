#include <cstdio>
#include <vector>
#include <cstring>
#include <set>
using namespace std;
const int N_MAX = 1000010;
const int inf = 0x3f3f3f3f;

set<int> vis;
int dfn[N_MAX], low[N_MAX], time_stamp;
int stk[N_MAX], top, n_scc, bel[N_MAX];
int in_dgr[N_MAX];
bool in_stk[N_MAX];
vector<int> scc[N_MAX];
int n_mine;

struct Mine {
	int x, d, l, r;
} mine[N_MAX];

namespace idt {
	int tree[N_MAX];
	void add(int i, int val) {
		for (; i < N_MAX; i += i & -i )
			tree[i] += val;
	}
	void add(int l, int r, int val) {
		l ++, r ++;
		add(l, val);
		add(r + 1, -val);
	}
	int sum(int i) {
		i ++;
		int res = 0;
		for (; i; i -= i & -i ) 
			res += tree[i];
		return res;
	}
}

namespace sgt {
	struct Node {
		int l, r;
		int val;
	} node[N_MAX * 3];

	void update(int i) {
		node[i].val = min(node[i * 2].val, node[i * 2 + 1].val);
	}

	void build(int i, int l, int r) {
		node[i].l = l, node[i].r = r;
		node[i].val = inf;
		if ( l == r )
			return;
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
	}

	int ask(int i, int l, int r) {
		if ( l > node[i].r || r < node[i].l )
			return inf;
		if ( l <= node[i].l && node[i].r <= r )
			return node[i].val;
		return min(ask(i * 2, l, r), ask(i * 2 + 1, l, r));
	}

	void set(int pos, int new_val) {
		int cur = 1;
		for (;;) {
			if ( node[cur].l == node[cur].r )
				break;
			int mid = (node[cur].l + node[cur].r) / 2;
			if ( pos <= mid )
				cur = cur * 2;
			else
				cur = cur * 2 + 1;
		}
		node[cur].val = new_val;
		cur /= 2;
		while ( cur ) {
			update(cur);
			cur /= 2;
		}
	}

	void build(int n) { build(1, 0, n - 1); }
	int ask(int l, int r) {
		if ( l > r )
			return inf;
		return ask(1, l, r);
	}
}

void dfs(int x) {
	dfn[x] = low[x] = time_stamp ++;
	stk[top ++] = x;
	in_stk[x] = true;
	sgt::set(x, dfn[x]);
	vis.erase(vis.lower_bound(x));

	int pre = -1;
	while ( 1 ) {
		set<int>::iterator it;
	   	if ( pre == -1 ) 
			it = vis.lower_bound(mine[x].l);
		else
			it = vis.upper_bound(pre);

		if ( it == vis.end() || *it > mine[x].r ) {
			if ( pre == -1 )
				low[x] = min(low[x], sgt::ask(mine[x].l, mine[x].r));
			else
				low[x] = min(low[x], sgt::ask(pre + 1, mine[x].r));
			break;
		}
		if ( pre == -1 )
			low[x] = min(low[x], sgt::ask(mine[x].l, *it));
		else
			low[x] = min(low[x], sgt::ask(pre + 1, *it));
		dfs(*it);
		low[x] = min(low[x], low[*it]);
		pre = *it;
	}

	if ( low[x] == dfn[x] ) {
		while ( 1 ) {
			int u = stk[-- top];
			bel[u] = n_scc;
			in_stk[u] = false;
			scc[n_scc].push_back(u);
			sgt::set(u, inf);
			if ( u == x ) 
				break;
		}
		n_scc ++;
	}
}	

int main() {
	scanf("%d", &n_mine);
	for ( int i = 0; i < n_mine; i ++ ) {
		scanf("%d%d", &mine[i].x, &mine[i].d);
		vis.insert(i);
	}
	sgt::build(n_mine);
	for ( int i = 0; i < n_mine; i ++ ) {
		int lb = -1, rb = i;
		for ( int mid = (lb + rb) / 2; lb < rb - 1; 
				mid = (lb + rb) / 2 ) {
			if ( mine[i].x - mine[mid].x <= mine[i].d )
				rb = mid;
			else
				lb = mid;
		}
		mine[i].l = rb;
		lb = i, rb = n_mine;
		for ( int mid = (lb + rb) / 2; lb < rb - 1;
				mid = (lb + rb) / 2 ) {
			if ( mine[mid].x - mine[i].x <= mine[i].d )
				lb = mid;
			else
				rb = mid;
		}
		mine[i].r = lb;
	}
	memset(dfn, -1, sizeof(dfn));
	for ( int i = 0; i < n_mine; i ++ ) 
		if ( dfn[i] == -1 )
			dfs(i);

	for ( int i = 0; i < n_mine; i ++ ) 
		idt::add(mine[i].l, mine[i].r, 1);

	for ( int i = 0; i < n_scc; i ++ ) {
		int sz = scc[i].size();
		for ( int j = 0; j < sz; j ++ )
			idt::add(mine[scc[i][j]].l, mine[scc[i][j]].r, -1);
		for ( int j = 0; j < sz; j ++ )
			in_dgr[i] += idt::sum(scc[i][j]);
		for ( int j = 0; j < sz; j ++ )
			idt::add(mine[scc[i][j]].l, mine[scc[i][j]].r, 1);
	}

	int ans2 = n_scc;
	int ans1 = 0;
	for ( int i = 0; i < n_scc; i ++ )
		if ( in_dgr[i] == 0 )
			ans1 ++;
	printf("%d\n%d\n", ans1, ans2);
}
