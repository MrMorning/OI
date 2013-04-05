#include <cstdio>
#include <cmath>
#include <set>

using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

struct Point {
	ll x, y;
	Point(){}
	Point(ll _x, ll _y) 
		: x(_x), y(_y){}
	bool operator< (const Point &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
};

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

ll cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

typedef pair<double, Point> pair_t;
typedef set<pair_t> set_t;
typedef set_t::iterator itr_t;

set_t S;
ll xm, ym, res;
Point pm;

ll my_abs(ll x) { return x < 0 ? -x : x; }

itr_t lower(pair_t x) {
	itr_t res = S.lower_bound(x);
	if ( res == S.end() ) return S.begin();
	return res;
}

itr_t next(itr_t x) {
	x ++;
	if ( x == S.end() ) return S.begin();
	return x;
}

itr_t prev(itr_t x) {
	if ( x == S.begin() ) return -- S.end();
	return -- x;
}

void init() {
	ll x[3], y[3];
	Point p[3];
	xm = ym = 0;
	for ( int i = 0; i < 3; i ++ ) {
		scanf(LL_FMT LL_FMT, &x[i], &y[i]);
		x[i] *= 3, y[i] *= 3;
		xm += x[i], ym += y[i];
	}
	xm /= 3, ym /= 3;
	pm = Point(xm, ym);
	for ( int i = 0; i < 3; i ++ ) {
		x[i] -= xm, y[i] -= ym;
		p[i] = Point(x[i], y[i]);
	}
	S.clear();
	for ( int i = 0; i < 3; i ++ ) 
		S.insert(make_pair(atan2(y[i], x[i]),
					Point(x[i], y[i])));
	res = my_abs(cross(p[0] - p[1], p[0] - p[2]));
}

void work() {
	int q;
	scanf("%d", &q);
	pm.x = pm.y = 0;
	while ( q -- ) {
		ll xt, yt;
		scanf(LL_FMT LL_FMT, &xt, &yt);
		xt = 3 * xt - xm, yt = 3 * yt - ym;
		Point pt(xt, yt);
		pair_t it = make_pair(atan2(yt, xt), pt);
		itr_t lw = lower(it),
			  nw = lw,
			  nx = next(nw),
			  pv = prev(lw);
		if ( cross(pv->second - nw->second, it.second - nw->second) <= 0 )
			if ( cross(it.second - nw->second, pm - nw->second) <= 0 ) {
				printf(LL_FMT"\n", res / 9);
				continue;
			}
		res += -cross(pv->second - it.second, nw->second - it.second);
		while ( cross(it.second - nw->second, nx->second - nw->second) >= 0 ) {
			ll tmp = -cross(nw->second - it.second, nx->second - it.second);
			res += tmp;
			S.erase(nw);
			nw = nx;
			nx = next(nx);
		}
		nw = pv;
		nx = prev(nw);
		while ( cross(it.second - nw->second, nx->second - nw->second) <= 0 ) {
			ll tmp = cross(nw->second - it.second, nx->second - it.second);
			res += tmp;
			S.erase(nw);
			nw = nx;
			nx = prev(nx);
		}
		S.insert(it);
		printf(LL_FMT"\n", res / 9);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	init();
	work();
}
