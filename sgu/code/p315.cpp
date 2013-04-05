#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#define NDEBUG
using namespace std;

const double kEps = 1e-8;
const double kInf = 1e100;
const int kVMax = 2510;

inline double sqr(double x) { return x * x; }

inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

struct Point {
	double x, y;
	Point(double xx, double yy):
		x(xx), y(yy){}
	Point(){}
	bool operator< (const Point &p) const {
		return sgn(x-p.x)<0 || (sgn(x-p.x)==0&&sgn(y-p.y)<0);
	}
	bool operator== (const Point &p) const {
		return sgn(x-p.x)==0 && sgn(y-p.y)==0;
	}
};

struct Segment {
	Point p1, p2;
	bool mark;
	vector<Point> vp;
	Segment(){ 
		mark = false; vp.clear();
   	}
};

vector<Point> pool;
vector<int> adj[kVMax];
double f[kVMax];
Point curCmpP;

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x,p1.y-p2.y);
}

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x+p2.x,p1.y+p2.y);
}

Point operator* (const Point &p1, double k) {
	return Point(p1.x*k, p1.y*k);
}

double cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

double calcDist(const Point &p1, const Point &p2) {
	return sqrt(sqr(p1.x-p2.x) + sqr(p1.y-p2.y));
}

double calcAgl(const Point &p1) {
	//assert(!(p1 == Point(0,0)));
	return atan2(p1.y,p1.x);
}

bool cmpP(const Point &p1, const Point &p2) {
	return sgn(calcDist(p1,curCmpP)-calcDist(p2,curCmpP)) < 0;
}

bool cmpAgl(int i, int j) {
	return calcAgl(pool[i]) < calcAgl(pool[j]);
}

bool isCross(double l1, double r1, double l2, double r2) {
	return sgn(max(l1,l2)-min(r1,r2)) <= 0;
}

bool strictIntersect(const Point &p1, const Point &p2,
		const Point &q1, const Point &q2) {
	if ( sgn(cross(p1-p2,q1-q2)) == 0 ) {
		if ( sgn(cross(p2-p1,q1-p1)) != 0 ) return false;
		if ( sgn(p1.x-p2.x) == 0 ) {
			return isCross(min(p1.y,p2.y),max(p1.y,p2.y),
					min(q1.y,q2.y),max(q1.y,q2.y));
		} else {
			return isCross(min(p1.x,p2.x),max(p1.x,p2.x),
					min(q1.x,q2.x),max(q1.x,q2.x));
		}
	} else
		return sgn(cross(q1-p1,p2-p1))*sgn(cross(p2-p1,q2-p1)) >= 0
			&& sgn(cross(p1-q1,q2-q1))*sgn(cross(q2-q1,p2-q1)) >= 0;
}

Point getItc(const Point &p1, const Point &p2,
		const Point &q1, const Point &q2) {
	if ( sgn(cross(p1-p2, q1-q2)) == 0 ) {
		if ( sgn(p1.x-p2.x) == 0 ) {
			if ( sgn(min(p1.y,p2.y)-q1.y)<=0 && sgn(q1.y-max(p1.y, p2.y))<=0 )
				return q1;
			else {
				assert(sgn(min(p1.y,p2.y)-q2.y)<=0 && sgn(q2.y-max(p1.y, p2.y))<=0);
				return q2;
			}
		} else {
			if ( sgn(min(p1.x,p2.x)-q1.x)<=0 && sgn(q1.x-max(p1.x, p2.x))<=0 )
				return q1;
			else {
				assert(sgn(min(p1.x,p2.x)-q2.x)<=0 && sgn(q2.x-max(p1.x, p2.x))<=0);
				return q2;
			}
		}
	}

	double 	a = q1.y - q2.y,
			b = q2.x - q1.x,
			c = -(a*q1.x+b*q1.y);
	double k1 = fabs(a*p1.x+b*p1.y+c),
		   k2 = fabs(a*p2.x+b*p2.y+c);
	Point v = (p2-p1) * (k1/(k1+k2));
	return p1 + v;
}

bool canCover(const Segment &s1, const Segment &s2) {
	Point p1 = s1.p1, p2 = s1.p2,
		  q1 = s2.p1, q2 = s2.p2;
	if ( !strictIntersect(p1,p2,q1,q2) ) return false;
	if ( sgn(cross(p1-p2,q1-q2)) != 0 ) return false;
	double l1, r1, l2, r2;
	if ( sgn(p1.x-p2.x) == 0 ) {
		l1 = min(p1.y, p2.y), r1 = max(p1.y, p2.y);
		l2 = min(q1.y, q2.y), r2 = max(q1.y, q2.y);
	} else {
		l1 = min(p1.x, p2.x), r1 = max(p1.x, p2.x);
		l2 = min(q1.x, q2.x), r2 = max(q1.x, q2.x);
	}
	return sgn(l1-l2) >= 0 && sgn(r1-r2) <= 0;
}

