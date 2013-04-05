#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

const int N_MAX = 55; 
const double EPS = 1e-8;
const double PI = acos(-1);

inline int sgn(double x) {
	if ( fabs(x) < EPS ) return 0;
	else if ( x > 0 ) return 1;
	return -1;
}

inline double sqr(double x) {
	return x * x;
}

struct Point {
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
	bool operator< (const Point &t) const {
		return sgn(x - t.x) < 0 || (sgn(x - t.x) == 0 && sgn(y - t.y) < 0);
	}
	bool operator== (const Point &t) const {
		return sgn(t.x - x) == 0 && sgn(t.y - y) == 0;
	}
	bool operator!= (const Point &t) const {
		return !(*this==t);
	}
};
Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator* (const Point &p1, double k) {
	return Point(p1.x * k, p1.y * k);
}

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

double dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

Point rotate(Point p, double agl) {
	Point vx(cos(-agl), sin(-agl)),
		  vy(cos(PI/2-agl), sin(PI/2-agl));
	return Point(dot(vx, p), dot(vy, p));
}

void elim(double mat[2][3], int n, int m) {
	for ( int i = 0, j = 0; i < m - 1; i ++ ) {
		int p;
		for ( p = j; p < n; p ++ )
			if ( sgn(mat[p][i]) != 0 ) 
				break;
		if ( p == n )
			continue;
		for ( int k = 0; k < m; k ++ )
			swap(mat[p][k], mat[j][k]);
		double coef = mat[j][i];
		for ( int k = 0; k < m; k ++ )
			mat[j][k] /= coef;
		for ( p = 0; p < n; p ++ )
			if ( p != j && sgn(mat[p][i]) != 0 ) {
				double t = mat[p][i];
				for ( int k = 0; k < m; k ++ )
					mat[p][k] -= t * mat[j][k];
			}
		j ++;
	}
}

vector<Point> getItc(Point p1, Point p2, double r1, double r2) {
	vector<Point> res;
	double d = sqrt(dot(p1 - p2, p1 - p2));
	if ( sgn(d - (r1 + r2)) > 0 || sgn(fabs(r1 - r2) - d) > 0)
		return res;
	double theta = acos((sqr(r1) + sqr(d) - sqr(r2)) / (2 * r1 * d));
	Point u = rotate(p2 - p1, theta);
	u = (u * (1.0 / d)) * r1;
	res.push_back(p1 + u);
	u = rotate(p2 - p1, -theta);
	u = (u * (1.0 / d)) * r1;
	res.push_back(p1 + u);
	return res;
}

bool onArc(Point pc, Point p1, Point p2, Point p3, Point pt) {
	if ( pt == p1 || pt == p3 )
		return true;
	static pair<double, int> arr[4];
	arr[0] = make_pair(atan2(p1.y - pc.y, p1.x - pc.x), 1);
	arr[1] = make_pair(atan2(p2.y - pc.y, p2.x - pc.x), 2);
	arr[2] = make_pair(atan2(p3.y - pc.y, p3.x - pc.x), 3);
	arr[3] = make_pair(atan2(pt.y - pc.y, pt.x - pc.x), -1);
	sort(arr, arr + 4);
	for ( int i = 0; i < 4; i ++ )
		if ( arr[i].second == -1 ) {
			int prev = arr[(i + 3) % 4].second,
				next = arr[(i + 1) % 4].second;
			return prev == 2 || next == 2;
		}
	assert(0);
}

struct Arc {
	Point core;
	Point p1, p2, p3;
	double rad;
	void read() {
		scanf("%lf%lf", &p1.x, &p1.y);
		scanf("%lf%lf", &p3.x, &p3.y);
		scanf("%lf%lf", &p2.x, &p2.y);

		double mat[2][3] = {
			{2*p2.x-2*p1.x, 2*p2.y-2*p1.y, dot(p2,p2)-dot(p1,p1)},
			{2*p3.x-2*p2.x, 2*p3.y-2*p2.y, dot(p3,p3)-dot(p2,p2)} };

		elim(mat, 2, 3);
		core.x = mat[0][2];
		core.y = mat[1][2];

		rad = sqrt(dot(p1 - core, p1 - core));

		assert(sgn(rad * rad - dot(p2 - core, p2 - core)) == 0);
		assert(sgn(rad * rad - dot(p3 - core, p3 - core)) == 0);
	}
} arc[N_MAX];
int nArc;

bool cksame(const Point &p1, const Point &p2) {
	return sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0;
}

vector<Point> out;

int main() {
	scanf("%d", &nArc);
	for ( int i = 0; i < nArc; i ++ ) 
		arc[i].read();
	for ( int i = 0; i < nArc; i ++ )
		for ( int j = 0; j < nArc; j ++ ) 
			if ( i != j ) {
				if ( arc[i].core == arc[j].core && sgn(arc[i].rad - arc[j].rad) == 0 ) {
					if ( (arc[i].p1 == arc[j].p1 && arc[i].p3 == arc[j].p3)
							|| (arc[i].p1 == arc[j].p3 && arc[i].p3 == arc[j].p1) ) {
						if ( onArc(arc[j].core, arc[j].p1, arc[j].p2, arc[j].p3, arc[i].p2) ) {
							puts("Infinity");
							return 0;
						}
					}
					if ( (arc[j].p1 != arc[i].p1 && arc[j].p1 != arc[i].p3 && onArc(arc[i].core, arc[i].p1, arc[i].p2, arc[i].p3, arc[j].p1))
							|| (arc[j].p3 != arc[i].p1 && arc[j].p3 != arc[i].p3 && onArc(arc[i].core, arc[i].p1, arc[i].p2, arc[i].p3, arc[j].p3)) ) {
						puts("Infinity");
						return 0;
					} 
					if ( arc[j].p1 == arc[i].p1 || arc[j].p1 == arc[i].p3 )
						out.push_back(arc[j].p1);
					if ( arc[j].p3 == arc[i].p1 || arc[j].p3 == arc[i].p3 ) 
						out.push_back(arc[j].p3);
				}
			}
	for ( int i = 0; i < nArc; i ++ )
		for ( int j = i + 1; j < nArc; j ++ ) {
				vector<Point> pointVec = getItc(arc[i].core, arc[j].core, arc[i].rad, arc[j].rad);
				for ( vector<Point>::iterator it = pointVec.begin();
						it != pointVec.end(); it ++ ) {
					if ( onArc(arc[i].core, arc[i].p1, arc[i].p2, arc[i].p3, *it)
							&& onArc(arc[j].core, arc[j].p1, arc[j].p2, arc[j].p3, *it) )
						out.push_back(*it);
				}
			}
	sort(out.begin(), out.end());
	out.resize(unique(out.begin(), out.end(), cksame) - out.begin());
	printf("%d\n", (int)out.size());
	for ( vector<Point>::iterator it = out.begin();
			it != out.end(); it ++ )
		printf("%.3lf %.3lf\n", it->x, it->y);
}
