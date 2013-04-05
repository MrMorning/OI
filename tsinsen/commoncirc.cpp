#define UDEB
#include <cstdio>
#include <cassert>
#include <cmath>
#include <set>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
typedef double val_t;

const val_t kEps = 1e-12;
const val_t kInf = 1e100;

#define SLOPE 0

int cmp = 0;

inline int sgn(val_t x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

inline bool myEqual(val_t x, val_t y) {
	return sgn(x-y) == 0;
}
inline bool myGreater(val_t x, val_t y) {
	return sgn(x-y) > 0;
}
inline bool myLess(val_t x, val_t y) {
	return sgn(x-y) < 0;
}

struct Point {
	val_t x, y;
	Point(){}
	Point(val_t xx, val_t yy):
		x(xx), y(yy){}
};

struct Line {
	val_t k, b;
	Line(){}
	Line(val_t kk, val_t bb):
		k(kk), b(bb){}
	val_t calcY(val_t x) const {
		return k * x + b;
	}
	bool on(Point p) {
		return myEqual(calcY(p.x), p.y);
	}
	bool above(Point p) {
		return myLess(calcY(p.x), p.y);
	}
	bool below(Point p) {
		return myGreater(calcY(p.x), p.y);
	}
	bool onOrAbove(Point p) {
		return on(p) || myLess(calcY(p.x), p.y);
	}
	bool onOrBelow(Point p) {
		return on(p) || myGreater(calcY(p.x), p.y);
	}
};

struct Info {
	Line l;
	val_t lb, rb;
	Info(Line ll, val_t lbb, val_t rbb):
		l(ll), lb(lbb), rb(rbb){}
	Info(val_t kk, val_t bb, val_t lbb, val_t rbb):
		l(kk, bb), lb(lbb), rb(rbb){}
};

struct setCmp {
	bool operator() (const Info &A, const Info &B) const {
		if ( cmp == SLOPE ) 
			return myLess(A.l.k, B.l.k);
		else
			return myLess(A.lb, B.lb);
	}
};

typedef set<Info, setCmp> set_t;
typedef set_t::iterator itr_t;

set_t S;

Point calcLeftPoint(Info I) {
	assert(!myEqual(kInf,I.lb));
	return Point(I.lb, I.l.calcY(I.lb));
}
Point calcRightPoint(Info I) {
	assert(!myEqual(kInf,I.rb));
	return Point(I.rb, I.l.calcY(I.rb));
}
Point getItc(const Line &l1, const Line &l2) {
	assert(!myEqual(l1.k, l2.k));
	double x = (l2.b-l1.b)/(l1.k-l2.k);
	return Point(x, l1.k*x+l1.b);
}

void addLine(val_t k, val_t b) {
#ifndef UDEB
	fprintf(stderr, "Add line %.3lf %.3lf\n", k, b);
	fprintf(stderr, "size= %d\n", S.size());
	foreach(it, S)
		fprintf(stderr, "y >= %.3lfx+%.3lf, [%.3lf %.3lf]\n", it->l.k, it->l.b, it->lb, it->rb);
#endif
	cmp = SLOPE;
	Line newL(k, b);
	itr_t succ = S.lower_bound(Info(k, b, 0, 0));
	if ( succ != S.end() ) {
		if ( myEqual(newL.k, succ->l.k) ) {
			if ( !myGreater(newL.b, succ->l.b) )
				return;	
		} else if ( newL.onOrAbove(calcLeftPoint(*succ)) )
			return;
	}

	Info newInfo(k, b, 0, 0);
	if ( succ == S.end() )
		newInfo.rb = kInf;
	if ( succ == S.begin() )
		newInfo.lb = -kInf;

	if ( succ != S.begin() ) {
		itr_t pred = succ;
		pred --;
		while ( pred != S.begin() && newL.below(calcLeftPoint(*pred)) ) {
			itr_t next = pred;
			next--;
			S.erase(pred);
			pred = next;
		}
		if ( myEqual(newL.k, pred->l.k) ) 
			S.erase(pred);
		else {
			Point itc = getItc(newL, pred->l);
			Info predInfo = *pred;
			predInfo.rb = itc.x;
			newInfo.lb = itc.x;
			S.erase(pred);
			S.insert(predInfo);
		}
	}

	if ( succ != S.end() ) {
		while ( succ != --S.end() && newL.below(calcRightPoint(*succ)) ) {
			itr_t next = succ;
			next++;
			assert(next != S.end());
			S.erase(succ);
			succ = next;
		}
		if ( myEqual(newL.k, succ->l.k) )
			S.erase(succ);
		else {
			Point itc = getItc(newL, succ->l);
			Info succInfo = *succ;
			succInfo.lb = itc.x;
			newInfo.rb = itc.x;
			S.erase(succ);
			S.insert(succInfo);
		}
	}

	S.insert(newInfo);
}

bool inside(Point p) {
	//fprintf(stderr, "inside %.3lf %.3lf?\n", p.x, p.y);
	if ( S.size() == 0 ) return false;
	cmp = !SLOPE;
	itr_t it = S.lower_bound(Info(0, 0, p.x, p.x));
	if ( it == S.end() || myGreater(it->lb, p.x) )
		it--;
	return !myGreater(it->l.calcY(p.x), p.y);
}

int main() {
//	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	while ( n -- ) {
		int t;
		val_t x, y;
		scanf("%d%lf%lf", &t, &x, &y);
		if ( t == 0 ) {
			val_t agl = atan2(y, x),
				  rad = 2*sqrt(x*x+y*y);
			rad = 1 / rad;
			x = cos(agl) * rad, y = sin(agl) * rad;
			val_t k = y / x;
			k = -1 / k;
			val_t b = y - k * x;
			addLine(k, b);
		} else {
			val_t agl = atan2(y, x),
				  rad = sqrt(x*x+y*y);
			rad = 1 / rad;
			x = cos(agl) * rad, y = sin(agl) * rad;
			printf("%s\n", inside(Point(x,y))?"Yes":"No");
		}
	}
}
