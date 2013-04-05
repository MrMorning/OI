#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;
const int kPntMax = 111;
const int kVtxMax = 111;
const double kEps = 1e-8;
inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

struct Point {
	double x, y;
	Point(){}
	Point(double _x, double _y):x(_x), y(_y){}
	bool operator< (const Point &T) const{
		return sgn(x-T.x)<0 || (sgn(x-T.x)==0 && sgn(y-T.y)<0);
	}
	bool operator== (const Point &T) const {
		return sgn(x-T.x)==0&&sgn(y-T.y)==0;
	}
} p[kPntMax], q[kPntMax], ps, pt;
int n, m;
double f[kVtxMax][kVtxMax];
Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x+p2.x, p1.y+p2.y);
}
Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x, p1.y-p2.y);
}
Point operator* (const Point &p1, double k) {
	return Point(p1.x * k, p1.y * k);
}
double cross(const Point &p1, const Point &p2) {
	return p1.x*p2.y-p1.y*p2.x;
}
double dot(const Point &p1, const Point &p2) {
	return p1.x*p2.x+p1.y*p2.y;
}
double calcDist(const Point &p1, const Point &p2) {
	return sqrt(dot(p1-p2, p1-p2));
}

bool isItc(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	if ( sgn(cross(p2-p1,q2-q1)) == 0 ) return false;
	return sgn(cross(q1-p1, p2-p1)) * sgn(cross(p2-p1, q2-p1)) >= 0
		&& sgn(cross(p1-q1, q2-q1)) * sgn(cross(q2-q1, p2-q1)) >= 0;
}

Point getItc(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	double a = p2.y - p1.y,
		   b = p1.x - p2.x,
		   c = -(a*p1.x+b*p1.y);
	double u = fabs(a*q1.x+b*q1.y+c),
		   v = fabs(a*q2.x+b*q2.y+c);
	Point d = q2-q1;
	d = d*(u/(u+v));
	return q1+d;
}

int main() {
	freopen("t.in", "r", stdin);
	for ( int i = 0; i < kVtxMax; i ++ )
		for ( int j = 0; j < kVtxMax; j ++ )
			if ( i != j ) f[i][j] = 1e100;
	scanf("%lf%lf%lf%lf", &ps.x, &ps.y, &pt.x, &pt.y);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%lf%lf", &p[i].x, &p[i].y);
	for ( int i = 0; i < n; i ++ ) {
		int j = (i+1) % n;
		f[i][j] = f[j][i] = calcDist(p[i], p[j]);
		if ( isItc(p[i], p[j], ps, pt) ) {
			q[m] = getItc(p[i], p[j], ps, pt); 
			bool found = false;
			for ( int k = 0; k < m; k ++ )
				if ( q[m] == q[k] ) found = true;
			if ( found ) continue;
			f[i][n+2+m] = f[n+2+m][i] = calcDist(q[m], p[i]);
			f[j][n+2+m] = f[n+2+m][j] = calcDist(q[m], p[j]);
			m++;
		}
	}
	assert(m <= 2);
	double ans;
	if ( m <= 1 ) ans = calcDist(ps, pt);
	else {
		f[n+2][n+3] = f[n+3][n+2] = 2*calcDist(q[0], q[1]);
		if ( calcDist(q[0], ps) < calcDist(q[1], ps) ) {
			f[n][n+2] = f[n+2][n] = calcDist(q[0], ps);
			f[n+1][n+3] = f[n+3][n+1] = calcDist(q[1], pt);
		} else {
			f[n][n+3] = f[n+3][n] = calcDist(q[1], ps);
			f[n+1][n+2] = f[n+2][n+1] = calcDist(q[0], pt);
		}
		int nn = n+m+2;
		for ( int k = 0; k < nn; k ++ )
			for ( int i = 0; i < nn; i ++ )
				for ( int j = 0; j < nn; j ++ )
					if ( f[i][j] > f[i][k] + f[k][j] )
						f[i][j] = f[i][k] + f[k][j];
		ans = f[n][n+1];
	}
	printf("%.10lf\n", ans);
}
