#include <cstdio>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

typedef double val_t;

const val_t kEps = 1e-8;
const int kNMax = 1010;
const int kSegMax = 3010;
const val_t PI = acos(-1);

inline int sgn(val_t x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

inline bool myEqual(val_t x, val_t y) {
	return sgn(x-y) == 0;
}

inline bool myLess(val_t x, val_t y) {
	return sgn(x-y) < 0;
}
inline bool myGreater(val_t x, val_t y) {
	return sgn(x-y) > 0;
}


inline val_t sqr(val_t x) { return x * x; }

inline val_t myAcos(val_t agl) {
	assert(myEqual(fabs(agl), 1) || myLess(fabs(agl),1));
	if ( agl > 1 ) return acos(1);
	else if ( agl < -1 ) return acos(-1);
	return acos(agl);
}

inline val_t myAtan2(val_t y, val_t x) {
	val_t res = atan2(y, x);
	if ( res < 0 ) res += 2*PI;
	return res;
}

struct Point {
	val_t x, y;
	Point(){}
	Point(val_t xx, val_t yy):x(xx), y(yy){}
} p[kNMax];

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x,p1.y-p2.y);
}

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x+p2.x,p1.y+p2.y);
}

Point operator* (const Point &p, val_t k) {
	return Point(p.x*k,p.y*k);
}

val_t dot(const Point &p1, const Point &p2) {
	return p1.x*p2.x+p1.y*p2.y;
}

val_t calcDist(const Point &p1, const Point &p2) {
	return sqrt(dot(p1-p2,p1-p2));
}

Point rotate(const Point &p, val_t agl) {
	Point vx(cos(-agl), sin(-agl)),
		  vy(cos(PI/2-agl), sin(PI/2-agl));
	return Point(dot(vx,p), dot(vy,p));
}

val_t rad[kNMax];
bool ban[kNMax];
int nSeg;

struct Segment {
	val_t l, r;
	Segment(){}
	Segment(val_t ll, val_t rr):l(ll),r(rr){}
	bool operator< (const Segment &S) const {
		return l < S.l;
	}
} seg[kSegMax];

int main() {
	freopen("t.in", "r", stdin);
	freopen("ANDOOR.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	val_t W, H;
	int n;
	for ( int tst = 0; tst < TST; tst ++ ) {
		scanf("%lf%lf%d", &W, &H, &n);
		for ( int i = 0; i < n; i ++ )
			scanf("%lf%lf%lf", &p[i].x, &p[i].y, &rad[i]);

		memset(ban, 0, sizeof(ban));
		for ( int i = 0; i < n; i ++ )
			for ( int j = 0; j < n; j ++ )
				if ( i != j ) {
					if ( myEqual(calcDist(p[i],p[j]),rad[j]-rad[i])
							|| myLess(calcDist(p[i], p[j]), rad[j] - rad[i]) )
						ban[i] = true;
				}
		for ( int i = 0; i < n; i ++ )
			if ( myGreater(p[i].x-rad[i],W) || myGreater(p[i].y-rad[i],H) )
				ban[i] = true;

		val_t finalAns = 0;
		for ( int i = 0; i < n; i ++ )
			if ( !ban[i] ) {
				nSeg = 0;
				for ( int j = 0; j < n; j ++ )
					if ( i != j && !ban[j] )	   
						if ( myGreater(calcDist(p[i], p[j]), abs(rad[i]-rad[j]))
								&& myLess(calcDist(p[i], p[j]), rad[i]+rad[j]) ) {

							val_t d = calcDist(p[i], p[j]);
							val_t alp = myAcos((sqr(rad[i])+sqr(d)-sqr(rad[j])) / (2*d*rad[i]));
							val_t agl0 = myAtan2(p[j].y-p[i].y,p[j].x-p[i].x);
							if ( myLess(agl0-alp, 0) ) {
								seg[nSeg++] = Segment(agl0-alp+2*PI, 2*PI);
								seg[nSeg++] = Segment(0, agl0+alp);
							} else if ( myEqual(agl0+alp, 2*PI) || myGreater(agl0+alp, 2*PI) ) {
								seg[nSeg++] = Segment(agl0-alp, 2*PI);
								seg[nSeg++] = Segment(0, agl0+alp-2*PI);
							} else {
								seg[nSeg++] = Segment(agl0-alp, agl0+alp);
							}
						}
				if ( myLess(p[i].x-rad[i], 0) ) {
					val_t beta = myAcos(p[i].x/rad[i]);
					seg[nSeg++] = Segment(PI-beta,PI+beta);
				}

				if ( myGreater(p[i].x, W) ) {
					val_t beta = myAcos((p[i].x-W)/rad[i]);
					seg[nSeg++] = Segment(PI+beta,2*PI);
					seg[nSeg++] = Segment(0, PI-beta);
				} else if ( myGreater(p[i].x+rad[i], W) ) {
					val_t beta = myAcos((W-p[i].x)/rad[i]);
					seg[nSeg++] = Segment(2*PI-beta,2*PI);
					seg[nSeg++] = Segment(0,beta);
				}
				if ( myLess(p[i].y-rad[i], 0) ) {
					val_t beta = myAcos(p[i].y/rad[i]);
					seg[nSeg++] = Segment(3*PI/2-beta, 3*PI/2+beta);						
				}
				if ( myGreater(p[i].y, H) ) {
					val_t beta = myAcos((p[i].y-H)/rad[i]);
					seg[nSeg++] = Segment(3*PI/2+beta, 2*PI);
					seg[nSeg++] = Segment(0, 3*PI/2-beta);
				} else if ( myGreater(p[i].y+rad[i], H) ) {
					val_t beta = myAcos((H-p[i].y)/rad[i]);
					seg[nSeg++] = Segment(PI/2-beta,PI/2+beta);
				}
				sort(seg, seg+nSeg);
				val_t curRight = -1e100;
				val_t res = 0;
				for ( int k = 0; k < nSeg; k ++ ) 
					if ( myGreater(seg[k].r, curRight) ) {
						if ( myLess(seg[k].l, curRight) ) {
							res += seg[k].r - curRight;
							curRight = seg[k].r;
						} else {
							res += seg[k].r - seg[k].l;
							curRight = seg[k].r;
						}
					}
				res = 2*PI-res;
				finalAns += res * rad[i];
			}
		if ( myEqual(finalAns,0) )
			finalAns = 0;
		printf("%.4lf\n", finalAns);
	}

}
