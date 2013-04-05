#include <cassert>
#include <vector>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const double PI = atan2(1.0, 1.0) * 4;
const double G = 9.18;
const double EPS = 10e-4;

bool iszero(double x) {
	return fabs(x) < EPS;
}

struct Point {
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
};

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y- p2.y);
}

double dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

bool is_intersected(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	double t1 = cross(q1 - p1, p2 - p1),
		 t2 = cross(p2 - p1, q2 - p1),
		 t3 = cross(p2 - q1, q2 - q1),
		 t4 = cross(q2 - q1, p1 - q1);
	double c1 = t1 * t2 ,
		 c2 = t3 * t4;
	return (c1 >= 0 || iszero(t1) || iszero(t2)) && (c2 >= 0 || iszero(t3) || iszero(t4));
}


struct DamBoard {
	double h, k;
	int sz, type;
	Point p[11];
	void input() {
		cin >> h;
		cin >> sz;
		for ( int i = 0; i < sz; i ++ )
			cin >> p[i].x >> p[i].y;
		p[sz] = p[0];
		cin >> type >> k;
	}
	void spell(Point &V) {
		if ( type == 0 ) {
			Point vy(cos(PI / 2 - k), sin(PI / 2 - k)),
				  vx(cos(-k), sin(-k));
			V = Point(dot(vx, V), dot(vy, V));
		} else if ( type == 1 ) 
			V.x = k;
		else
			V.y = k;
	}
	bool inside(const Point &it) {
		for ( int i = 0; i < sz; i ++ )
			if ( iszero(cross(it - p[i], p[i + 1] - p[i])) 
						&& min(p[i].x, p[i + 1].x) <= it.x 
						&& it.x <= max(p[i].x, p[i + 1].x)  )
				return true;
		int cnt = 0;
		for ( int i = 0; i < sz; i ++ )
			if ( min(p[i].x, p[i + 1].x) < it.x 
					&& it.x <= max(p[i].x, p[i + 1].x) )
				if ( is_intersected(p[i], p[i + 1], it, Point(it.x, it.y + 2000)) )
					cnt ++;
		return cnt == 1;
	}
	Point calc(const Point &it, const Point &V) {
		vector<Point> vp;
		Point to = V;
		while ( fabs(to.x) <= 2000 && fabs(to.y) <= 2000 ) {
			if ( !iszero(to.x) )
				to.x *= 2;
			if ( !iszero(to.y) )
				to.y *= 2;
		}
		to.x += it.x, to.y += it.y;
		for ( int i = 0; i < sz; i ++ )
			if ( is_intersected(p[i], p[i + 1], it, to) 
					&& !iszero(cross(V, p[i + 1] - p[i]))) {
				double a = to.y - it.y, b = it.x - to.x,
					   c = -(it.x * a + it.y * b);
				double u = fabs(a * p[i].x + b * p[i].y + c),
					   v = fabs(a * p[i + 1].x + b * p[i + 1].y + c);
				vp.push_back(Point((u * p[i + 1].x + v * p[i].x) / (u + v), 
						(u * p[i + 1].y + v * p[i].y) / (u + v)));
			}
		assert(vp.size() > 0);
		if ( vp.size() == 1 )
			return vp[0];
		for ( int i = 0; i < (int)vp.size(); i ++ )
			if ( fabs(vp[i].x - it.x) > EPS 
					|| fabs(vp[i].y - it.y) > EPS )
				return vp[i];
		assert(0);
	}
} dam[10];

bool exist[10];
void solve() {
	Point V, C;
	double H, res = 0;
	int N;

	C.x = C.y = 0;
	cin >> V.x >> V.y >> H;
	cin >> N;
	memset(exist, -1, sizeof(exist));
	for ( int i = 0; i < N; i ++ ) {
		dam[i].input();
		if ( dam[i].h < 0 || iszero(dam[i].h) ) 
			exist[i] = false;
	}

	if ( H < 0 ) {
		printf("Forever!\n");
		return;
	}

	while ( 1 ) {
		if ( iszero(H) ) {
			cout << setiosflags(ios::fixed) << setprecision(2) << res << '\n';
			return;
		}
		if ( iszero(V.x) && iszero(V.y) ) {
			printf("Forever!\n");
			return;
		}
		int t = -1;
		for ( int i = 0; i < N; i ++ )
			if ( dam[i].h <= H && exist[i] && (t == -1 || dam[t].h < dam[i].h) )
				t = i;
		if ( t == -1 ) {
			res += sqrt(2 * H / G);
			cout << setiosflags(ios::fixed) << setprecision(2) << res << '\n';
			return;
		}

		double spend = sqrt(2 * (H - dam[t].h) / G);
		if ( !dam[t].inside(Point(C.x + V.x * spend, C.y + V.y * spend)) ) {
			exist[t] = false;
			continue;
		}
		H = dam[t].h;
		C.x += V.x * spend, C.y += V.y * spend;
		res += spend;
		exist[t] = false;

		dam[t].spell(V);

		if ( iszero(V.x) && iszero(V.y) ) {
			printf("Forever!\n");
			return;
		}
		Point nxt = dam[t].calc(C, V);
		if ( iszero(V.x) )
			res += fabs((nxt.y - C.y) / V.y);
		else
			res += fabs((nxt.x - C.x) / V.x);
		C = nxt;
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	cin >> TST;
	for ( int i = 1; i <= TST; i ++ ) {
		printf("Case %d: ", i);
		solve();
	}
}
