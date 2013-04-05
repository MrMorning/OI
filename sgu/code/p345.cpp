#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long double val_t;

const val_t kEps = 1e-8;
const int kNMax = 50010;

inline int sgn(val_t x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

struct Point {
	val_t x, y;
	Point(){}
	Point(val_t xx, val_t yy):
		x(xx), y(yy){}
	bool operator== (const Point &pt) const {
		return sgn(x-pt.x)==0 && sgn(y-pt.y)==0;
	}
} p[kNMax*2], hull[kNMax];

struct Segment {
	Point p1, p2;
	Segment(){}
	Segment(Point pp, Point qq):
		p1(pp), p2(qq) {}
	bool contain(const Point &pt) const {
		if ( sgn(p1.x-p2.x) == 0 )
			return sgn(min(p1.y,p2.y)-pt.y) <= 0 && sgn(pt.y-max(p1.y,p2.y)) <= 0;
		else
			return sgn(min(p1.x,p2.x)-pt.x) <= 0 && sgn(pt.x-max(p1.x,p2.x)) <= 0;
	}
};

struct Line {
	Point p1, p2;
	val_t a, b, c;
	Line(){}
	Line(Point pp, Point qq) {
		p1 = pp; p2 = qq;
		a = p2.y-p1.y;
		b = p1.x-p2.x;
		c = -(a*p1.x+b*p1.y);
	}
	Point getIntersection(const Segment &S);
	bool isIntersected(const Segment &S);
	val_t calcDist(const Point &p) {
		return fabs(a*p.x+b*p.y+c)/(sqrt(a*a+b*b));
	}
	bool contain(const Point &p) {
		return sgn(a*p.x+b*p.y+c)==0;
	}
};

int n, m, st;
val_t polar[kNMax*2];
val_t presum[kNMax*2];

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x+p2.x, p1.y+p2.y);
}

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x, p1.y-p2.y);
}

Point operator* (const Point &p1, val_t k) {
	return Point(p1.x*k, p1.y*k);
}

val_t cross(const Point &p1, const Point &p2) {
	return p1.x*p2.y-p1.y*p2.x;
}

