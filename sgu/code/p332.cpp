#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

typedef double val_t;
const int kPointMax = 10010;
const val_t EPS = 1e-10;
const val_t PI = acos(-1);

inline int sgn(val_t x) {
	if ( fabs(x) < EPS ) return 0;
	if ( x > 0 ) return 1;
	return -1;
}

struct Point {
	val_t x, y;
	Point(){}
	Point(val_t xx, val_t yy):
		x(xx), y(yy){}
	bool operator< (const Point &t) const {
		return sgn(y - t.y) < 0 || (sgn(y - t.y) == 0 && sgn(x - t.x) < 0);
	}
	bool operator> (const Point &t) const {
		return sgn(y - t.y) > 0 || (sgn(y - t.y) == 0 && sgn(x - t.x) > 0);
	}
};

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}
Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}
Point operator* (const Point &p, val_t k) {
	return Point(p.x * k, p.y * k);
}
val_t cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}
val_t dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}
void rotate(Point &p, val_t agl) {
	Point vy(cos(PI/2-agl), sin(PI/2-agl)),
		  vx(cos(-agl), sin(-agl));
	p = Point(dot(p, vx), dot(p, vy));
}

struct Constrain {
	val_t a, b, c;
	Constrain(){}
	Constrain(val_t aa, val_t bb, val_t cc):
		a(aa), b(bb), c(cc){}
	void reverse() {
		a *= -1, b *= -1, c *= -1;
	}
	val_t func(const Point &p) const{
		return a * p.x + b * p.y + c;
	}
	val_t calcY(val_t x) const{
		return (-c - a * x) / b;
	}
	val_t calcX(val_t y) const{
		return (-c - b * y) / a;
	}
	Point getOnePoint() {
		if ( sgn(b) != 0 )
			return Point(0, calcY(0));
		else
			return Point(-c / a, 0);
	}
	Point getVector() const{
		return Point(b, -a);
	}
} constrain[kPointMax];

bool isParellel(const Constrain &l1, const Constrain &l2) {
	return sgn(cross(l1.getVector(), l2.getVector())) == 0;
}

Point getIntersection(const Constrain &l1, const Constrain &l2) {
	val_t y = (l1.a * l2.c - l1.c * l2.a) / (l2.a * l1.b - l1.a * l2.b);
	if ( sgn(l1.a) != 0 ) 
		return Point((-l1.c - l1.b * y) / l1.a, y);
	return Point((-l2.c - l2.b * y) / l2.a, y);
}

Point convex[kPointMax];
int nconvex;

bool check(val_t lim) {
	static Point tmp[kPointMax];
	static int flag[kPointMax];

	for ( int i = 0; i < nconvex; i ++ ) {
		Point p1 = convex[i], p2 = convex[i + 1];
		Point v = Point(p1.y - p2.y, p2.x - p1.x);
		if ( sgn(cross(v, p2 - p1)) < 0 )
			v = v * -1;
		v = v * (lim / sqrt(dot(v, v)));
		p1 = p1 + v;
		p2 = p2 + v;
		val_t a = p1.y - p2.y,
			  b = p2.x - p1.x,
			  c = -(a * p1.x + b * p1.y);
		constrain[i] = Constrain(a, b, c);
		if ( sgn(constrain[i].func(p1 + v)) < 0 )
			constrain[i].reverse();
	}
	random_shuffle(constrain, constrain + nconvex);

	//half planes intersection
	Point cur = constrain[0].getOnePoint();
	for ( int i = 1; i < nconvex; i ++ ) {
		if ( sgn(constrain[i].func(cur)) >= 0 )
			continue;
		Point v = constrain[i].getVector();
		if ( sgn(v.y) < 0 || (sgn(v.y) == 0 && sgn(v.x) < 0) )
			v = v * -1;
		int ntmp = 0;
		for ( int j = 0; j < i; j ++ )
			if ( !isParellel(constrain[i], constrain[j]) ) {
				Point p = getIntersection(constrain[i], constrain[j]);
				Point q = p + v;
				flag[ntmp] = sgn(constrain[j].func(q));
				tmp[ntmp++] = p;
			} else {
				assert(sgn(dot(constrain[i].getVector(), constrain[j].getVector())) == -1);
				if ( sgn(constrain[j].func(constrain[i].getOnePoint())) < 0 )
					return false;
			}
		int low = -1, high = -1;
		for ( int j = 0; j < ntmp; j ++ ) {
			if ( flag[j] == 1 ) {
				if ( high == -1 || tmp[high] < tmp[j] )
					high = j;
			} else {
				if ( low == -1 || tmp[low] > tmp[j] )
					low = j;
			}
		}
		if ( low != -1 && high != -1 && tmp[high] > tmp[low] )
			return false;
		if ( low == -1 ) {
			if ( high != -1 )
				cur = tmp[high];
			else
				cur = constrain[i].getOnePoint();
		} else
			cur = tmp[low];
	}
	return true;
}

int main() {
	freopen("t.in", "r", stdin);
	srand(42);
	scanf("%d", &nconvex);
	for ( int i = 0; i < nconvex; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		convex[i] = Point(x, y);
	}
	convex[nconvex] = convex[0];
	reverse(convex, convex + nconvex + 1);

	val_t lb = 0, rb = 2*1e7;
	while ( rb - lb > 1e-5 ) {
		val_t mid = (lb + rb) / 2;
		if ( check(mid) )
			lb = mid;
		else
			rb = mid;
	}
	cout << setprecision(18) << setiosflags(ios::fixed) << lb;
}
