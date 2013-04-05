#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
typedef long long ll;
using namespace std;

const int N_MAX = 100010;

#define UNLUCK 0
#define LUCK 1

struct Interval {
	int l, r;
	Interval(int _l, int _r):
		l(_l), r(_r){}
	bool operator< (const Interval &it)const {
		return r < it.r || (r == it.r && l > it.l);
	}
};

struct Segment {
	int type, l, r;
	Segment(){}
	Segment(int _type, int _l, int _r):
		type(_type), l(_l), r(_r){}
} seg[N_MAX];
int seg_cnt = 0;

set<Interval> itv_set;
map<int, int> luck_map;
vector<int> luck_vec[N_MAX];
bool done[1010];

ll acc;
void add_itv_to_set(const Interval &t) {
	int n = t.r - t.l + 1;
	acc += (ll)n * (n + 1) / 2;
	itv_set.insert(t);
}
ll calc_s(ll n, ll m, ll s0) {
	ll res = 0;
	res = m * n * n;
   	res -= m * n;
   	res += m * (m + 1) * (2 * m + 1) / 6;
   	res += (2 * n - 1) * m * (1 + m) / 2;
	res /= 2;
	res += m * s0;
	res -= m * n * (n + 1) / 2;

	return res;
}
bool is_luck(int x) {
	bool res = true;
	while ( x ) {
		res &= x % 10 == 4 || x % 10 == 7;
		x /= 10;
	}
	return res;
}

int n;
int a[N_MAX];

int main() {
	freopen("t.in", "r", stdin);

	int luck_idx = 0;
	ll res = 0;

	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &a[i]);
		if ( is_luck(a[i]) ) {
			if ( luck_map.count(a[i]) == 0 )
				luck_map[a[i]] = ++ luck_idx;
			luck_vec[luck_map[a[i]]].push_back(i);
		}
	}
	for ( int i = 1; i <= n; i ++ )  {
		if ( !is_luck(a[i]) ) {
			int st = i;
			while ( i + 1 <= n && !is_luck(a[i + 1]) )
				i ++;
			seg[++seg_cnt] = Segment(UNLUCK, st, i);
		} else
			seg[++seg_cnt] = Segment(LUCK, i, i);
	}
	for ( int i = 1; i <= seg_cnt; i ++ ) {
		const Segment &left = seg[i];
		memset(done, 0, sizeof(done));
		if ( left.type == LUCK ) {
			if ( i == 1 ) continue;
			itv_set.clear();
			acc = 0;

			add_itv_to_set(Interval(1, left.l - 1));

			for ( int k = i; k <= seg_cnt; k ++ ) {
				const Segment &right = seg[k];
				if ( right.type == LUCK ) {
					int id = luck_map[a[right.l]];
					if ( !done[id] ) {
						done[id] = true;
						for ( int sz = (int)luck_vec[id].size(), j = 0; j < sz; j ++ ) {
							int t = luck_vec[id][j];
							if ( t >= left.l ) break;
							set<Interval>::iterator it = itv_set.lower_bound(Interval(t, t));
							int n = it->r - it->l + 1, l = it->l, r = it->r;
							itv_set.erase(it);

							acc -= (ll)n * (n + 1) / 2;
							Interval next_l(l, t - 1), next_r(t + 1, r);
							if ( l <= t - 1 )
								add_itv_to_set(next_l);
							if ( t + 1 <= r )
								add_itv_to_set(next_r);
						}
					}
					res += acc;
				} else { //right segment is unlucky
					res += acc * (right.r - right.l + 1);
				}
			}
		} else { //left segment is unlucky --- complicated
			itv_set.clear();
			acc = 0;
			if ( left.l > 1 )
				add_itv_to_set(Interval(1, left.l - 1));
			for ( int k = i; k <= seg_cnt; k ++ ) {
				if ( k == i ) { //brute force
					ll h = left.l - 1, 
					   m = left.r - left.l + 1;
					for ( int t = 1; t <= m; t ++ ) {
						ll tmp1 = (h + t - 1) * (h + t) / 2,
						   tmp2 = m - t + 1;
						res += tmp1 * tmp2;
					}
				} else {
					const Segment &right = seg[k];
					if ( right.type == LUCK ) {
						int id = luck_map[a[right.l]];
						if ( !done[id] ) {
							done[id] = true;
							for ( int sz = (int)luck_vec[id].size(), j = 0; j < sz; j ++ ) {
								int t = luck_vec[id][j];
								if ( t >= left.l ) break;
								set<Interval>::iterator it = itv_set.lower_bound(Interval(t, t));
								int n = it->r - it->l + 1, l = it->l, r = it->r;
								itv_set.erase(it);

								acc -= (ll)n * (n + 1) / 2;
								Interval next_l(l, t - 1), next_r(t + 1, r);
								if ( l <= t - 1 )
									add_itv_to_set(next_l);
								if ( t + 1 <= r )
									add_itv_to_set(next_r);
							}
						}
						//stat
						ll h, m = left.r - left.l + 1;
						if ( itv_set.begin() == itv_set.end() )
							h = 0;
						else {
							set<Interval>::iterator it = -- itv_set.end();
							h = it->r - it->l + 1;
						}
						res += calc_s(h, m, acc);
					} else {
						//stat directly
						ll h, m = left.r - left.l + 1;
						if ( itv_set.begin() == itv_set.end() )
							h = 0;
						else {
							set<Interval>::iterator it = -- itv_set.end();
							h = it->r - it->l + 1;
						}
						res += calc_s(h, m, acc) * (right.r - right.l + 1);
					}
				}
			}
		}
	}
	cout << res << '\n';
}
