#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>
#define FOR(i, l, r) for(int i = (l); i < (r); i ++)
#define REP(i, n) for(int i = 0; i < (n); i ++)
#define ALL(x) (x).begin(), (x).end()
#define EQUAL(x, y) (fabs((x) - (y)) < EPS)
#define pb(t) push_back(t)
#define SQR(x) ((x) * (x))

const double EPS = 10e-8;
const int L_MAX = 80;
const int V_MAX = L_MAX * L_MAX;
const int E_MAX = 2000000;

using namespace std;

struct Point
{
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
	bool operator< (const Point &t) const
	{
		return x < t.x || (EQUAL(x, t.x) && y < t.y);
	}
	bool operator== (const Point &t) const
	{
		return EQUAL(x, t.x) && EQUAL(y, t.y);
	}
};

Point operator- (const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

double cross(const Point &p1, const Point &p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

struct Line
{
	double a, b, c;
	Line(double x1, double y1, double x2, double y2)
	{
		a = y1 - y2;
		b = x2 - x1;
		c = -(a * x1 + b * y1);
	}
};

struct Edge
{
	int to;
	bool marked;
	Edge *next;
} edge[E_MAX], *begin[V_MAX];

vector<Point> point;
vector<Line> line;
vector<int> cycle;
vector<double> area;

void addEdge(int u, int v)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->marked = false;
	e->to = v, e->next = begin[u]; begin[u] = e;
}

bool isIntersected(const Line &l1, const Line &l2)
{
	if(l1.a == 0 || l2.a == 0)
		return (l1.a != 0 || l2.a != 0);
	else return !EQUAL(l1.b / l1.a, l2.b / l2.a);
}

inline Point getIntersection(Line l1, Line l2)
{
	if(EQUAL(l1.a, 0))
		swap(l1, l2);

	double k = l2.a / l1.a;
	double y = -(l2.c - k * l1.c) / (l2.b - k * l1.b);
	return Point((-l1.c - l1.b * y) / l1.a, y);
}

inline double getAgl(const Point &p1, const Point &p2)
{
	double l1 = sqrt(SQR(p1.x) + SQR(p1.y)),
		   l2 = sqrt(SQR(p2.x) + SQR(p2.y));
	return acos((p1.x * p2.x + p1.y * p2.y) / (l1 * l2));
}

void readData()
{
	int nl;
	scanf("%d", &nl);
	REP(i, nl)
	{
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		line.pb(Line(x1, y1, x2, y2));
	}
}

void createIntersections()
{
	REP(i, line.size())
		FOR(j, i + 1, line.size())
		if(isIntersected(line[i], line[j]))
			point.push_back(getIntersection(line[i], line[j]));
	sort(ALL(point));
	vector<Point>::iterator it = unique(ALL(point));
	point.resize(it - point.begin());
}

int bsearch(const Point &p)
{
	int lb = 0, rb = point.size();
	for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) / 2)
		if(point[mid] < p || point[mid] == p)
			lb = mid;
		else
			rb = mid;
	return lb;
}

bool cmp_idx(int a, int b)
{
	return point[a] < point[b];
}

void createEdges()
{
	static vector<int> vp[L_MAX];
	REP(i, line.size())
		FOR(j, i + 1, line.size())
		if(isIntersected(line[i], line[j]))
		{
			Point p = getIntersection(line[i], line[j]);
			int idx = bsearch(p);
			vp[i].pb(idx);
			vp[j].pb(idx);
		}
	REP(i, line.size())
	{
		sort(ALL(vp[i]), cmp_idx);
		vector<int>::iterator it = unique(ALL(vp[i]));
		vp[i].resize(it - vp[i].begin());

		REP(k, (int)vp[i].size() - 1)
		{
			addEdge(vp[i][k], vp[i][k + 1]);
			addEdge(vp[i][k + 1], vp[i][k]);
		}
	}
}

void dfs(int u, int p, int terminal)
{
	cycle.pb(u);
	if(u == terminal)
		return;
	Edge *best;
	double bestAgl = 10e100;
	for(Edge *e = begin[u]; e; e = e->next)
		if(!e->marked)
		{
			int v = e->to;
			const Point &p1 = point[p], &p2 = point[u], &p3 = point[v];
			int flag = (cross(p2 - p1, p3 - p2) > 0) ? -1 : 1;
			if(fabs(cross(p2 - p1, p3 - p2)) < EPS)
				flag = 1;
			double agl = getAgl(p2 - p1, p3 - p2) * flag;
			if(best == NULL || agl < bestAgl)
				bestAgl = agl, best = e;
		}
	assert(best != NULL);
	best->marked = true;
	dfs(best->to, u, terminal);
}

double calcArea()
{
	double res = 0;
	REP(i, cycle.size())
		res += cross(point[cycle[i]], point[cycle[(i + 1) % cycle.size()]]) / 2;
	return fabs(res);
}

void statArea()
{
	REP(i, point.size())
	{
		while(1)
		{
			bool flag = false;
			for(Edge *e = begin[i]; e; e = e->next)
				if(!e->marked)
				{
					flag = true;
					e->marked = true;
					cycle.clear();
					cycle.pb(i);
					dfs(e->to, i, i);
					break;
				}
			if(!flag)
				break;

			area.pb(calcArea());
		}
	}
}

void output()
{
	sort(ALL(area));
	int cnt = 0;
	REP(i, area.size())
		if(EQUAL(area[i], 0))
			cnt ++;
	if(area.size() == 0)
	{
		printf("0\n");
		return;
	}
	printf("%d\n", (int)area.size() - cnt - 1);
	FOR(i, cnt, (int)area.size() - 1)
		printf("%.4lf\n", area[i]);
}

int main()
{
	freopen("t.in", "r", stdin);
	readData();
	createIntersections();
	createEdges();
	statArea();
	output();
}