val_t dot(const Point &p1, const Point &p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

val_t calcDist(const Point &p1, const Point &p2) {
	return sqrt(dot(p1-p2,p1-p2));
}

Point Line::getIntersection(const Segment &S) {
	Point p1 = S.p1, p2 = S.p2;
	val_t u = fabs(a*p1.x+b*p1.y+c),
		   v = fabs(a*p2.x+b*p2.y+c);
	Point d = p2-p1;
	d = d * (u/(u+v));
	return p1+d;
}

bool Line::isIntersected(const Segment &S) {
	Line L2(S.p1, S.p2);
	if ( sgn(cross(Point(a,b), Point(L2.a, L2.b))) == 0 )
		return false;
	Point p = getIntersection(S);
	if ( S.contain(p) && contain(p) ) return true;
	return false;
}

bool cmpByPolar(const Point &p1, const Point &p2) {
	val_t agl1 = atan2(p1.y-p[0].y, p1.x-p[0].x),
		   agl2 = atan2(p2.y-p[0].y, p2.x-p[0].x);
	if ( sgn(agl1-agl2) < 0 
			|| (sgn(agl1-agl2)==0 && sgn(calcDist(p[0],p1)-calcDist(p[0],p2))<0 ) )
		return true;
	return false;
}

void convexHull() {
	int t = 0;
	for ( int i = 1; i < n; i ++ ) {
		if ( sgn(p[i].x-p[t].x) < 0
				|| (sgn(p[i].x-p[t].x) == 0
					&& sgn(p[i].y-p[t].y) < 0) )
			t = i;
	}
	swap(p[0], p[t]);
	sort(p+1, p+n, cmpByPolar);
	p[n] = p[0];
	int top = 0;
	hull[top++] = p[0];
	for ( int i = 1; i <= n; i ++ ) {
		if ( top < 2 ) 
			hull[top++] = p[i];
		else {
			Point A = hull[top-2], B = hull[top-1];
			while ( sgn(cross(A-B, p[i]-B)) >= 0 ) {
				top--;
				if ( top < 2 ) break;
				A = hull[top-2], B = hull[top-1];
			} 
		   	hull[top++] = p[i];
		}
	}
	//assert(hull[0] == hull[top-1]);
	n = top-1;
	memcpy(p, hull, sizeof(Point)*top);
}

int findFarthest(val_t agl) {
	if ( sgn(agl-polar[st+n-1]) >= 0 
			|| sgn(agl-polar[st]) <= 0 ) return st;
	int lb = st-1, rb = st+n-1;
	while ( lb < rb-1 ) {
		int mid = (lb + rb) / 2;
		if ( sgn(polar[mid]-agl) >= 0 ) 
			rb = mid;
		else
			lb = mid;
	}
	return rb;
}

int findNearest(int lb, int rb, Line L) {
	while ( rb-lb >= 3 ) {
		int lmid = lb+(rb-lb+1)/3,
			rmid = rb-(rb-lb+1)/3;
		if ( sgn(L.calcDist(p[lmid])-L.calcDist(p[rmid])) < 0 )
			rb = rmid;
		else
			lb = lmid;
	}
	for ( int i = lb; i <= rb; i ++ )
		if ( L.isIntersected(Segment(p[i], p[i+1])) )
			return i;
	assert(0);
}

val_t calcCrossSum(int l, int r) {
	if ( l > r ) return 0;
	return presum[r] - (l==0?0:presum[l-1]);
}

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		p[i].x = x, p[i].y = y;
	}
	convexHull();
	for ( int i = 0; i < n; i ++ ) 
		p[n+i] = p[i];
	for ( int i = 0; i < 2*n-1; i ++ ) {
		polar[i] = atan2(p[i+1].y-p[i].y, p[i+1].x-p[i].x);
		presum[i] = (i==0?0:presum[i-1]) + cross(p[i], p[i+1]);
	}
	polar[2*n-1] = polar[n-1];
	for ( int i = 0; i < 2*n-1; i ++ )
		if ( sgn(polar[i]) >= 0 && sgn(polar[i+1]) <= 0 ) {
			st = i+1;
			break;
		}
	scanf("%d", &m);
	while ( m -- ) {
		Point p1, p2;
		double tx1, ty1, tx2, ty2;
		scanf("%lf%lf%lf%lf", &tx1, &ty1, &tx2, &ty2);
		p1.x = tx1, p1.y = ty1, p2.x = tx2, p2.y = ty2;
		Line L(p1, p2);
		int i1 = findFarthest(atan2(p1.y-p2.y,p1.x-p2.x)),
			i2 = findFarthest(atan2(p2.y-p1.y,p2.x-p1.x));
		if ( !L.isIntersected(Segment(p[i1], p[i2])) ) {
			puts("0.00");
			continue;
		}
		if ( i1 >= n ) i1 -= n;
		if ( i2 >= n ) i2 -= n;
		if ( i2 < i1 ) 
			swap(i2, i1);
		int j1 = findNearest(i1, i2-1, L),
			j2 = findNearest(i2, i1+n-1, L);
		if ( j1 >= n ) j1 -= n;
		if ( j2 >= n ) j2 -= n;
		//assert(j1 < n && j2 < n);
		if ( j1 > j2 ) swap(j1, j2);
		Point q1 = L.getIntersection(Segment(p[j1], p[j1+1])),
			  q2 = L.getIntersection(Segment(p[j2], p[j2+1]));
		val_t area1 = 0, area2 = 0;
		area1 = cross(q2, q1) + cross(q1, p[j1+1]);
		area1 += calcCrossSum(j1+1, j2-1);
		area1 += cross(p[j2], q2);

		area2 = cross(q1, q2) + cross(q2, p[j2+1]);
		area2 += calcCrossSum(j2+1, n+j1-1);
		area2 += cross(p[j1], q1);

		area1 = fabs(area1), area2 = fabs(area2);
		printf("%.10lf\n", (double)min(area1, area2)/2);
	}
}
