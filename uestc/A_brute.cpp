#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 100010;

int init_val[N_MAX];

struct Info {
	int all_best;
	int lb, rb;
	int lval, rval;
	int lbest, rbest;
	bool e;
	Info(bool _e = true):
		e(_e){}
};

Info operator+ (const Info &A, const Info &B) {
	if ( !A.e ) return B;
	if ( !B.e ) return A;
	Info res;
	res.lb = A.lb; res.rb = B.rb;
	res.lval = A.lval;
	res.rval = B.rval;

	res.lbest = A.lbest;
	res.rbest = B.rbest;

	res.all_best = max(A.all_best, B.all_best);
	if ( A.rval < B.lval ) {
		res.all_best = max(res.all_best, A.rbest + B.lbest);
		if ( A.lbest == A.rb - A.lb + 1 )
			res.lbest = A.lbest + B.lbest;
		if ( B.rbest == B.rb - B.lb + 1 )
			res.rbest = B.rbest + A.rbest;
	}
	return res;
}

struct Node {
	int l, r;
	int tag;
	Info info;
} node[N_MAX * 4];

void update(int i) {
	node[i].info = node[i * 2].info + node[i * 2 + 1].info;
}

void mark(int i, int tag) {
	node[i].tag += tag;
	node[i].info.lval += tag;
	node[i].info.rval += tag;
}

void push_down(int i) {
	if ( node[i].tag ) {
		mark(i * 2, node[i].tag);
		mark(i * 2 + 1, node[i].tag);
		node[i].tag = 0;
	}
}

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	if ( l == r ) {
		node[i].info.lb = node[i].info.rb = l;
		node[i].info.lval = node[i].info.rval = init_val[l];
		node[i].info.all_best = node[i].info.lbest = node[i].info.rbest = 1;
		node[i].tag = 0;
		return;
	}
	int mid = (l + r) / 2;
	build(i * 2, l, mid);
	build(i * 2 + 1, mid + 1, r);
	update(i);
}

void add_seg(int i, int l, int r, int val) {
	if ( node[i].l > r || node[i].r < l )
		return;
	if ( l <= node[i].l && node[i].r <= r ) {
		mark(i, val);
		return;
	}
	push_down(i);
	add_seg(i * 2, l, r, val);
	add_seg(i * 2 + 1, l, r, val);
	update(i);
}

Info ask(int i, int l, int r) {
	if ( node[i].l > r || node[i].r < l )
		return Info(false);
	if ( l <= node[i].l && node[i].r <= r )
		return node[i].info;
	push_down(i);
	Info res = ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
	update(i);
	return res;
}

void solve() {
	int N, Q;
	scanf("%d%d", &N, &Q);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d", &init_val[i]);
	while ( Q -- ) {
		static char str[5];
		scanf("%s", str);
		if ( str[0] == 'q' ) {
			int l, r;
			scanf("%d%d", &l, &r);
			int prev = -0x3f3f3f3f, cnt = 0;
			int res = 1;
			for ( int i = l; i <= r; i ++ ) {
				if ( init_val[i] <= prev ) {
					prev = init_val[i];
					cnt = 1;
					continue;
				}
				prev = init_val[i];
				cnt ++;
				res = max(res, cnt);
			}
			printf("%d\n", res);
		} else {
			int l, r, v;
			scanf("%d%d%d", &l, &r, &v);
			for ( int i = l; i <= r; i ++ )
				init_val[i] += v;
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for ( int tst = 1; tst <= TST; tst ++ ) {
		printf("Case #%d:\n", tst);
		solve();
	}
}
