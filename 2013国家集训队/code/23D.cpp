#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int kSearchTimes = 50;
const double kRadMax = 100.0;
const double PI = acos(-1);
const double kEps = 1e-8;

inline double sqr(double x) { return x * x; }
inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

struct Point {
	double x, y;
	Point(){}
	Point(double xx, double yy):
		x(xx), y(yy){}
};

double getDist(const Point &p1, const Point &p2) {
	return sqrt(sqr(p1.x-p2.x) + sqr(p1.y-p2.y));
}

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator* (const Point &p1, double k) {
	return Point(p1.x * k, p1.y * k);
}

double dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

void rotate(Point &p, double agl) {
	Point vy = Point(cos(PI/2-agl), sin(PI/2-agl)),
		  vx = Point(cos(-agl), sin(-agl));
	p = Point(dot(p, vx), dot(p, vy));
}

void elim(double mat[2][3], int n, int m) {
	int p = 0;
	for ( int i = 0; i < m-1; i ++ ) {
		int k = -1;
		for ( int j = p; j < n; j ++ )
			if ( sgn(mat[j][i]) != 0 ) {
				k = j;
				break;
			}
		if ( k == -1 ) 
			continue;
		for ( int t = 0; t < m; t ++ ) swap(mat[p][t], mat[k][t]);
		double tmp = 1.0/mat[p][i];
		for ( int t = 0; t < m; t ++ ) mat[p][t] *= tmp;
		for ( int t = 0; t < n; t ++ )
			if ( t != p && sgn(mat[t][i]) != 0 ) {
				double c = mat[t][i] / mat[p][i];
				for ( k = 0; k < m; k ++ ) 
					mat[t][k] -= c * mat[p][k];
			}
		p++;
	}
}

bool noSol(double mat[2][3], int n, int m) {
	for ( int i = 0; i < n; i ++ ) {
		bool allZero = true;
		for ( int k = 0; k < m-1; k ++ )
			allZero &= sgn(mat[i][k]) == 0;
		if ( allZero && sgn(mat[i][m-1]) != 0 )
		   return true;	
	}
	return false;
}

Point Q1, Q2, Q3, Q4;

bool test(Point p1, Point p2, Point p3) {
	double mat[2][3];
	Point p4 = (p1+p2)*0.5, p5 = (p1+p3)*0.5;
	Point v1(p1.y-p2.y, p2.x-p1.x),
		  v2(p1.y-p3.y, p3.x-p1.x);
	mat[0][0] = v1.x, mat[0][1] = v2.x, mat[0][2] = 2*p1.x-p4.x-p5.x;
	mat[1][0] = v1.y, mat[1][1] = v2.y, mat[1][2] = 2*p1.y-p4.y-p5.y;
	elim(mat, 2, 3);
	if ( !noSol(mat, 2, 3) ) {
		Q1 = Point(mat[0][2] * v1.x + p4.x, mat[0][2] * v1.y + p4.y);
		Q2 = Point(mat[1][2] * v2.x + p5.x, mat[1][2] * v2.y + p5.y);
		Q3 = Q2 + ((p3-Q2) * 2);
		Q4 = Q1 + ((p2-Q1) * 2);
		int type = sgn(cross(Q2-Q1,Q3-Q2));
		if ( type != 0 && type == sgn(cross(Q3-Q2,Q4-Q3)) && type == sgn(cross(Q4-Q3, Q1-Q4)) 
				&& type == sgn(cross(Q1-Q4,Q2-Q1)) ) {
			printf("YES\n");
			printf("%.10lf %.10lf %.10lf %.10lf ", Q1.x, Q1.y, Q2.x, Q2.y);
			printf("%.10lf %.10lf %.10lf %.10lf\n", Q3.x, Q3.y, Q4.x, Q4.y);
			return true;
		}
	}
	return false;
}

void solve() {
	int x1, y1, x2, y2, x3, y3;
	scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
	Point p1(x1, y1), p2(x2, y2), p3(x3, y3);
	if ( test(p1, p2, p3) ) return;
	if ( test(p2, p1, p3) ) return;
	if ( test(p3, p1, p2) ) return;
	printf("NO\n\n");
}

int main() {
	freopen("t.in", "r", stdin);
	int TST = 0;
	scanf("%d", &TST);
	while ( TST -- ) 
		solve();
}
