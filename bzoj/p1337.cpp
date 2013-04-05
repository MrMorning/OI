#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const long double EPS = 10e-10;

struct Point {
	long double x, y;
	Point(){}
	Point(long double _x, long double _y):
		x(_x), y(_y){}
} p[100010], memo[3];
int now;

struct Circle {
	Point core;
	long double r;
	Circle(){}
	Circle(Point _p, long double _r):
		core(_p), r(_r){}
};

int n;

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

long double sqr(long double x) { return x * x; }
long double dist(const Point &p1, const Point &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
long double cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

void elim(long double mat[2][3], int n, int m) {
	for ( int i = 0, j = 0; i < m && j < n; i ++ ) {
		int p;
		for ( p = j; p < n; p ++ ) 
			if ( abs(mat[p][i]) > EPS )
				break;
		if ( p == n )
			continue;
		for ( int k = 0; k < m; k ++ )
			swap(mat[p][k], mat[j][k]);
		long double t = mat[j][i];
		for ( int k = 0; k < m; k ++ )
			mat[j][k] /= t;
		for ( p = 0; p < n; p ++ ) {
			long double t2 = mat[p][i];
			if ( p != j && abs(mat[p][i]) > EPS )
				for ( int k = 0; k < m; k ++ )
					mat[p][k] -= t2 * mat[j][k];
		}
		j ++;
	}
}

Circle calc_core(const Point &p1, const Point &p2) {
	Point pm = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
	return Circle(pm, dist(p1, pm));
}

Circle calc_core(const Point &p1, const Point &p2, const Point &p3) {
	static long double mat[2][3];
	mat[0][0] = 2 * (p2.x - p1.x);
	mat[0][1] = 2 * (p2.y - p1.y);
	mat[0][2] = sqr(p2.x) - sqr(p1.x) + sqr(p2.y) - sqr(p1.y);
	mat[1][0] = 2 * (p3.x - p2.x);
	mat[1][1] = 2 * (p3.y - p2.y);
	mat[1][2] = sqr(p3.x) - sqr(p2.x) + sqr(p3.y) - sqr(p2.y);
	elim(mat, 2, 3);
	Point pm = Point(mat[0][2], mat[1][2]);
	return Circle(pm, dist(p1, pm));
}

bool in_circ(const Point &p1, const Point &p2, const Point &p3, const Point &pt) {
	Circle c = calc_core(p1, p2, p3);
	return dist(pt, c.core) <= c.r;
}

bool in_circ(const Point &p1, const Point &p2, const Point &pt) {
	Circle c = calc_core(p1, p2);
	return dist(pt, c.core) <= c.r;
}
int main() {
	freopen("t.in", "r", stdin);

	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%Lf%Lf", &p[i].x, &p[i].y);
	random_shuffle(p, p + n);
	memo[0] = p[0], memo[1] = p[1];
	now = 0;
	for ( int i = 2; i < n; i ++ )
		if ( (!now && !in_circ(memo[0], memo[1], p[i]))
				|| (now && !in_circ(memo[0], memo[1], memo[2], p[i])) ) {
			now = 0;
			memo[0] = p[i], memo[1] = p[0];
			for ( int j = 1; j < i; j ++ ) {
				if ( (!now && !in_circ(memo[0], memo[1], p[j]))
						|| (now && !in_circ(memo[0], memo[1], memo[2], p[j])) ) {
					now = 0;
					memo[0] = p[i], memo[1] = p[j];
					for ( int k = 0; k < j; k ++ ) {
						if ( (!now && !in_circ(memo[0], memo[1], p[k]))
								|| (now && !in_circ(memo[0], memo[1], memo[2], p[k])) ) {
							if ( abs(cross(memo[1] - memo[0], p[k] - memo[0])) > EPS ) {
								now = 1;
								memo[2] = p[k];
							} else {
								now = 0;
								memo[0].x = min(p[i].x, min(p[j].x, p[k].x));
								memo[0].y = min(p[i].y, min(p[j].y, p[k].y));
								memo[1].x = max(p[i].x, max(p[j].x, p[k].x));
								memo[1].y = max(p[i].y, max(p[j].y, p[k].y));
							}
						}
					}
				}
			}
		}
	Circle res;
	if ( !now )
		res = calc_core(memo[0], memo[1]);	
	else
		res = calc_core(memo[0], memo[1], memo[2]);
	printf("%.10Lf\n", res.r);
	printf("%.10Lf %.10Lf\n", res.core.x, res.core.y);
}
