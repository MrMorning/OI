#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair

const double kEps = 1E-8, kPi = acos(-1.0);
inline int sgn(double x) {
	if (fabs(x) < kEps) return 0;
	if (x > 0.0) return 1;
	return -1;
}
inline double sqr(double x) {
	return (x * x);
}

typedef pair<double, double> pdd;
const int kMaxN = 1000;
int n;
double w, h;

struct Point {
	double x, y;
	Point() {}
	Point(double x_, double y_) : x(x_), y(y_) {}
} edge[4];

Point core[kMaxN];
double radius[kMaxN];

typedef Point Vector;
inline double len(const Vector &v) {
	return (sqrt(sqr(v.x) + sqr(v.y)));
}
inline double len2(const Vector &v) {
	return (sqr(v.x) + sqr(v.y));
}
inline double angel(const Vector &v) {
	return (atan2(v.y, v.x));
}
inline Vector operator - (const Vector &a, const Vector &b) {
	return Vector(a.x - b.x, a.y - b.y);
}

bool Inside(const Point &p) {
	return (sgn(p.x - 0) >= 0 && sgn(p.x - w) <= 0 && sgn(p.y - 0) >= 0 && sgn(p.y - h) <= 0);
}

bool OnEdge(const Point &p) {
	for (int i = 0; i < 4; ++ i) {
		int j = (i + 1);
		if (j == 4) j = 0;
		if (i & 1) {
			double y0 = min(edge[i].y, edge[j].y), y1 = max(edge[i].y, edge[j].y);
			if (sgn(p.x - edge[i].x) == 0 && sgn(p.y - y0) >= 0 && sgn(p.y - y1) <= 0) return true;
		}
		else {
			double x0 = min(edge[i].x, edge[j].x), x1 = max(edge[i].x, edge[j].x);
			if (sgn(p.y - edge[i].y) == 0 && sgn(p.x - x0) >= 0 && sgn(p.x - x1) <= 0) return true;
		}
	}
	return false;
}

pdd solve_eq(double A, double B, double C) {
	double D = B * B - 4.0 * A * C;
	if (sgn(D) == 0) D = 0.0;
	else D = sqrt(D);
	return (mp((-B + D) / (2.0 * A), (-B - D) / (2.0 * A)));
}

double calc(const Point &core, double radius, double u_agl, double v_agl) {
	if (sgn(u_agl - v_agl) >= 0) return 0.0;
	static vector<double> intersect;
	intersect.clear();
	for (int i = 0; i < 4; ++ i) {
		int j = i + 1;
		if (j == 4) j = 0;
		double dist;
		if (i & 1) {
			dist = fabs(core.x - edge[i].x);
		}
		else {
			dist = fabs(core.y - edge[i].y);
		}
		if (sgn(dist - radius) > 0) continue;
		double A, B, C;
		if (i & 1) {
			A = 1.0, B = -2.0 * core.y, C = sqr(edge[i].x - core.x) + sqr(core.y) - sqr(radius);
			pdd sol = solve_eq(A, B, C);
			intersect.pb(angel(Point(edge[i].x, sol.first) - core));
			intersect.pb(angel(Point(edge[i].x, sol.second) - core));
		}
		else {
			A = 1.0, B = -2.0 * core.x, C = sqr(edge[i].y - core.y) + sqr(core.x) - sqr(radius);
			pdd sol = solve_eq(A, B, C);
			intersect.pb(angel(Point(sol.first, edge[i].y) - core));
			intersect.pb(angel(Point(sol.second, edge[i].y) - core));
		}
	}
	sort(intersect.begin(), intersect.end());
	int m = 0;
	for (int i = 0; i < int(intersect.size()); ++ i)
		if (!i || sgn(intersect[i] - intersect[i - 1]) > 0) intersect[m ++] = intersect[i];
	intersect.resize(m);
	m = 0;
	for (int i = 0; i < int(intersect.size()); ++ i)
		if (Inside(Point(core.x + radius * cos(intersect[i]), core.y + radius * sin(intersect[i]))))
			intersect[m ++] = intersect[i];
	intersect.resize(m);
	static vector<pdd> segs;
	segs.clear();
	if (m > 1) {
		for (int i = 0; i < m; ++ i) {
			int j = i + 1;
			double u = intersect[i];
			if (j == m) j = 0;
			double v = intersect[j];
			if (i + 1 == m) v += 2.0 * kPi;
			double agl = (u + v) * 0.5;
			Point tmp(core.x + radius * cos(agl), core.y + radius * sin(agl));
			if (Inside(tmp)) {
				v = intersect[j];
				if (sgn(u - v) <= 0) segs.pb(mp(u, v));
				else {
					segs.pb(mp(u, kPi));
					segs.pb(mp(-kPi, v));
				}
			}
		}
	}
	else if (m == 1) {
		bool edged = false;
		Point tmp(core.x + radius * cos(intersect[0]), core.y + radius * sin(intersect[0]));
		for (int i = 0; i < 4; ++ i)
			if (sgn(tmp.x - edge[i].x) == 0 && sgn(tmp.y - edge[i].y) == 0) edged = true;
		tmp = Point(core.x, core.y);
		if (Inside(tmp) && !edged) segs.pb(mp(-kPi, kPi));
	}
	else if (m == 0) {
		Point tmp(core.x + radius, core.y);
		if (Inside(tmp)) segs.pb(mp(-kPi, kPi));
	}
	sort(segs.begin(), segs.end());
	static vector<pair<double, int> > rec;
	rec.clear();
	for (int i = 0; i < int(segs.size()); ++ i) {
		rec.pb(mp(segs[i].first, 1));
		rec.pb(mp(segs[i].second, -1));
	}
	rec.pb(mp(u_agl, 2));
	rec.pb(mp(v_agl, -2));
	int cnt[2];
	cnt[0] = cnt[1] = 0;
	sort(rec.begin(), rec.end());
	m = rec.size();
	double res = 0.0;
	int pre = -1;
	for (int i = 0; i < m; ++ i) {
		if (rec[i].second == 1) ++ cnt[0];
		else if (rec[i].second == -1) -- cnt[0];
		else if (rec[i].second == 2) ++ cnt[1];
		else if (rec[i].second == -2) -- cnt[1];
		if (cnt[0] && cnt[1]) {
			if (pre == -1) pre = i;
		}
		else {
			if (pre != -1) {
				res += radius * (rec[i].first - rec[pre].first);
				pre = -1;
			}
		}
	}
	return res;
}

