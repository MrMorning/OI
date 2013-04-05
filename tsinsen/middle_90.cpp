#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 20010, BLK_SIZE = 120;
const int BLK_MAX = N_MAX / BLK_SIZE + 10;

namespace sgt {
	struct Info {
		int sum, lm, rm;
		bool e;
		Info(bool _e = true):
			e(_e){}
	};
	
	Info operator+ (const Info &A, const Info &B) {
		if ( !A.e ) return B;
		if ( !B.e ) return A;
		Info res;
		res.sum = A.sum + B.sum;
		res.lm = max(A.lm, A.sum + B.lm);
		res.rm = max(B.rm, B.sum + A.rm);
		return res;
	}

	struct Node {
		int l, r;
		Info info;
	} node[N_MAX * 4];

	void update(int i) {
		node[i].info = node[i * 2].info + node[i * 2 + 1].info;
	}

	void build(int i, int l, int r) {
		node[i].l = l, node[i].r = r;
		if ( l == r ) {
			node[i].info.lm = node[i].info.rm = node[i].info.sum = 1;
			return;
		}
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
		update(i);
	}

	Info ask(int i, int l, int r) {
		if ( node[i].l > r || node[i].r < l )
			return Info(false);
		if ( l <= node[i].l && node[i].r <= r )
			return node[i].info;
		return ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
	}

	void change(int pos) {
		int cur = 1;
		while ( 1 ) {
			if ( node[cur].l == node[cur].r ) {
				node[cur].info.sum = -1;
				node[cur].info.lm = node[cur].info.rm = 0;
				break;
			}
			int mid = (node[cur].l + node[cur].r) / 2;
			if ( pos <= mid )
				cur = cur * 2;
			else 
				cur = cur * 2 + 1;
		}
		cur >>= 1;
		while ( cur ) {
			update(cur);
			cur >>= 1;
		}
	}
}

struct Block {
	int l, r, sz;
	int sorted[BLK_SIZE], f[N_MAX], g[N_MAX], memo[N_MAX];
	bool done[N_MAX];
	int count_less(int x) {
		if ( done[x] )
			return memo[x];
		done[x] = true;
		memo[x] = lower_bound(sorted, sorted + sz, x) - sorted;
		return memo[x];
	}
} blk[BLK_MAX];
int n_blk;

int ele[N_MAX], n_ele, n_evt;
pair<int, int> evt[N_MAX];
int axis[N_MAX], axis_cnt;
int modified[N_MAX];

int ceil_div(int a, int b) {
	if ( a % b == 0 )
		return a / b;
	else
		return a / b + 1;
}

int find_blk(int pos) {
	return pos / BLK_SIZE;
}

void init_block() {
	n_blk = ceil_div(n_ele, BLK_SIZE);
	for ( int i = 0; i < n_blk; i ++ ) {
		blk[i].l = i * BLK_SIZE;
		blk[i].r = min(n_ele - 1, (i + 1) * BLK_SIZE - 1);
		blk[i].sz = blk[i].r - blk[i].l + 1;
		for ( int j = blk[i].l; j <= blk[i].r; j ++ )
			blk[i].sorted[j - blk[i].l] = ele[j];
		sort(blk[i].sorted, blk[i].sorted + blk[i].sz);
	}
	sgt::build(1, 0, n_ele - 1);
	for ( int i = 0; i < n_ele; i ++ )
		evt[n_evt ++] = make_pair(ele[i], i);
	sort(evt, evt + n_evt);
	for ( int i = 0; i < n_blk; i ++ )
		modified[i] = true;
	for ( int i = 0, cur_val = 0; i < n_evt; i ++ ) {

		for ( int j = 0; j < n_blk; j ++ ) {
			if ( modified[j] ) {
				sgt::Info I = sgt::ask(1, blk[j].l, blk[j].r);
				blk[j].f[cur_val] = I.lm;
				blk[j].g[cur_val] = I.rm;
				modified[j] = false;
			} else {
				blk[j].f[cur_val] = blk[j].f[cur_val - 1];
				blk[j].g[cur_val] = blk[j].g[cur_val - 1];
			}
		}

		int st = i;
		while ( i + 1 < n_evt && evt[i + 1].first == evt[i].first )
			i ++;
		for ( int j = st; j <= i; j ++ ) {
			sgt::change(evt[j].second);
			modified[find_blk(evt[j].second)] = true;
		}
		cur_val ++;
	}
}