void addEdge(int i, int j) {
	if ( sgn(cross(pool[i], pool[j])) > 0 ) {
		adj[i].pb(j);
#ifndef NDEBUG
		fprintf(stderr, "%d->%d\n", i, j);
#endif
	}
}

int getId(const Point &p) {
	return lower_bound(pool.begin(), pool.end(), p) - pool.begin();
}

int main() {
	freopen("t.in", "r", stdin);
	int nSeg;
	scanf("%d", &nSeg);
	vector<Segment> seg(nSeg);
	for ( int i = 0; i < nSeg; i ++ ) {
		scanf("%lf%lf%lf%lf", &seg[i].p1.x, &seg[i].p1.y,
				&seg[i].p2.x, &seg[i].p2.y);
	}
	for ( int i = 0; i < (int)seg.size(); i ++ ) {
		if ( sgn(calcDist(seg[i].p1, seg[i].p2)) == 0 ) 
			seg[i].mark = true;
		if ( sgn(cross(Point(0,0)-seg[i].p1,seg[i].p2-seg[i].p1)) == 0 )
			seg[i].mark = true;
	}
	for ( int i = 0; i < (int)seg.size(); i ++ ) {
		for ( int j = 0; j < (int)seg.size(); j ++ ) 
			if ( i != j && !seg[j].mark ) {
				if ( canCover(seg[j], seg[i]) )
					seg[i].mark = true;
			}
	}
	for ( int i = 0; i < (int)seg.size(); i ++ ) 
		if ( seg[i].mark ) {
			seg.erase(seg.begin()+i);
			i--;
		}
	nSeg = seg.size();
	for ( int i = 0; i < nSeg; i ++ ) {
		seg[i].vp.pb(seg[i].p1);
		seg[i].vp.pb(seg[i].p2);
		pool.pb(seg[i].p1);
		pool.pb(seg[i].p2);
	}
	for ( int i = 0; i < nSeg; i ++ )
		for ( int j = 0; j < nSeg; j ++ )
			if ( i != j && strictIntersect(seg[i].p1, seg[i].p2, seg[j].p1, seg[j].p2) ) {
				Point p = getItc(seg[i].p1, seg[i].p2, seg[j].p1, seg[j].p2);
				seg[i].vp.pb(p);
				pool.pb(p);
			}
	sort(pool.begin(), pool.end());
	pool.resize(unique(pool.begin(), pool.end())-pool.begin());

#ifndef NDEBUG
	foreach(it, pool) {
		printf("%d: %.3lf %.3lf\n", it-pool.begin(), it->x, it->y);
	}
#endif

	for ( int i = 0; i < nSeg; i ++ ) {
		curCmpP = seg[i].p1;
#ifndef NDEBUG
		foreach(it, seg[i].vp) {
			fprintf(stderr, "%d: %.3lf %.3lf\n", it-seg[i].vp.begin(), it->x, it->y);
		}
#endif
		sort(seg[i].vp.begin(), seg[i].vp.end(), cmpP);
		seg[i].vp.resize(unique(seg[i].vp.begin(), seg[i].vp.end())-seg[i].vp.begin());
		int sz = seg[i].vp.size();
		for ( int j = 0; j < sz-1; j ++ ) {
			addEdge(getId(seg[i].vp[j]), getId(seg[i].vp[j+1]));
			addEdge(getId(seg[i].vp[j+1]), getId(seg[i].vp[j]));
		}
	}

	int n = pool.size();
	vector<int> arr;
	for ( int i = 0; i < n; i ++ )
		arr.pb(i);
	sort(arr.begin(), arr.end(), cmpAgl);

	double ans = 0;
	for ( int src = 0; src < n; src ++ ) {
		for ( int i = 0; i < n; i ++ ) f[i] = -kInf;
		f[arr[src]] = 0;
		for ( int i = src; i < n; i ++ )
			if ( sgn(f[arr[i]]) >= 0 ) {
				foreach(it, adj[arr[i]]) {
					double tmp = f[arr[i]] + calcDist(pool[arr[i]], pool[*it]);
					if ( sgn(calcAgl(pool[*it])) < 0 && sgn(calcAgl(pool[arr[i]])) >= 0 ) {
						if ( (*it) == arr[src] )
							ans = max(ans, tmp);
					} else
						f[*it] = max(f[*it], tmp);
				}
			}
	}

	printf("%.10lf\n", ans);
}