double Calc(const Point &core, double radius, double u_agl, double v_agl) {
	return (calc(core, radius, u_agl, v_agl));
}

int main() {
	freopen("t.in", "r", stdin);
	int t;
	for (scanf("%d", &t); t --; ) {
		scanf("%lf%lf%d", &w, &h, &n);
		for (int i = 0; i < n; ++ i) {
			scanf("%lf%lf%lf", &core[i].x, &core[i].y, &radius[i]);
		}
		edge[0] = Point(0.0, 0.0);
		edge[1] = Point(w, 0.0);
		edge[2] = Point(w, h);
		edge[3] = Point(0.0, h);
		double res = 0.0;
		for (int i = 0; i < n; ++ i) {
			static vector<pdd> segs;
			segs.clear();
			bool included = false;
			for (int j = 0; j < n; ++ j) if (j != i) {
				double dist2 = len2(core[i] - core[j]);
				if (sgn(dist2 - sqr(radius[i] + radius[j])) >= 0) continue;
				if (sgn(dist2 - sqr(radius[i] - radius[j])) <= 0) {
				   	if (sgn(radius[i] - radius[j]) <= 0) {
						included = true;
						break;
					}
					else continue;
				}
				double agl = angel(core[j] - core[i]);	
				double dlt = acos((sqr(radius[i]) + len2(core[j] - core[i]) - sqr(radius[j])) / (2.0 * radius[i] * len(core[j] - core[i])));
				double u = agl - dlt, v = agl + dlt;
				u += kPi, v += kPi;
				u = fmod(fmod(u, 2.0 * kPi) + 2.0 * kPi, 2.0 * kPi);
				v = fmod(fmod(v, 2.0 * kPi) + 2.0 * kPi, 2.0 * kPi);
				u -= kPi, v -= kPi;
				if (sgn(u - v) <= 0) segs.pb(mp(u, v));
				else {
					segs.pb(mp(u, kPi));
					segs.pb(mp(-kPi, v));
				}
			}
			if (included) continue;
			if (segs.empty()) {
				res += Calc(core[i], radius[i], -kPi, kPi);
			}
			else {
				sort(segs.begin(), segs.end());
				int m = 0;
				for (int j = 0; j < int(segs.size()); ++ j) {
					double st = segs[j].first, ed = segs[j].second;
					while (j + 1 < int(segs.size()) && sgn(segs[j + 1].first - ed) <= 0) {
						ed = max(ed, segs[j + 1].second);
						++ j;
					}
					segs[m ++] = mp(st, ed);
				}
				segs.resize(m);
				for (int j = 0; j < m; ++ j) {
					int k = j + 1;
					if (k == m) k = 0;
					double u = segs[j].second, v = segs[k].first;
					if (sgn(u - v) <= 0)
						res += Calc(core[i], radius[i], u, v);
					else
						res += Calc(core[i], radius[i], u, kPi) + Calc(core[i], radius[i], -kPi, v);
				}
			}
		}
		printf("%.4lf\n", res);
	}
	return 0;
}
