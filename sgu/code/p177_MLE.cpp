#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 1100;

struct Color
{
	int time, val;
	bool operator< (const Color &t) const
	{
		return time < t.time;
	}
};

struct Node2
{
	int l, r;
	Color color;
};

struct Node
{
	int l, r;
	Node2 node[N_MAX * 3];
	void build(int i, int l, int r)
	{
		node[i].l = l, node[i].r = r;
		if(l != r)
		{
			int mid = (l + r) / 2;
			build(i * 2, l, mid);
			build(i * 2 + 1, mid + 1, r);
		}
	}
	void paint(int i, int l, int r, Color color)
	{
		if(node[i].l > r || node[i].r < l)
			return;
		if(l <= node[i].l && node[i].r <= r)
		{
			node[i].color = color;
			return;
		}
		paint(i * 2, l, r, color);
		paint(i * 2 + 1, l, r, color);
	}

	Color ask(int pos)
	{
		int now = 1;
		Color res;
		res.time = -1;
		while(1)
		{
			if(res < node[now].color)
				res = node[now].color;
			if(node[now].l == node[now].r)
				break;
			int mid = (node[now].l + node[now].r) / 2;
			if(pos <= mid)
				now = now * 2;
			else
				now = now * 2 + 1;
		}
		return res;
	}
} node[N_MAX * 3];

void build(int i, int x1, int x2, int y1, int y2)
{
	node[i].l = x1, node[i].r = x2;
	node[i].build(1, y1, y2);
	if(x1 < x2)
	{
		int mid = (x1 + x2) / 2;
		build(i * 2, x1, mid, y1, y2);
		build(i * 2 + 1, mid + 1, x2, y1, y2);
	}
}

void paint(int i, int x1, int x2, int y1, int y2, Color color)
{
	if(node[i].l > x2 || node[i].r < x1)
		return;
	if(x1 <= node[i].l && node[i].r <= x2)
	{
		node[i].paint(1, y1, y2, color);
		return;
	}
	paint(i * 2, x1, x2, y1, y2, color);
	paint(i * 2 + 1, x1, x2, y1, y2, color);
}

Color ask(int x, int y)
{
	int now = 1;
	Color res;
	res.time = -1;
	while(1)
	{
		Color tmp = node[now].ask(y);
		if(res < tmp)
			res = tmp;
		if(node[now].l == node[now].r)
			break;
		int mid = (node[now].l + node[now].r) / 2;
		if(x <= mid)
			now = now * 2;
		else
			now = now * 2 + 1;
	}
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	build(1, 1, n, 1, n);
	for(int i = 0, x1, y1, x2, y2; i < m; i ++)
	{
		static char str[5];
		scanf("%d%d%d%d%s", &x1, &y1, &x2, &y2, str);
		Color c;
		c.val = str[0] == 'b', c.time = i + 1;
		paint(1, min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2), c);
	}
	int res = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			res += ask(i, j).val == 0;
	printf("%d\n", res);
}
