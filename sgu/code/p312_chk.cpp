#include <cstdio>
#include <cmath>
#include <cassert>

typedef double val_t;
const val_t EPS = 1e-8;

int sgn(val_t x) {
	if ( fabs(x) < EPS )
		return 0;
	if ( x > 0 )
		return 1;
	return -1;
}

struct Point {
	val_t x, y;
	Point(){}
	Point(val_t _x, val_t _y):
		x(_x), y(_y){}
};
Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator* (const Point &p1, val_t k) {
	return Point(p1.x * k, p1.y * k);
}
Point operator/ (const Point &p1, val_t k) {
	return Point(p1.x / k, p1.y / k);
}

val_t dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

val_t cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

val_t getDist(const Point &p1, const Point &p2) {
	return sqrt(dot(p1 - p2, p1 - p2));
}

val_t getDist(const Point &q, const Point &p1, const Point &p2) {
	val_t a = p1.y - p2.y,
		  b = p2.x - p1.x,
		  c = -(a * p1.x + b * p1.y);
	return fabs(a * q.x + b * q.y + c) / sqrt(a * a + b * b);
}

Point getItc(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	val_t a = p1.y - p2.y,
		  b = p2.x - p1.x,
		  c = -(a * p1.x + b * p1.y);
	val_t u = fabs(a * q1.x + b * q1.y + c),
		  v = fabs(a * q2.x + b * q2.y + c);
	return Point((v * q1.x + u * q2.x) / (u + v),
			(v * q1.y + u * q2.y) / (u + v));
}
Point p[4];
val_t ratio[4], area[4];
int main() {
	FILE *fdata = fopen("t.in", "r"),
		 *fans = fopen("t.out", "r");
	int n;
	fscanf(fdata, "%d", &n);
	for ( int i = 0; i < n; i ++ )
		fscanf(fdata, "%lf%lf", &p[i].x, &p[i].y);
	val_t totArea = 0;
	for ( int i = 0; i < n; i ++ ) 
		totArea += cross(p[i], p[(i + 1) % n]);
	totArea = fabs(totArea) / 2;
	val_t totRatio = 0;
	for ( int i = 0; i < n; i ++ ) {
		fscanf(fdata, "%lf", &ratio[i]);
		totRatio += ratio[i];
		fscanf(fdata, "%*c");
	}
	for ( int i = 0; i < n; i ++ ) {
		static Point q[4];
		int m;
		fscanf(fans, "%d", &m);
		for ( int j = 0; j < m; j ++ ) 
			fscanf(fans, "%lf%lf", &q[j].x, &q[j].y);
		area[i] = 0;
		for ( int j = 0; j < m; j ++ )
			area[i] += cross(q[j], q[(j + 1) % m]);
		area[i] = fabs(area[i]) / 2;
		assert(sgn(area[i] / totArea - ratio[i] / totRatio) == 0);
	}
	//assert(sgn((area[0]+area[1]) / totArea - (ratio[0] + ratio[1]) / totRatio) == 0);
}

