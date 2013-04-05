#include <cstdio>
#include <cmath>
#include <set>
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
	double agl;
	Point(){}
	Point(ll _x, ll _y): x(_x), y(_y){}
	bool operator< (const Point &T) const {
		return agl < T.agl;
	}
	void read() {
		scanf(LL_FMT LL_FMT, &x, &y);
	}
	void prep();
} core;
typedef set<Point>::iterator itr_t;

void Point::prep() {
	x *= 3, y *= 3;
	x -= core.x, y -= core.y;
	agl = atan2(y, x);
}

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

ll cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

set<Point> sp;

itr_t next(itr_t cur) {
	cur ++;
	if ( cur == sp.end() ) return sp.begin();
	return cur;
}

itr_t prev(itr_t cur) {
	if ( cur == sp.begin() ) return --sp.end();
	return --cur;
}

bool insert(Point p, bool change) {
	itr_t it = sp.lower_bound(p), succ, pred;
	if ( it == sp.end() ) succ = sp.begin(), pred = --sp.end();
	else succ = it, pred = prev(it);
	if ( cross(p - *pred, *succ - *pred) <= 0 ) return true;
	if ( !change ) return false;
	while ( 1 ) {
		itr_t ppred = prev(pred);
		if ( cross(*pred - *ppred, p - *ppred) >= 0 ) break;
		sp.erase(pred);
		pred = ppred;
	}
	while ( 1 ) {
		itr_t ssucc = next(succ);
		if ( cross(*succ - *ssucc, p - *ssucc) <= 0 ) break;
		sp.erase(succ);
		succ = ssucc;
	}
	sp.insert(p);
	return true;
}

int main() {
	freopen("t.in", "r", stdin);
	int nq;
	scanf("%d", &nq);
	nq -= 3;
	Point p1, p2, p3;
	scanf("%*d");p1.read(); scanf("%*d"); p2.read(); scanf("%*d"); p3.read();
	core = Point(p1.x+p2.x+p3.x, p1.y+p2.y+p3.y);
	p1.prep(); p2.prep(); p3.prep();
	sp.insert(p1); sp.insert(p2); sp.insert(p3);

	while ( nq -- ) {
		int t;
		Point p;
		scanf("%d", &t);
		p.read();
		p.prep();
		if ( t == 1 ) insert(p, true);
		else printf("%s\n", insert(p, false) ? "YES" : "NO");
	}
}
