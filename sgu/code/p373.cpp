#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#define ALL(X) (X).begin(), (X).end()
using namespace std;

const double kEps = 1e-8;
const double kPi = acos(-1);
const int kLineMax = 10;
const int kSegMax = 1000;
const int kVtxMax = 100;
const int kAreaMax = 11;

inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

inline double sqr(double x) {
	return x * x;
}

struct Point {
	double x, y;
	Point(){}
	Point(double xx, double yy):
		x(xx), y(yy){}
	bool operator< (const Point &p) const {
		return sgn(x-p.x) < 0 || (sgn(x-p.x)==0 && sgn(y-p.y) < 0);
	}
	bool operator== (const Point &p) const {
		return sgn(x-p.x)==0 && sgn(y-p.y)==0;
	}
};

struct Line {
	double a, b, c;
	vector<Point> vp;
	bool parallel(Line l2) {
		return sgn(a*l2.b-b*l2.a)==0;
	}
	Point getItcWithLine(Line l2) {
		double a1 = a, b1 = b, c1 = c,
			   a2 = l2.a, b2 = l2.b, c2 = l2.c;
		double x, y;
		y = -(c1*a2-a1*c2)/(b1*a2-a1*b2);
		if ( sgn(a1) != 0 )
			x = (-c1-b1*y)/a1;
		else
			x = (-c2-b2*y)/a2;
		return Point(x, y);
	}
	bool coincide(Line l2) {
		return parallel(l2) && sgn(b*l2.c-c*l2.b)==0 && sgn(a*l2.c-c*l2.a)==0;
	}
} line[kLineMax];

struct Segment {
	int p[2];
	double w[2];
	bool vis[2];
	int getDir(int x) {
		return x == p[1];
	}
} seg[kSegMax];

vector<Point> dis;
vector<int> adj[kVtxMax];
double area[kAreaMax];
int nArea;
map<int, pair<double, double> > memo;
double R;
vector<Point> circ;
int nSeg;
map<pair<int, int>, bool> hasSeg;

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x,p1.y-p2.y);
}

double cross(const Point &p1, const Point &p2) {
	return p1.x*p2.y-p1.y*p2.x;
}

vector<double> solveEq(double a, double b, double c) {
	double delta = b*b-4*a*c;
	vector<double> res;
	res.pb((sqrt(delta)-b)/(2*a));
	res.pb((-sqrt(delta)-b)/(2*a));
	return res;
}

vector<Point> getItcWithCirc(Line l) {
	vector<Point> res;
	double a = l.a, b = l.b, c = l.c;
	if ( sgn(a) != 0 ) {
		vector<double> tmp = solveEq(sqr(b/a)+1, 2*c*b/sqr(a),sqr(c/a)-sqr(R));
		foreach(it, tmp)
			res.pb(Point((-c-b*(*it))/a, *it));
	} else {
		vector<double> tmp = solveEq(sqr(a/b)+1, 2*c*a/sqr(b),sqr(c/b)-sqr(R));
		foreach(it, tmp)
			res.pb(Point(*it, (-c-a*(*it))/b));
	}
	return res;
}


bool cmpTurn(Point p1, Point p2, Point q1, Point q2) {
	int sign1 = sgn(cross(p1-p2,q1-p2)),
		sign2 = sgn(cross(p1-p2,q2-p2));
	if ( sign1 != sign2 ) 
		return sign2 < sign1;
	if (!(sign1 != 0))
		assert(0);
	return sgn(cross(q2-p2,q1-p2)) < 0;
}

bool cmpByAgl(const Point &p1, const Point &p2) {
	return sgn(atan2(p1.y,p1.x)-atan2(p2.y,p2.x)) < 0;
}
bool eqByAgl(const Point &p1, const Point &p2) {
	return sgn(atan2(p1.y,p1.x)-atan2(p2.y,p2.x)) == 0;
}

int curStd;
#define CMP_X 0
#define CMP_Y 1
bool cmpByXY(const Point &p1, const Point &p2) {
	if ( curStd == CMP_X ) 
		return sgn(p1.x-p2.x) < 0;
	else
		return sgn(p1.y-p2.y) < 0;
}
bool eqByXY(const Point &p1, const Point &p2) {
	if ( curStd == CMP_X ) 
		return sgn(p1.x-p2.x) == 0;
	else
		return sgn(p1.y-p2.y) == 0;
}

double calcAgl(const Point &p) {
	return atan2(p.y,p.x);
}
double calcArcArea(double agl) {
	while ( sgn(agl-0) < 0 )
		agl += 2 * kPi;
	while ( sgn(agl-2*kPi) >= 0 )
		agl -= 2*kPi;
	return 0.5*agl*R*R-0.5*sin(agl)*R*R;
}

Point getPointOnCirc(double agl) {
	return Point(cos(agl)*R, sin(agl)*R);
}

int getID(const Point &p) {
	return lower_bound(ALL(dis), p)-dis.begin();
}

void addSeg(int p0, int p1, double w0, double w1) {
	if ( p0 == p1 || hasSeg[mp(p0,p1)] ) return;
	Segment &x = seg[nSeg++];
	x.p[0] = p0, x.p[1] = p1;
	x.w[0] = w0, x.w[1] = w1;
	adj[p0].pb(nSeg-1);
	adj[p1].pb(nSeg-1);
	hasSeg[mp(p0,p1)] = hasSeg[mp(p1,p0)] = true;
}

