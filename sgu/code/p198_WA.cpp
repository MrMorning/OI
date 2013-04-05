#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define SQR(x) ((x) * (x))
const double EPS = 10e-6;

struct Edge
{
	int to;
	Edge *next;
} edge[90000], *begin[300];

void addEdge(int u, int v)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u];
	begin[u] = e;
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
bool vis[300];
double dr;

inline Point operator-(const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

inline double cross(const Point &p1, const Point &p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

void dfs(int u)
{
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->to;
		if(vis[v])
		{
			printf("NO\n");
			exit(0);
		}
		dfs(v);
	}
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
				const Point &pi = c[i].p, &pj = c[j].p;
				if(cross(pj - pi, sp - pi) > 0)
					addEdge(i, j);
				else
					addEdge(j, i);
			}
		}
	for(int i = 0; i < nc; i ++)
	{
		memset(vis, 0, sizeof(vis));
		dfs(i);
	}
	printf("YES\n");
}
