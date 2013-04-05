#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int, int> pair_t;
typedef set<pair_t> set_t;
typedef set_t::iterator itr_t;

using namespace std;

const int N_MAX = 100010;

struct Bus {
	int s, f, t, idx;
	bool operator< (const Bus &o) const {
		return f < o.f;
	}
} bus[N_MAX];

struct Citizen {
	int l, r, b, idx;
	bool operator< (const Citizen &t) const {
		return r < t.r;
	}
} cit[N_MAX];

struct IndexTree {
	set_t ele[2 * N_MAX];
	void add(int i, pair_t p) {
		i ++;
		for (; i < 2 * N_MAX; i += i & -i )
			ele[i].insert(p);
	}
	int sum(int i, int lower) {
		i ++;
		pair_t res(-1, -1);
		for (; i; i -= i & -i ) {
			itr_t it = ele[i].lower_bound(make_pair(lower, 0));
			if ( it != ele[i].end() ) {
				if ( res.first == -1 || it->first < res.first )
					res = *it;
			}
		}
		return res.second;
	}
} idt;

int axis[2 * N_MAX], axis_cnt;
int time[2 * N_MAX], time_cnt;

int n, m;
int out[N_MAX];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d%d%d", &bus[i].s, &bus[i].f, &bus[i].t);
		bus[i].idx = i;
		time[time_cnt ++] = bus[i].f;
		axis[axis_cnt ++] = bus[i].s;
	}
	for ( int i = 0; i < m; i ++ ) {
		scanf("%d%d%d", &cit[i].l, &cit[i].r, &cit[i].b);
		cit[i].idx = i;
		time[time_cnt ++] = cit[i].r;
		axis[axis_cnt ++] = cit[i].l;
	}
	sort(axis, axis + axis_cnt);
	sort(time, time + time_cnt);
	axis_cnt = unique(axis, axis + axis_cnt) - axis;
	time_cnt = unique(time, time + time_cnt) - time;
	for ( int i = 0; i < n; i ++ )
		bus[i].s = lower_bound(axis, axis + axis_cnt, bus[i].s) - axis;
	for ( int i = 0; i < m; i ++ )
		cit[i].l = lower_bound(axis, axis + axis_cnt, cit[i].l) - axis;
	sort(bus, bus + n);
	sort(cit, cit + m);

	int p = n, q = m;
	for ( int upper = time_cnt - 1; upper >= 0; upper -- ) {
		while ( p && bus[p - 1].f >= time[upper] ) {
			idt.add(bus[p - 1].s, make_pair(bus[p - 1].t, bus[p - 1].idx));
			p --;
		}

		while ( q && cit[q - 1].r >= time[upper] ) {
			out[cit[q - 1].idx] = idt.sum(cit[q - 1].l, cit[q - 1].b);
			q --;
		}

	}
	for ( int i = 0; i < m; i ++ )
		if ( out[i] == -1 )
			printf("-1 ");
		else
			printf("%d ", out[i] + 1);
}
