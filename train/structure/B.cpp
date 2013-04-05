#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N_MAX = 100010;
const ll inf = 0x3f3f3f3f3f3f3f3fLL;

struct Node {
	int l, r;
	ll now_max, ever_max;
	ll tag, ever_tag;
} node[N_MAX * 3];

void update(int i) {
	node[i].now_max = max(node[i * 2].now_max, node[i * 2 + 1].now_max);
	node[i].ever_max = max(node[i * 2].ever_max, node[i * 2 + 1].ever_max);
}

void mark(int i, ll tag, ll ever_tag) {
	node[i].ever_max = max(node[i].ever_max, node[i].now_max + ever_tag);
	node[i].now_max += tag;
	node[i].ever_tag = max(node[i].ever_tag, node[i].tag + ever_tag);
	node[i].tag += tag;
}

void push_down(int i) {
	if ( node[i].tag != 0 || node[i].ever_tag != 0 ) {
		mark(i * 2, node[i].tag, node[i].ever_tag);
		mark(i * 2 + 1, node[i].tag, node[i].ever_tag);
		node[i].tag = node[i].ever_tag = 0;
	}
}

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	if ( l == r )
		return;
	int mid = (l + r) / 2;
	build(i * 2, l, mid);
	build(i * 2 + 1, mid + 1, r);
}

void add(int i, int l, int r, ll val) {
	if ( node[i].l > r || node[i].r < l )
		return;
	if ( l <= node[i].l && node[i].r <= r ) {
		mark(i, val, val);
		return;
	}
	push_down(i);
	add(i * 2, l, r, val);
	add(i * 2 + 1, l, r, val);
	update(i);
}

ll ask(int i, int l, int r) {
	if ( node[i].l > r || node[i].r < l )
		return -inf;
	if ( l <= node[i].l && node[i].r <= r )
		return node[i].ever_max;
	push_down(i);
	ll res = max(ask(i * 2, l, r), ask(i * 2 + 1, l, r));
	update(i);
	return res;
}

int n, m;
int a[N_MAX];
vector<pair<int, int> > q[N_MAX];
ll ans[N_MAX];

struct {
	int ele[2 * N_MAX];
	int &operator[] (int i) {
		return ele[i + N_MAX];
	}
} last;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	build(1, 1, n);
	scanf("%d", &m);
	for ( int i = 1; i <= m; i ++ ) {
		int l, r;
		scanf("%d%d", &l, &r);
		q[r].push_back(make_pair(i, l));
	}
	for ( int i = 1; i <= n; i ++ ) {
		add(1, last[a[i]] + 1, i, a[i]);
		for ( int j = 0, sz = q[i].size(); j < sz; j ++ ) 
			ans[q[i][j].first] = ask(1, q[i][j].second, i);
		last[a[i]] = i;
	}
	for ( int i = 1; i <= m; i ++ )
		printf("%lld\n", ans[i]);
}
