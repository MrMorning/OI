#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAXN 20000
#define MAXY 160000

using std::vector;
using std::sort;

struct Segment
{
	int y1, y2, x;
	vector<int> vec;
	bool operator< (const Segment &a)const
	{
		return x < a.x;
	}
} seg[MAXN];
int tree[MAXY * 4];
bool hash[MAXN];
int now, n;

void Push_Down(int i)
{
	if(tree[i])
	{
		tree[i * 2] = tree[i * 2 + 1] = tree[i];
		tree[i] = 0;
	}
}

void Query(int i, int l, int r, int a, int b)
{
	if(l > b || a > r) return;
	if(a <= l && r <= b)
	{
		if(tree[i] != 0)
		{
			if(!hash[tree[i]])
				seg[now].vec.push_back(tree[i]), hash[tree[i]] = true;
			Push_Down(i);
			return;
		}
	}
	if(l == r) return;
	Push_Down(i);
	Query(i * 2, l, (l + r) / 2, a, b);
	Query(i * 2 + 1, (l + r) / 2 + 1, r, a, b);
}

void Change(int i, int l, int r, int a, int b, int color)
{
	if(l > b || a > r) return;
	if(a <= l && r <= b)
	{
		tree[i] = color;
		return;
	}
	if(l == r) return;
	Push_Down(i);
	Change(i * 2, l, (l + r) / 2, a, b, color);
	Change(i * 2 + 1, (l + r) / 2 + 1, r, a, b, color);
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
	{
		scanf("%d\n", &n);
		for(int i = 1; i <= n; i ++)
		{
			scanf("%d %d %d\n", &seg[i].y1, &seg[i].y2, &seg[i].x);
			seg[i].y1 ++, seg[i].y2 ++;
			seg[i].y1 <<= 1, seg[i].y2 <<= 1;
			seg[i].vec.clear();
		}
		sort(seg + 1, seg + n + 1);
		memset(tree, 0, sizeof(tree));
		for(int i = 1; i <= n; i ++)
		{
			now = i, memset(hash, 0, sizeof(hash));
			Query(1, 1, MAXY, seg[i].y1, seg[i].y2);
			Change(1, 1, MAXY, seg[i].y1, seg[i].y2, i);
		}
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 0; j < seg[i].vec.size(); j ++)
			{
				int k = seg[i].vec[j];
				for(int l = 0; l < seg[k].vec.size(); l ++)
					for(int m = 0; m < seg[i].vec.size(); m ++)
						if(seg[k].vec[l] == seg[i].vec[m])
							ans ++;
			}
		printf("%d\n", ans);
			
	}
}
