#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#define MAXN 800

using std::map;
using std::set;

const double EPS = 1e-12;

struct Segment
{
	double x1, x2, y;
} seg_in[MAXN], seg_out[MAXN];

struct Node
{
	double len;
	int cover;
} tree[2 * MAXN];

set<double> set_x, set_y;
double x[2 * MAXN], y[2 * MAXN];
map<double, int> map_x;
int n, testNum;

int comp(const void *a, const void *b)
{
	if(((Segment*)a)->y - ((Segment*)b)->y > 0)
		return 1;
	else
		return -1;
}

void change(int i, int l, int r, int a, int b, int val)
{
	if(a <= l && r <= b)
	{
		tree[i].cover += val;
		if(tree[i].cover)
			tree[i].len = x[r] - x[l];
		else if(r > l)
			tree[i].len = tree[i * 2].len + tree[i * 2 + 1].len;
		else tree[i].len = 0;
		return;
	}
	if(l > b || r < a) return;
	int mid = (l + r) / 2;
	if(l + 1 < r)
	{
		change(2 * i, l, mid, a, b, val);
		change(2 * i + 1, mid, r, a, b, val);//caution! [a, b] = [a, mid] U [mid, b]
	}
	if(tree[i].cover)
		tree[i].len = x[r] - x[l];
	else
		tree[i].len = tree[i * 2].len + tree[i * 2 + 1].len;
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		scanf("%d\n", &n);
		if(! n) 
			break;
		set_x.clear(), set_y.clear();
		for(int i = 1; i <= n; i ++)
		{
			double x1, y1, x2, y2;
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			set_x.insert(x1), set_x.insert(x2);
			set_y.insert(y1), set_y.insert(y2);
			seg_in[i].x1 = x1, seg_in[i].x2 = x2, seg_in[i].y = y1;
			seg_out[i].x1 = x1, seg_out[i].x2 = x2, seg_out[i].y = y2;
		}
		int nx = 0, ny = 0;
		for(set<double>::iterator it = set_x.begin(); it != set_x.end(); ++ it)
			x[++ nx] = *it;
		for(set<double>::iterator it = set_y.begin(); it != set_y.end(); ++ it)
			y[++ ny] = *it;
		qsort(seg_in + 1, n, sizeof(Segment), comp);
		qsort(seg_out + 1, n, sizeof(Segment), comp);
		map_x.clear();
		for(int i = 1; i <= nx; i ++)
			map_x[x[i]] = i;
		double ans = 0;
		memset(tree, 0, sizeof(tree));
		for(int i = 1, in_p = 1, out_p = 1; i < ny; i ++)
		{
			while(seg_in[in_p].y == y[i] && in_p <= n)
				change(1, 1, nx, map_x[seg_in[in_p].x1], map_x[seg_in[in_p].x2], 1), in_p ++;
			while(seg_out[out_p].y == y[i] && out_p <= n)
				change(1, 1, nx, map_x[seg_out[out_p].x1], map_x[seg_out[out_p].x2], -1), out_p ++;
			ans += tree[1].len * (y[i + 1] - y[i]);
		}
		printf("Test case #%d\n", ++ testNum);
		printf("Total explored area: %.2lf\n\n", ans + EPS);
	}
}
