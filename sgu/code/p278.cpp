#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;
const int POINT_MAX = 100000;
const double inf = 1e100;

inline bool fequal(double a, double b) {
	return fabs(a - b) < EPS;
}

struct Point {
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
	double dist() {
		return sqrt(x * x + y * y);
	}
};
int N, A, B;

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

double cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

bool isItc(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	return cross(q1 - p1, p2 - p1) * cross(p2 - p1, q2 - p1) >= 0;
}

Point src;
Point p[POINT_MAX], hull[POINT_MAX], stk[POINT_MAX];
int hullSize;
bool cmpSolar(const Point &p1, const Point &p2) {
	double tmp = cross(p1 - src, p2 - src);
	return !fequal(0, tmp) && tmp > 0;
}

void convexHull() {
	src = Point(inf, inf);
	int id = -1;
	for ( int i = 0; i < N; i ++ ) 
		if ( p[i].x < src.x || (fequal(p[i].x, src.x) && p[i].y < src.y) )
			src = p[i], id = i;
	swap(p[id], p[0]);
	sort(p + 1, p + N, cmpSolar);
	int top = 0;
	for ( int i = 0; i < N; i ++ ) {
		while ( top >= 2 ) {
			double tmp = cross(stk[top - 1] - stk[top - 2], p[i] - stk[top - 1]);
			if ( tmp < 0 || fequal(0, tmp) )
				top --;
			else break;
		}
		stk[top ++] = p[i];
	}

	hullSize = top;
	memcpy(hull, stk, sizeof(Point) * top);
}

int main() {
	scanf("%d%d%d", &N, &A, &B);
	double ans = 0;
	for ( int i = 0; i < N; i ++ ) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		p[i] = Point((double)a / c, (double)b / c);
		double x = min((double)A / p[i].x, (double)B / p[i].y);
		ans = max(ans, x);
	}
	convexHull();
	hull[hullSize] = hull[0];
	for ( int i = 0; i < hullSize; i ++ ) {
		if ( !fequal(cross(hull[i], hull[i + 1]), 0) )
			if ( isItc(Point(0, 0), Point(A, B), hull[i], hull[i + 1]) )
				ans = max(ans, (cross(hull[i], Point(A, B)) + cross(Point(A, B), hull[i + 1])) / cross(hull[i], hull[i + 1]));
	}
	printf("%.6lf\n", ans);
}
