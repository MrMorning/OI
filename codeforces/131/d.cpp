#include <cstdio>
#include <cmath>
const double PI = acos(-1);
int n;

struct Point {
	double x, y;
	Point(double _x, double _y):
		x(_x), y(_y){}
	Point(){}
};

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

double dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

Point rot(const Point &p, double agl) {
	Point vx(cos(-agl), sin(-agl)),
		  vy(cos(PI/2-agl), sin(PI/2-agl));
	return Point(dot(vx, p), dot(vy, p));
}

Point r[5], p[5555];
int a[111][6];

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);

	r[0] = Point(10, 0);
	for ( int i = 1; i <= 4; i ++ )
		r[i] = rot(r[i-1], 2*PI/5);

	p[4] = Point(0,0);
	p[5] = p[4]+r[1];
	p[1] = p[5]+r[2];
	p[2] = p[1]+r[3];
	p[3] = p[2]+r[4];
	for ( int i = 1; i <= 5; i ++ )
		a[1][i] = i;

	int id4 = 4;
	for ( int i = 2; i <= n; i ++ ) {
		p[id4+2] = p[id4] + r[3];
		p[id4+3] = p[id4+2] + r[4];
		p[id4+4] = p[id4+3] + r[0];
		p[id4+5] = p[id4+4] + r[1];
		a[i][1] = id4;
		a[i][2] = id4+2;
		a[i][3] = id4+3;
		a[i][4] = id4+4;
		a[i][5] = id4+5;
		id4 += 4;
	}
	printf("%d\n", id4+1);
	for ( int i = 1; i <= id4+1; i ++ )
		printf("%.10lf %.10lf\n", p[i].x, p[i].y);
	for ( int i = 1; i <= n; i ++ ) {
		for ( int j = 1; j <= 5; j ++ )
			printf("%d ", a[i][j]);
		puts("");
	}
	printf("%d ", 1);
	for ( int i = 1; i <= n; i ++ ) {
		printf("%d ", a[i][3]);
		printf("%d ", a[i][5]);
		printf("%d ", a[i][2]);
		printf("%d ", a[i][4]);
	}
	for ( int i = n - 1; i >= 1; i -- )
		printf("%d ", a[i][4]);
	printf("1\n");
}
