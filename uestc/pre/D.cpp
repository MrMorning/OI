#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

bool feq(long double a, long double b) {
	return fabs(a - b) < 10e-8;
}

long double sqr(long double x) { return x * x; }

struct Point {
	long double x, y;
	Point(){}
	Point(long double _x, long double _y):
		x(_x), y(_y){}
	bool operator< (const Point &p2) const{
		return x < p2.x || (x == p2.x && y < p2.y);
	}
	
	bool operator ==(const Point &p2) const {
		return feq(x, p2.x) && feq(y, p2.y);
	}
};

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

long double cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

long double calc_dist(const Point &p1, const Point &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

void get_its(vector<Point> &res, const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	long double t1 = cross(q2 - p1, p2 - p1) * cross(p2 - p1, q1 - p1),
		 t2 = cross(p2 - q1, q2 - q1) * cross(q2 - q1, p1 - q1);
	if (  (t1 >= 0 || feq(t1, 0))
			&& (t2 >= 0 || feq(t2, 0)) ) {
		long double a = p1.y - p2.y,
			   b = p2.x - p1.x,
			   c = -(a * p1.x + b * p1.y);
		long double u = fabs(q1.x * a + q1.y * b + c),
			   v = fabs(q2.x * a + q2.y * b + c);
		res.push_back(Point((u * q2.x + v * q1.x) / (u + v), (u * q2.y + v * q1.y) / (u + v)));
	}
}


long double Px, Py, L1, W1;
long double Qx, Qy, L2, W2;
long double Sx, Sy, Tx, Ty;
int N;

long double common(long double l1, long double r1, long double l2, long double r2) {
	long double res = min(r1 - l1, r2 - l2);
	res = min(res, r1 - l2);
	res = min(res, r2 - l1);
	return res;
}

bool inside(long double Sx, long double Sy, long double L, long double W, long double tx, long double ty) {
	return Sx <= tx && tx <= Sx + L
		&& Sy <= ty && ty <= Sy + W;
}

long double calc1() {
	long double a = Ty - Sy,
		b = Sx - Tx,
		c = -(a  * Sx + b * Sy);
	if ( feq(a, 0) ) {
		if ( Py < Sy && Sy < Py + W1 )
			return common(Px, Px + L1, min(Sx, Tx), max(Sx, Tx));
		else
			return 0;
	} else if ( feq(b, 0) ) {
		if ( Px < Sx && Sx < Px + L1 )
			return common(Py, Py + W1, min(Sy, Ty), max(Sy, Ty));
		else
			return 0;
	} else {
		static vector<Point> vp;
		vp.clear();
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Px, Py), Point(Px, Py + W1));
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Px, Py + W1), Point(Px + L1, Py + W1));
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Px + L1, Py + W1), Point(Px + L1, Py));
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Px + L1, Py), Point(Px, Py));
		sort(vp.begin(), vp.end());
		vp.resize(unique(vp.begin(), vp.end()) - vp.begin());
		if ( (int)vp.size() == 2 ) {
			return calc_dist(vp[0], vp[1]);
		} else if ( (int)vp.size() == 1 ) {
			if ( inside(Px, Py, L1, W1, Sx, Sy) && inside(Px, Py, L1, W1, Tx, Ty) )
				return calc_dist(Point(Sx, Sy), Point(Tx, Ty));
			else if ( inside(Px, Py, L1, W1, Sx, Sy) && !inside(Px, Py, L1, W1, Tx, Ty) )
				return calc_dist(vp[0], Point(Sx, Sy));
			else if ( !inside(Px, Py, L1, W1, Sx, Sy) && inside(Px, Py, L1, W1, Tx, Ty) )
				return calc_dist(vp[0], Point(Tx, Ty));
			else
				return 0;
		} else {
			if ( inside(Px, Py, L1, W1, Sx, Sy) && inside(Px, Py, L1, W1, Tx, Ty) )
				return calc_dist(Point(Sx, Sy), Point(Tx, Ty));
			else
				return 0;
		}
	 }
}

long double calc2() {
	long double a = Ty - Sy,
		b = Sx - Tx,
		c = -(a  * Sx + b * Sy);
	if ( feq(a, 0) ) {
		if ( Qy <= Sy && Sy <= Qy + W2 )
			return common(Qx, Qx + L2, min(Sx, Tx), max(Sx, Tx));
		else
			return 0;
	} else if ( feq(b, 0) ) {
		if ( Qx <= Sx && Sx <= Qx + L2 )
			return common(Qy, Qy + W2, min(Sy, Ty), max(Sy, Ty));
		else
			return 0;
	} else {
		static vector<Point> vp;
		vp.clear();
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Qx, Qy), Point(Qx, Qy + W2));
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Qx, Qy + W2), Point(Qx + L2, Qy + W2));
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Qx + L2, Qy + W2), Point(Qx + L2, Qy));
		get_its(vp, Point(Sx, Sy), Point(Tx, Ty), Point(Qx + L2, Qy), Point(Qx, Qy));
		sort(vp.begin(), vp.end());
		vp.resize(unique(vp.begin(), vp.end()) - vp.begin());
		if ( (int)vp.size() == 2 ) {
			return calc_dist(vp[0], vp[1]);
		} else if ( (int)vp.size() == 1 ) {
			if ( inside(Qx, Qy, L2, W2, Sx, Sy) && inside(Qx, Qy, L2, W2, Tx, Ty) )
				return calc_dist(Point(Sx, Sy), Point(Tx, Ty));
			else if ( inside(Qx, Qy, L2, W2, Sx, Sy) && !inside(Qx, Qy, L2, W2, Tx, Ty) )
				return calc_dist(vp[0], Point(Sx, Sy));
			else if ( !inside(Qx, Qy, L2, W2, Sx, Sy) && inside(Qx, Qy, L2, W2, Tx, Ty) )
				return calc_dist(vp[0], Point(Tx, Ty));
			else
				return 0;
		} else {
			if ( inside(Qx, Qy, L2, W2, Sx, Sy) && inside(Qx, Qy, L2, W2, Tx, Ty) )
				return calc_dist(Point(Sx, Sy), Point(Tx, Ty));
			else
				return 0;
		}
	 }
}

void solve() {
	cin >> Px >> Py >> L1 >> W1 >> Qx >> Qy >> L2 >> W2;
	if ( inside(Qx, Qy, L2, W2, Px, Py) ) {
		swap(Px, Qx);
		swap(Py, Qy);
		swap(L1, L2);
		swap(W1, W2);
	}
	cin >> N;
	long double res = 0;
	while ( N -- ) {
		cin >> Sx >> Sy >> Tx >> Ty;
		long double tmp = calc1() - calc2();
		res += tmp;
	}
	cout << fixed << setprecision(2) << res << '\n';
}

int main() {
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	int TST;
	cin >> TST;
	for ( int t = 1; t <= TST; t ++ ) {
		cout << "Case #" << t << ": ";
		solve();
	}
}
