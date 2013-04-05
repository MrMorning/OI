#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <algorithm>
#define SQR(x) ((x) * (x))
using namespace std;
const double EPS = 10e-6;
const double oo = 10e100;

struct Edge
{
	int to;
	bool marked;
	Edge *next, *inv;
} edge[90000], *begin[300];

inline Edge *addEdge(int u, int v)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->marked = false, e->to = v, e->next = begin[u];
	return begin[u] = e;
}

struct Point
{
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
} sp;
struct Circle
{
	Point p;
	double r;
} c[300];
int nc;
double dr;
int np, cycle[301];

inline Point operator-(const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

inline double cross(const Point &p1, const Point &p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

inline double getAgl(const Point &p1, const Point &p2)
{
	double l1 = sqrt(SQR(p1.x) + SQR(p1.y)),
		   l2 = sqrt(SQR(p2.x) + SQR(p2.y));
	return acos((p1.x * p2.x + p1.y * p2.y) / (l1 * l2));
}

inline bool intersect(const Point &p1, const Point &p2, const Point &q1, const Point &q2)
{
	return (cross(q1 - p1, p2 - p1) * cross(p2 - p1, q2 - p1) >= 0) 
		&& (cross(p1 - q1, q2 - q1) * cross(q2 - q1, p2 - q1) >= 0);
}

void dfs(int u, Edge *pe, int terminal)
{
	cycle[np ++] = u;
	if(u == terminal)
		return;
	Edge *best = NULL;
	double bestAgl;
	for(Edge *e = begin[u]; e; e = e->next)
		if(!e->marked && e->inv != pe)
		{
			int v = e->to;
			if(p == -1)
			{
				best = e;
				break;
			}
			const Point &p1 = c[p].p, &p2 = c[u].p, &p3 = c[v].p;
			int flag = (cross(p2 - p1, p3 - p2) > 0) ? -1 : 1;
			double agl = getAgl(p2 - p1, p3 - p2) * flag;
			if(best == NULL || agl < bestAgl)
				bestAgl = agl, best = e;
		}
	if(best == NULL)
		for(Edge *e = begin[u]; e; e = e->next)
			if(!e->marked && e->inv == pe)
			{
				best = e;
				break;
			}
	assert(best != NULL);
	best->marked = true;
	dfs(best->to, u, terminal);
}

bool inCycle()
{
	Point rp = Point(sp.x, oo);
	cycle[np] = cycle[0];
	int cnt = 0;
	for(int i = 0; i < np; i ++)
	{
		const Point &p1 = c[cycle[i]].p, &p2 = c[cycle[i + 1]].p;
		if(intersect(p1, p2, sp, rp))
			if(min(p1.x, p2.x) < sp.x && sp.x <= max(p1.x, p2.x))
				cnt ++;
	}
	return cnt & 1;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &nc);
	for(int i = 0; i < nc; i ++)
		scanf("%lf%lf%lf", &c[i].p.x, &c[i].p.y, &c[i].r);
	scanf("%lf%lf%lf", &sp.x, &sp.y, &dr);
	for(int i = 0; i < nc; i ++)
		c[i].r += dr;
	for(int i = 0; i < nc; i ++)
		for(int j = i + 1; j < nc; j ++)
		{
			double dist = sqrt(SQR(c[i].p.x - c[j].p.x) + SQR(c[i].p.y - c[j].p.y));
			if(fabs(dist - c[i].r - c[j].r) > EPS && dist < c[i].r + c[j].r)
			{
				Edge *e1 = addEdge(i, j),
					 *e2 = addEdge(j, i);
				e1->inv = e2, e2->inv = e1;
			}
		}
	for(int i = 0; i < nc; i ++)
		for(int t = 0; t < 2; t ++)
		{
			np = 0;
			for(Edge *e = begin[i]; e; e = e->next)
				if(!e->marked)
				{
					e->marked = true;
					dfs(e->to, -1, i);
					break;
				}

			if(inCycle())
			{
				printf("NO\n");
				return 0;
			}
		}
	printf("YES\n");
}