void dfs(int i, int curP, int src, double acc) {
	int best = -1;
	int i1 = seg[i].p[0], i2 = seg[i].p[1];
	if ( i2 != curP )
		swap(i1, i2);
	seg[i].vis[seg[i].getDir(curP)] = true;
	Point p1 = dis[i1], p2 = dis[i2];
	acc += cross(p1, p2) / 2;
	acc += seg[i].w[seg[i].getDir(i2)];
	if ( i2 == src ) {
		if ( sgn(acc) > 0 )
			area[nArea++] = acc;
		return;
	}
	foreach(it, adj[curP]) 
		if ( *it != i && !seg[*it].vis[!seg[*it].getDir(i2)]) {
			if ( best == -1 || cmpTurn(p1, p2, 
						dis[seg[best].p[0]+seg[best].p[1]-i2],
						dis[seg[*it].p[0]+seg[*it].p[1]-i2]) )
				best = *it;
		}
	assert(best != -1);
	int q = seg[best].p[!seg[best].getDir(i2)];
	dfs(best, q, src, acc);
}

#define GET(s, i) (((s)>>(2*(i)))&3)
#define SET(s, i, x) ((s)+((x)<<(2*(i))))
pair<double, double> dp(int s) {
	if ( memo.count(s) ) return memo[s];
	pair<double, double> &res = memo[s] = mp(-1, -1);
	double sum1 = 0, sum2 = 0;
	bool over = true;
	for ( int i = 0; i < nArea; i ++ )
		if ( GET(s, i) == 1 )
			sum1 += area[i];
		else if ( GET(s, i) == 2 )
			sum2 += area[i];
		else 
			over = false;
	if ( over ) return res = mp(0, 0);
	if ( sgn(sum1-sum2) <= 0 ) {
		res = mp(-1, -1);
		for ( int i = 0; i < nArea; i ++ )
			if ( GET(s, i) == 0 ) {
				double tmp = dp(SET(s, i, 1)).first + area[i];
				if ( sgn(tmp-res.first) > 0 )
					res = mp(tmp, dp(SET(s, i, 1)).second);
			}
	} else {
		res = mp(-1, -1);
		for ( int i = 0; i < nArea; i ++ )
			if ( GET(s, i) == 0 ) {
				double tmp = dp(SET(s, i, 2)).second + area[i];
				if ( sgn(tmp-res.second) > 0 )
					res = mp(dp(SET(s, i, 2)).first, tmp);
			}
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d%lf" , &n, &R);
	/*double randAgl = (double)rand() / RAND_MAX * 2*kPi;
	circ.pb(getPointOnCirc(randAgl));
	circ.pb(getPointOnCirc(randAgl+kPi/2));
	circ.pb(getPointOnCirc(randAgl+kPi));
	circ.pb(getPointOnCirc(randAgl+3*kPi/2));
	*/
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%lf%lf%lf", &line[i].a, &line[i].b, &line[i].c);
		vector<Point> tv = getItcWithCirc(line[i]);
		assert((int)tv.size()==2);
		foreach(it, tv) {
			line[i].vp.pb(*it);
			circ.pb(*it);
		}
		double agl0 = calcAgl(tv[0]),
			   agl1 = calcAgl(tv[1]);
		circ.pb(getPointOnCirc((agl0+agl1)/2));
		circ.pb(getPointOnCirc((agl0+agl1)/2+kPi));
	}

	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ )
			if ( i != j && !line[i].parallel(line[j]) ) {
				Point p = line[i].getItcWithLine(line[j]);
				if ( sgn(sqr(p.x)+sqr(p.y)-sqr(R)) <= 0 )
					line[i].vp.pb(p);
			}	

	foreach(it, circ)
		dis.pb(*it);
	for ( int i = 1; i <= n; i ++ )
		foreach(it, line[i].vp)
			dis.pb(*it);
	sort(ALL(dis));
	dis.resize(unique(ALL(dis)) - dis.begin());

//	foreach(it, dis)
//		printf("%.3lf %.3lf\n", it->x, it->y);

	sort(ALL(circ), cmpByAgl);
	circ.resize(unique(ALL(circ))-circ.begin());
	for ( int sz = circ.size(), i = 0; i < sz; i ++ ) {
		double tmp = calcArcArea(calcAgl(circ[(i+1)%sz])-calcAgl(circ[i]));
		addSeg(getID(circ[i]), getID(circ[(i+1)%sz]), 0, tmp);
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( sgn(line[i].vp[0].x-line[i].vp[1].x) == 0 ) 
			curStd = CMP_Y;
		else curStd = CMP_X;
		sort(ALL(line[i].vp), cmpByXY);
		line[i].vp.resize(unique(ALL(line[i].vp))-line[i].vp.begin());
		int sz = line[i].vp.size();
		for ( int j = 0; j < sz-1; j ++ )
			addSeg(getID(line[i].vp[j]), getID(line[i].vp[j+1]), 0, 0);
	}

	for ( int i = 0; i < nSeg; i ++ ) {
		for ( int d = 0; d <= 1; d ++ )
			if ( !seg[i].vis[d] )
				dfs(i, seg[i].p[d], seg[i].p[!d], 0);
	}

	assert(nArea <= 11);
	printf("%.4lf %.4lf\n", dp(0).first, dp(0).second);
}
