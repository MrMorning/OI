#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#define MAXN 100000

using namespace std;

struct Node
{
	unsigned int l, r;
   	int	maxl, sum;
} node[MAXN << 3];

struct Point
{
	unsigned x, y;
   	int	c;
	bool operator< (const Point &t)const
	{
		return x < t.x;
	}
} p[2][MAXN];

unsigned int Y[MAXN];
int n, nY;
unsigned int H, W;
set<unsigned int> set_y;
map<unsigned int, unsigned int> map_y;

void Build(int i, unsigned int l, unsigned int r)
{
	node[i].l = l, node[i].r = r;
	node[i].maxl = node[i].sum = 0;
	if(l == r)
		return;
	Build(i * 2, l, (l + r) / 2);
	Build(i * 2 + 1, (l + r) / 2 + 1, r);
}

void Update(int i)
{
	node[i].sum = node[i * 2].sum + node[i * 2 + 1].sum;
	node[i].maxl = max(node[i * 2].maxl, node[i * 2].sum + node[i * 2 + 1].maxl);
}

void Change(int i, unsigned int y, int val)
{
	if(y > node[i].r || node[i].l > y) return;
	if(node[i].l == y && y == node[i].r)
	{
		node[i].sum += val, node[i].maxl += val;
		return;
	}
	Change(i * 2, y, val);
	Change(i * 2 + 1, y, val);
	Update(i);
}


int main()
{
	freopen("t.in", "r", stdin);
	while(! feof(stdin))
	{
		scanf("%d %u %u\n", &n, &W, &H);
		for(int i = 1, a, b, c; i <= n; i ++)
		{
			scanf("%u %u %d\n", &a, &b, &c);
			p[0][i].x = a, p[0][i].y = b, p[0][i].c = c;
		}
		sort(p[0] + 1, p[0] + n + 1);
		for(int i = 1; i <= n; i ++)
			p[1][i].x = p[0][i].x + W, p[1][i].y = p[0][i].y + H, p[1][i].c = - p[0][i].c;
		set_y.clear();
		for(int i = 1; i <= n; i ++)
			set_y.insert(p[0][i].y), set_y.insert(p[1][i].y);
		nY = 0;
		map_y.clear();
		for(set<unsigned int>::iterator it = set_y.begin(); it != set_y.end(); ++ it)
		{
			Y[++ nY] = *it;
			map_y[*it] = nY;
		}
		for(int i = 1; i <= n; i ++)
		{
			if(p[0][i].x == p[0][i-1].x && p[0][i].y == p[0][i-1].y)
				printf("WA!");
			p[0][i].y = map_y[p[0][i].y];
			p[1][i].y = map_y[p[1][i].y];
		}
		int l1 = 1, l2 = 0;
		int ans = 0;
		Build(1, 1, MAXN);
		while(l2 <= n && l1 <= n)
		{
			while(p[0][l2 + 1].x - p[0][l1].x + 1 <= W && l2 < n) 
			{
				l2 ++;
				Change(1, p[0][l2].y, p[0][l2].c);
				Change(1, p[1][l2].y, p[1][l2].c);
			}
			if(node[1].maxl > ans)
				ans = node[1].maxl;
			Change(1, p[0][l1].y, -p[0][l1].c);
			Change(1, p[1][l1].y, -p[1][l1].c);
			l1 ++;
		}
		printf("%d\n", ans);
	}
}
