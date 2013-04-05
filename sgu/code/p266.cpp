#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

typedef long double val_t;

const val_t kPi = acos(-1);
const val_t kEps = 1e-8;

inline int sgn(val_t x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

inline bool myEqual(val_t x, val_t y) {
	return sgn(x - y) == 0;
}

inline bool myLess(val_t x, val_t y) {
	return sgn(x - y) < 0;
}

inline val_t sqr(val_t x) { return x * x; }

struct Point3D {
	val_t x, y, z;
	Point3D(val_t xx, val_t yy, val_t zz):
		x(xx), y(yy), z(zz){}
	Point3D(){}
	val_t mod() {
		return sqrt(sqr(x)+sqr(y)+sqr(z));
	}
} p1, p2;

struct Point2D {
	val_t x, y;
	Point2D(val_t xx, val_t yy):
		x(xx), y(yy){}
	Point2D(){}
	val_t mod() {
		return sqrt(sqr(x)+sqr(y));
	}
} q1, q2;

Point3D operator- (const Point3D &p1, const Point3D &p2) {
	return Point3D(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z);
}

Point2D operator- (const Point2D &p1, const Point2D &p2) {
	return Point2D(p1.x-p2.x,p1.y-p2.y);
}
Point2D operator+ (const Point2D &p1, const Point2D &p2) {
	return Point2D(p1.x+p2.x,p1.y+p2.y);
}

Point2D operator* (const Point2D &p, val_t k) {
	return Point2D(p.x*k,p.y*k);
}

val_t dot(const Point3D &p1, const Point3D &p2) {
	return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

val_t dot(const Point2D &p1, const Point2D &p2) {
	return p1.x*p2.x+p1.y*p2.y;
}

val_t cross(const Point2D &p1, const Point2D &p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

Point2D rotate(const Point2D &p, val_t agl) {
	Point2D vx(cos(-agl),sin(-agl)),
			vy(cos(kPi/2-agl),sin(kPi/2-agl));
	return Point2D(dot(p, vx), dot(p, vy));
}

val_t r, curK, curB;

void calcCutPoint(Point2D p, Point2D &res1, Point2D &res2) {
	val_t agl = asin(r / p.mod()),
		   len = sqrt(sqr(p.mod())-sqr(r));
	Point2D v = Point2D(0,0) - p;
	v = v * (len / p.mod());
	res1 = p + rotate(v, -agl);
	res2 = p + rotate(v, agl);
}

val_t calcY(val_t x) {
	return curK * x + curB;
}

val_t myAcos(val_t agl) {
	if ( agl > 1 || agl < -1 ) return 0;
	return acos(agl);
}

val_t calc_f(val_t x) {
	if ( myEqual(x, r) ) return 0;
	return 2*r*myAcos(calcY(x)/sqrt(sqr(r)-sqr(x)));
}	

val_t simpson(val_t lb, val_t rb, val_t llv, val_t mmv, val_t rrv) {
	val_t mid = (lb+rb) / 2,
		   lmid = (lb+mid) / 2,
		   rmid = (mid+rb) / 2;
	val_t curVal = (rb-lb)/6*(llv+4*mmv+rrv),
		   lVal = calc_f(lmid), rVal = calc_f(rmid);
	if ( fabs(curVal - (mid-lb)/6*(llv+4*lVal+mmv)
			- (rb-mid)/6*(mmv+4*rVal+rrv)) < kEps )
		return curVal;
	return simpson(lb,mid,llv,lVal,mmv)+simpson(mid,rb,mmv,rVal,rrv);
}

val_t calcCapArea(val_t l) {
	val_t coef = (r-sqrt(sqr(r)-sqr(l/2)))/(2*r);
	return 4*kPi*sqr(r)*coef;
}

bool shadow(Point2D p1, Point2D p2, Point2D q) {
	return sgn(cross(p1,q)) <= 0 && sgn(cross(p2,q)) >= 0;
}

int main() {
	freopen("t.in", "r", stdin);
	cin >> r;
	cin >> p1.x >> p1.y >> p1.z;
	cin >> p2.x >> p2.y >> p2.z;

	val_t alpha = acos(dot(p1, p2) / p1.mod() / p2.mod()),
		   l1 = p1.mod(), l2 = p2.mod();
	q1 = Point2D(l1, 0), q2 = Point2D(cos(alpha)*l2,sin(alpha)*l2);
	if ( q2.y < 0 ) 
		q2.y = -q2.y;
	Point2D f11, f12, f21, f22;
	calcCutPoint(q1, f11, f12);
	calcCutPoint(q2, f21, f22);
	assert(myEqual(f11.x, f12.x));
	val_t ans = calcCapArea((f11-f12).mod()) + calcCapArea((f21-f22).mod()),
		   common = 0;
	if ( sgn(min(f21.x, f22.x)-f11.x) >= 0 )
		common = calcCapArea((f21-f22).mod());
	else if ( sgn(max(f21.x, f22.x)-f11.x) <= 0 ) {
		if ( !shadow(f21,f22,f11) || !shadow(f21,f22,f12) )
			common = 0;
		else common = calcCapArea((f11-f12).mod());
	} else {
		val_t lb = f11.x, rb;
		if ( myLess(f22.y, 0) ) {
			rb = f22.x;
			common += calcCapArea(2*sqrt(sqr(r)-sqr(f22.x)));
		} else 
			rb = r;
		curK = (f21.y-f22.y)/(f21.x-f22.x);
		curB = f21.y-curK*f21.x;
		common += simpson(lb, rb, calc_f(lb), calc_f((lb+rb)/2), calc_f(rb));
	}
	ans -= common;
	cout << setprecision(3) << setiosflags(ios::fixed) << ans;
}
