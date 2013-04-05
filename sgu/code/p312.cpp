#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;

typedef double val_t;

char out[4][1000];
int nOut;
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

void solve3() {
	val_t S1, S2, S3;
	Point v4, v5, p1, p2, p3, p4, p5, p6;
	scanf("%lf%lf", &p1.x, &p1.y);
	scanf("%lf%lf", &p2.x, &p2.y);
	scanf("%lf%lf", &p3.x, &p3.y);

	scanf("%lf:%lf:%lf", &S1, &S2, &S3);
	v4 = p3 - p2;
	v4 = v4 / (S1 + S3);
	v4 = v4 * S1;
	p4 = p2 + v4;

	v5 = p1 - p3;
	v5 = v5 / (S1 + S2);
	v5 = v5 * S2;
	p5 = p3 + v5;

	p6 = getItc(p1, p4, p2, p5);

	printf("3 %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf\n", 
			p1.x, p1.y, p2.x, p2.y, p6.x, p6.y);
	printf("3 %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf\n", 
			p2.x, p2.y, p3.x, p3.y, p6.x, p6.y);
	printf("3 %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf\n", 
			p3.x, p3.y, p1.x, p1.y, p6.x, p6.y);
}

void work(Point p1, Point p2, Point p3, Point p5, val_t S1, val_t S2) {
	Point v6, p6;
	val_t Sa = fabs(cross(p1 - p2, p5 - p2) / 2),
		  Sb = fabs(cross(p5 - p2, p3 - p2) / 2);
	val_t Sx = (Sa * S2 - Sb * S1) / (S1 + S2);
	if ( Sx > 0 ) {
		v6 = p1 - p5;
		v6 = v6 * (Sx / Sa);
		p6 = p5 + v6;
		sprintf(out[nOut++], "3 %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf", 
				p1.x, p1.y, p2.x, p2.y, p6.x, p6.y);
		sprintf(out[nOut++], "4 %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf", 
				p2.x, p2.y, p3.x, p3.y, p5.x, p5.y, p6.x, p6.y);
	} else {
		v6 = p3 - p5;
		v6 = v6 * (-Sx / Sb);
		p6 = p5 + v6;
		sprintf(out[nOut++], "4 %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf", 
				p1.x, p1.y, p2.x, p2.y, p6.x, p6.y, p5.x, p5.y);
		sprintf(out[nOut++], "3 %.12lf %.12lf %.12lf %.12lf %.12lf %.12lf", 
				p2.x, p2.y, p3.x, p3.y, p6.x, p6.y);
	}
}

void solve4() {
	val_t S1, S2, S3, S4;
	Point v5, p1, p2, p3, p4, p5;
	scanf("%lf%lf", &p1.x, &p1.y);
	scanf("%lf%lf", &p2.x, &p2.y);
	scanf("%lf%lf", &p3.x, &p3.y);
	scanf("%lf%lf", &p4.x, &p4.y);
	scanf("%lf:%lf:%lf:%lf", &S1, &S2, &S3, &S4);

	bool tag = false;
	if ( sgn(cross(p1 - p2, p3 - p1)) * sgn(cross(p3 - p1, p4 - p1)) < 0 ) {
		tag = true;
		swap(p1, p2);
		swap(p2, p3);
		swap(p3, p4);
		swap(S1, S2);
		swap(S2, S3);
		swap(S3, S4);
	}

	v5 = p4 - p2;
	v5 = v5 / (S1 + S2 + S3 + S4);
	v5 = v5 * (S1 + S2);
	p5 = p2 + v5;

	work(p1, p2, p3, p5, S1, S2);
	work(p3, p4, p1, p5, S3, S4);
	for ( int i = 0; i < 4; i ++ )
		printf("%s\n", out[(i - tag + 4) % 4]);
}

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	if ( n == 3 ) 
		solve3();
	else
		solve4();
}

