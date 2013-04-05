#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 1200;

struct Color
{
	short time;
	bool val;
	bool operator< (const Color &t) const
	{
		return time < t.time;
	}
};

struct Node2
{
	Node2 *ch[2];
	short l, r;
	Color color;
};
int n, m;

Node2 *alloc2(int l, int r)
{
	static Node2 node[3 * N_MAX * N_MAX - 200000];
	static int freePos = 0;
	Node2 *x = &node[freePos ++];
	x->l = l, x->r = r;
	return x;
}

struct Node
{
	Node *ch[2];
	short l, r;
	Node2 *root;
	inline Node2 *deepin(Node2 *x, int c)
	{
		if(x->ch[c] == NULL)
		{
			if(c == 0)
				x->ch[c] = alloc2(x->l, (x->l + x->r) / 2);
			else
				x->ch[c] = alloc2((x->l + x->r) / 2 + 1, x->r);
		}
		return x->ch[c];
	}
	void paint(Node2 *x, int l, int r, Color color)
	{
		if(x->l > r || x->r < l)
			return;
		if(l <= x->l && x->r <= r)
		{
			x->color = color;
			return;
		}
		int mid = (x->l + x->r) / 2;
		if(l <= mid)
			paint(deepin(x, 0), l, r, color);
		if(r > mid)
			paint(deepin(x, 1), l, r, color);
	}

	Color ask(int pos)
	{
		Node2 *x = root;
		Color res;
		res.time = -1;
		while(1)
		{
			if(res < x->color)
				res = x->color;
			if(x->l == x->r)
				break;
			int mid = (x->l + x->r) / 2;
			if(pos <= mid)
				x = deepin(x, 0);
			else
				x = deepin(x, 1);
		}
		return res;
	}
} *root;

Node *alloc(int l, int r)
{
	static Node node[3 * N_MAX];
	static int freePos = 0;
	Node *x = &node[freePos ++];
	x->l = l, x->r = r;
	x->root = alloc2(1, n);
	return x;
}

inline Node *deepin(Node *x, int c)
{
	if(x->ch[c] == NULL)
	{
		if(c == 0)
			x->ch[c] = alloc(x->l, (x->l + x->r) / 2);
		else
			x->ch[c] = alloc((x->l + x->r) / 2 + 1, x->r);
	}
	return x->ch[c];
}

void paint(Node *x, int x1, int x2, int y1, int y2, Color color)
{
	if(x->l > x2 || x->r < x1)
		return;
	if(x1 <= x->l && x->r <= x2)
	{
		x->paint(x->root, y1, y2, color);
		return;
	}
	paint(deepin(x, 0), x1, x2, y1, y2, color);
	paint(deepin(x, 1), x1, x2, y1, y2, color);
}

Color ask(int x, int y)
{
	Node *now = root;
	Color res;
	res.time = -1;
	while(1)
	{
		Color tmp = now->ask(y);
		if(res < tmp)
			res = tmp;
		if(now->l == now->r)
			break;
		int mid = (now->l + now->r) / 2;
		if(x <= mid)
			now = deepin(now, 0);
		else
			now = deepin(now, 1);
	}
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	root = alloc(1, n);
	for(int i = 0, x1, y1, x2, y2; i < m; i ++)
	{
		static char str[5];
		scanf("%d%d%d%d%s", &x1, &y1, &x2, &y2, str);
		Color c;
		c.val = str[0] == 'b', c.time = i + 1;
		paint(root, min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2), c);
	}
	int res = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			res += ask(i, j).val == 0;
	printf("%d\n", res);
}
