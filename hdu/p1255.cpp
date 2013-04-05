#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
#define MAXN 2010
using namespace std;
const long double EPS = 1e-8;

struct Node
{
	int l, r, cover;
   	long double len1, len2;
} node[MAXN << 4];

struct Segment
{
	long double xl, xr, y;
    int	flag;
	bool operator< (const Segment &t)const
	{
		return y < t.y;
	}
} seg[MAXN * 2];

int n, idxNum;
long double idx[MAXN * 2];

void Build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	node[i].cover = node[i].len1 = node[i].len2 = 0;
	if(l + 1 == r) return;
	Build(i * 2, l, (l + r) / 2);
	Build(i * 2 + 1, (l + r) / 2, r);
}

void Update(int i)
{
	if(node[i].cover >= 2)
		node[i].len1 = node[i].len2 = idx[node[i].r] - idx[node[i].l];
	else if(node[i].cover == 1)
	{
		node[i].len1 = idx[node[i].r] - idx[node[i].l];
		node[i].len2 = node[i*2].len1 + node[i*2+1].len1;
	}
	else
	{
		node[i].len1 = node[i*2].len1 + node[i*2+1].len1;
		node[i].len2 = node[i*2].len2 + node[i*2+1].len2;
	}
}

void Change(int i, int a, int b, int val)
{
	if(node[i].r < a || node[i].l > b) return;
	if(a <= node[i].l && node[i].r <= b)
	{
		node[i].cover += val;
		Update(i);
		return;
	}
	Change(i * 2, a, b, val), Change(i * 2 + 1, a, b, val);
	Update(i);
}

int BinSearch(long double x)
{
	int l = 1, r = idxNum, mid = (l + r) / 2;
	while(l < r)
	{
		if(idx[mid] >= x)
			r = mid;
		else
			l = mid + 1;
		mid = (l + r) / 2;
	}
	return l;
}

int main()
{
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
	{
		memset(node, 0 ,sizeof(node));
		scanf("%d\n", &n);
		idxNum = 0;
		for(int i = 1; i <= n; i ++)
		{
			long double x1, y1, x2, y2;
			scanf("%Lf %Lf %Lf %Lf\n", &x1, &y1, &x2, &y2);
			seg[2 * i - 1].xl = x1, seg[2 * i - 1].xr = x2, seg[2 * i - 1].y = y1, seg[2 * i - 1].flag = 1;
			seg[2 * i].xl = x1, seg[2 * i].xr = x2, seg[2 * i].y = y2, seg[2 * i].flag = -1;
			idx[++ idxNum] = x1, idx[++ idxNum] = x2;
		}
		sort(idx + 1, idx + 1 + idxNum);
		sort(seg + 1, seg + 1 + 2 * n);
		int tmp = idxNum, idxNum = 0;
		for(int i = 1; i <= tmp; i ++)
			if(i > 0 && idx[i] == idx[i-1]) continue;
			else
				idx[++ idxNum] = idx[i];
		for(int i = 1; i <= 2 * n; i ++)
		{
			seg[i].xl = BinSearch(seg[i].xl);
			seg[i].xr = BinSearch(seg[i].xr);
		}
		Build(1, 1, idxNum);
		long double ans = 0;
		for(int i = 1; i <= 2 * n; i ++)
		{
			Change(1, seg[i].xl, seg[i].xr, seg[i].flag);
			long double tmp = node[1].len2 * (seg[i + 1].y - seg[i].y);
				ans += tmp;
		}
		cout << setiosflags(ios::fixed);
		cout << setprecision(2) << ans << '\n';
	}
}