int calc_sum(int l, int r, int lim) {
	if ( l > r )
		return 0;
	int tl = find_blk(l), tr = find_blk(r);
	int res = 0;
	if ( tl == tr ) {
		for ( int i = l; i <= r; i ++ )
			res += ele[i] >= lim ? 1 : -1;
	} else {
		for ( int i = l; i <= blk[tl].r; i ++ )
			res += ele[i] >= lim ? 1 : -1;
		for ( int i = blk[tr].l; i <= r; i ++ )
			res += ele[i] >= lim ? 1 : -1;
		for ( int i = tl + 1; i <= tr - 1; i ++ ) {
			int tmp = blk[i].count_less(lim);
			res -= tmp;
			res += blk[i].sz - tmp;
		}
	}
	return res;
}

int calc_pre_max(int l, int r, int lim) {
	if ( l > r )
		return 0;
	int tl = find_blk(l), tr = find_blk(r);
	int res = 0;
	if ( tl == tr ) {
		int cnt = 0;
		for ( int i = l; i <= r; i ++ ) {
			cnt += ele[i] >= lim ? 1 : -1;
			res = max(res, cnt);
		}
	} else {
		int cnt = 0;
		for ( int i = l; i <= blk[tl].r; i ++ ) {
			cnt += ele[i] >= lim ? 1 : -1;
			res = max(res, cnt);
		}
		for ( int i = tl + 1; i <= tr - 1; i ++ ) {
			res = max(res, cnt + blk[i].f[lim]);
			int tmp = blk[i].count_less(lim);
			cnt -= tmp;
			cnt += blk[i].sz - tmp;
		}
		for ( int i = blk[tr].l; i <= r; i ++ ) {
			cnt += ele[i] >= lim ? 1 : -1;
			res = max(res, cnt);
		}
	}
	return res;
}

int calc_suf_max(int l, int r, int lim) {
	if ( l > r )
		return 0;
	int tl = find_blk(l), tr = find_blk(r);
	int res = 0;
	if ( tl == tr ) {
		int cnt = 0;
		for ( int i = r; i >= l; i -- ) {
			cnt += ele[i] >= lim ? 1 : -1;
			res = max(res, cnt);
		}
	} else {
		int cnt = 0;
		for ( int i = r; i >= blk[tr].l; i -- ) {
			cnt += ele[i] >= lim ? 1 : -1;
			res = max(res, cnt);
		}
		for ( int i = tr - 1; i >= tl + 1; i -- ) {
			res = max(res, cnt + blk[i].g[lim]);
			int tmp = blk[i].count_less(lim);
			cnt -= tmp;
			cnt += blk[i].sz - tmp;
		}
		for ( int i = blk[tl].r; i >= l; i -- ) {
			cnt += ele[i] >= lim ? 1 : -1;
			res = max(res, cnt);
		}
	}
	return res;
}

bool check(int a, int b, int c, int d, int lim) {
	b --, c ++;
	int mid_sum = calc_sum(b + 1, c - 1, lim);
	int suf = calc_suf_max(a, b, lim), pre = calc_pre_max(c, d, lim);
	return mid_sum + suf + pre >= 0;
}

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d", &n_ele);
	for ( int i = 0; i < n_ele; i ++ ) {
		scanf("%d", &ele[i]);
		axis[axis_cnt ++] = ele[i];
	}
	sort(axis, axis + axis_cnt);
	axis_cnt = unique(axis, axis + axis_cnt) - axis;
	for ( int i = 0; i < n_ele; i ++ )
		ele[i] = lower_bound(axis, axis + axis_cnt, ele[i]) - axis;
	init_block();

	int n_que;
	scanf("%d", &n_que);
	int haha = 0;
	while ( n_que -- ) {
		int a, b, c, d;
		int q[4];
		scanf("%d%d%d%d", &a, &b, &c, &d);
		q[0] = (a + haha) % n_ele;
		q[1] = (b + haha) % n_ele;
		q[2] = (c + haha) % n_ele;
		q[3] = (d + haha) % n_ele;
		sort(q, q + 4);
		a = q[0], b = q[1], c = q[2], d = q[3];

		int lb = 0, rb = axis_cnt;
		for ( int mid = (lb + rb) / 2;
				lb < rb - 1; mid = (lb + rb) / 2 ) {
			if ( check(a, b, c, d, mid) )
				lb = mid;
			else
				rb = mid;
		}
		printf("%d\n", axis[lb]);
		haha = axis[lb];
	}
}
