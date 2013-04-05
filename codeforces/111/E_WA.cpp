#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 100010;

struct Info {
	int min, max, idx;
	bool e;
	Info(bool _e = true):
		e(_e){}
	void set(int d, int val) { idx = d, min = max = val; }
};

Info operator+ (const Info &a, const Info &b) {
	if ( !a.e ) return b;
	if ( !b.e ) return a;
	Info res;
	res.min = min(a.min, b.min);
	res.max = max(a.max, b.max);
	res.idx = a.idx;
	return res;
}

struct Node {
	int l, r;
	Info info;
	int tag_val, tag_idx;
} node[N_MAX * 3];

struct Bus {
	int s, f, t, idx;
	bool operator< (const Bus &o) const {
		return t < o.t;
	}
} bus[N_MAX];

struct Citizen {
	int l, r, b, idx;
	bool operator< (const Citizen &t) const {
		return b < t.b;
	}
} cit[N_MAX];

int axis[4 * N_MAX], axis_cnt;
int time[2 * N_MAX], time_cnt;

void mark(int i, int d, int val) {
	node[i].info.set(d, val);
	node[i].tag_idx = d;
	node[i].tag_val = val;
}

void push_down(int i) {
	if ( node[i].tag_val != -1 ) {
		mark(i * 2, node[i].tag_idx, node[i].tag_val);
		mark(i * 2 + 1, node[i].tag_idx, node[i].tag_val);
		node[i].tag_val = -1;
	}
}

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	node[i].tag_val = -1;
	node[i].info.set(-1, -1);
	if ( l == r )
		return;
	int mid = (l + r) / 2;
	build(i * 2, l, mid);
	build(i * 2 + 1, mid + 1, r);
}

void set(int i, int l, int r, int d, int val) {
	if ( node[i].l > r || node[i].r < l )
		return;
	if ( l <= node[i].l && node[i].r <= r ) {
		mark(i, d, val);
		return;
	}
	push_down(i);
	set(i * 2, l, r, d, val);
	set(i * 2 + 1, l, r, d, val);
	node[i].info = node[i * 2].info + node[i * 2 + 1].info;
}

Info ask(int i, int l, int r) {
	if ( node[i].l > r || node[i].r < l )
		return Info(false);
	if ( l <= node[i].l && node[i].r <= r ) {
		return node[i].info;
	}
	push_down(i);
	Info ret = ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
	node[i].info = node[i * 2].info + node[i * 2 + 1].info;
	return ret;
}
int n, m;
int out[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d%d%d", &bus[i].s, &bus[i].f, &bus[i].t);
		bus[i].idx = i;
		axis[axis_cnt ++] = bus[i].s;
		axis[axis_cnt ++] = bus[i].f;
		time[time_cnt ++] = bus[i].t;
	}
	for ( int i = 0; i < m; i ++ ) {
		scanf("%d%d%d", &cit[i].l, &cit[i].r, &cit[i].b);
		cit[i].idx = i;
		axis[axis_cnt ++] = cit[i].l;
		axis[axis_cnt ++] = cit[i].r;
		time[time_cnt ++] = cit[i].b;
	}
	sort(axis, axis + axis_cnt);
	sort(time, time + time_cnt);
	axis_cnt = unique(axis, axis + axis_cnt) - axis;
	time_cnt = unique(time, time + time_cnt) - time;
	for ( int i = 0; i < n; i ++ ) {
		bus[i].s = lower_bound(axis, axis + axis_cnt, bus[i].s) - axis;
		bus[i].f = lower_bound(axis, axis + axis_cnt, bus[i].f) - axis;
		bus[i].t = lower_bound(time, time + time_cnt, bus[i].t) - time;
	}
	for ( int i = 0; i < m; i ++ ) {
		cit[i].l = lower_bound(axis, axis + axis_cnt, cit[i].l) - axis;
		cit[i].r = lower_bound(axis, axis + axis_cnt, cit[i].r) - axis;
		cit[i].b = lower_bound(time, time + time_cnt, cit[i].b) - time;
	}
	sort(bus, bus + n);
	sort(cit, cit + m);
	build(1, 0, axis_cnt - 1);

	int p = n, q = m;
	for ( int cur_time = time_cnt - 1; cur_time >= 0; cur_time -- ) {
		while ( p && bus[p - 1].t >= cur_time ) {
			set(1, bus[p - 1].s, bus[p - 1].f, bus[p - 1].idx, bus[p - 1].t);
			p --;
		}
		while ( q && cit[q - 1].b >= cur_time ) {
			Info tmp = ask(1, cit[q - 1].l, cit[q - 1].r);
			if ( tmp.min == tmp.max )
				out[cit[q - 1].idx] = tmp.idx;
			else
				out[cit[q - 1].idx] = -1;
			q --;
		}
	}
	for ( int i = 0; i < m; i ++ )
		printf("%d ", out[i] + 1);
}
