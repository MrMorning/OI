#include <cstdio>
#include <cmath>
#include <algorithm>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

const int N_PNT_MAX = 2000;
struct Point
{
	double x, y, plr_agl;
	Point(){};
	Point(double _x, double _y): x(_x), y(_y){};
	bool operator< (const Point &another) const
	{
		return x < another.x || (x == another.x && y < another.y);
	}
};

Point pnt[N_PNT_MAX];
int cnvx[N_PNT_MAX];
int n_pnt, n_cnvx_pnt;

Point operator- (const Point &a, const Point &b)
{
	return Point(a.x - b.x, a.y - b.y);
}

double operator* (const Point &a, const Point &b)
{
	return a.x * b.y - b.x * a.y;
}

inline double dist(Point &a, Point &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline bool cmp_on_plr_agl(const Point &a, const Point &b)
{
	return a.plr_agl < b.plr_agl || (a.plr_agl == b.plr_agl && a < b); 
}
void calc_cnvx()
{
	//get the leftest pnt, 
	//garantee p[0], p[1] and p[n - 1] is in cnvx
	Point &pnt_std = pnt[0];
	for(int i = 1; i < n_pnt; i ++)
		if(pnt[i] < pnt_std)
			pnt_std = pnt[i];
	std::swap(pnt_std, pnt[0]);

	//calc plr angle based on pnt_std
	pnt[0].plr_agl = -10E100;
	for(int i = 1; i < n_pnt; i ++)
		pnt[i].plr_agl = atan2(pnt[i].y - pnt[0].y, pnt[i].x - pnt[0].x);
	std::sort(pnt, pnt + n_pnt, cmp_on_plr_agl);

	//do Graham Scanning
	int top = 0;

	cnvx[top ++] = 0, cnvx[top ++] = 1, cnvx[top ++] = 2;
	for(int i = 3; i < n_pnt; i ++)
	{
		Point &p_now = pnt[i];
		while(1)
		{
			Point &p1 = pnt[cnvx[top - 2]],
				  &p2 = pnt[cnvx[top - 1]];
			if((p2 - p1) * (p_now - p1) > 0)
				break;
			top --;
		}
		cnvx[top ++] = i;
	}
	n_cnvx_pnt = top;
}
#define NEXT(i, k) (((i) + (k)) % n_cnvx_pnt)
int main()
{
	freopen("land.in", "r", stdin);
	freopen("land.out", "w", stdout);
	scanf("%d", &n_pnt);
	for(int i = 0; i < n_pnt; i ++)
		scanf("%lf%lf", &pnt[i].x, &pnt[i].y);
	std::sort(pnt, pnt + n_pnt);
	calc_cnvx();
	
	double ans = 0;
	for(int i = 0; i < n_cnvx_pnt; i ++)
	{
		int j = NEXT(i, 1);
		Point &p_i = pnt[cnvx[i]];
		while(1)
		{
			if(dist(pnt[cnvx[NEXT(j, 1)]], p_i) < dist(pnt[cnvx[j]], p_i))
				break;
			j = NEXT(j, 1);
		}
		Point &p_j = pnt[cnvx[j]];

		double area_max[2];
		area_max[0] = area_max[1] = 0;
		for(int k = NEXT(i, 1); k != j; k = NEXT(k, 1))
		{
			Point &p_k = pnt[cnvx[k]];
			double area_now = fabs((p_i - p_k) * (p_j - p_k)) / 2;
			area_max[0] = MAX(area_max[0], area_now);
		}
		for(int k = NEXT(j, 1); k != i; k = NEXT(k, 1))
		{
			Point &p_k = pnt[cnvx[k]];
			double area_now = fabs((p_i - p_k) * (p_j - p_k)) / 2;
			area_max[1] = MAX(area_max[1], area_now);
		}
		ans = MAX(ans, area_max[0] + area_max[1]);
	}
	printf("%.3lf\n", ans);
}
