/*
Date: 11/01/12
Problem: ¸²¸ÇµÄÃæ»ý
*/
#include <cstdio>
#include <algorithm>

#define N 1100

struct Seg
{
	int l, r, lc, rc, cnt;
	double sum, asum;
};

struct Line
{
	int mark;
	double l, r, h;

	bool operator < (const Line& x) const
	{
		return h < x.h;
	}
};

Seg tree[N * 6];
Line dat[N * 2];
double p[N * 2];
int n, buildcnt;

void Build(int l, int r)
{
	tree[buildcnt].l = l, tree[buildcnt].r = r;
	tree[buildcnt].cnt = 0, tree[buildcnt].sum = 0, tree[buildcnt].asum = 0;

	if (l < r)
	{
		int mid = (l + r) >> 1, now = buildcnt;
		tree[now].lc = ++buildcnt, Build(l, mid);
		tree[now].rc = ++buildcnt, Build(mid + 1, r);
	}
}

void Update(int root)
{
	if (tree[root].cnt)
		tree[root].sum = p[tree[root].r + 1] - p[tree[root].l];
	else if (tree[root].l == tree[root].r)
		tree[root].sum = 0;
	else
		tree[root].sum = tree[tree[root].lc].sum + tree[tree[root].rc].sum;

	if (tree[root].cnt > 1)
		tree[root].asum = p[tree[root].r + 1] - p[tree[root].l];
	else if (tree[root].l == tree[root].r)
		tree[root].asum = 0;
	else if (tree[root].cnt)
		tree[root].asum = tree[tree[root].lc].sum + tree[tree[root].rc].sum;
	else
		tree[root].asum = tree[tree[root].lc].asum + tree[tree[root].rc].asum;
}

void Change(int l, int r, int mark, int root)
{
	if ((l <= tree[root].l) && (r >= tree[root].r))
	{
		tree[root].cnt += mark;
		Update(root);
		return;
	}

	int mid = (tree[root].l + tree[root].r) >> 1;
	if (l <= mid) Change(l, r, mark, tree[root].lc);
	if (r >  mid) Change(l, r, mark, tree[root].rc);
	Update(root);
}

int Search(double x, int r)
{
	int l = 0, mid;

	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (p[mid] == x) return mid;
		if (p[mid] > x)
			r = mid - 1;
		else
			l = mid + 1;
	}

	return -1;
}
int main()
{
	int t, k, m, ll, rr;
	double x1, y1, x2, y2, ans;
	scanf("%d", &t);

	for (int cas = 0; cas < t; cas++)
	{
		scanf("%d", &n);	
		k = 0, m = 0;

		for (int i = 0; i < n; i++)
		{
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			p[m] = x1, dat[m].l = x1, dat[m].r = x2, dat[m].h = y1, dat[m].mark =  1, ++m;
			p[m] = x2, dat[m].l = x1, dat[m].r = x2, dat[m].h = y2, dat[m].mark = -1, ++m;
		}

		std::sort(p, p + m), std::sort(dat, dat + m);
		for (int i = 0; i < m; i++)
			if ((!i) || (p[i] != p[i - 1])) p[k++] = p[i];

		buildcnt = 0, Build(0, k - 1), ans = 0;

		for (int i = 0; i < m - 1; i++)
		{
			ll = Search(dat[i].l, k - 1), rr = Search(dat[i].r, k - 1) - 1;
			if (ll > rr)
			{
				ans += tree[0].asum * (dat[i + 1].h - dat[i].h);
				continue;
			}
			Change(ll, rr, dat[i].mark, 0);
			ans += tree[0].asum * (dat[i + 1].h - dat[i].h);
		}

		printf("%0.2lf\n", ans);
	}

	return 0;
}
