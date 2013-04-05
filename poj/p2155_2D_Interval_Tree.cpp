#include <cstdio>
#include <cstring>
#define MAXN 1000
#define ROOT 1, 1, n
#define NODE int i, int l, int r
#define LCHILD i << 1, l, (l + r) >> 1
#define RCHILD (i << 1) + 1, ((l + r) >> 1) + 1, r

int T[MAXN * 4][MAXN * 4];
int n, ans;

void Modify_y(int root_x, NODE, int y1, int y2)
{
	if(y2 < l || y1 > r) return;
	if(y1 <= l && r <= y2)
	{
		T[root_x][i] ^= 1;
		return;
	}
	Modify_y(root_x, LCHILD, y1, y2);
	Modify_y(root_x, RCHILD, y1, y2);
}

void Modify_x(NODE, int x1, int x2, int y1, int y2)
{
	if(x2 < l || x1 > r) return;
	if(x1 <= l && r <= x2)
	{
		Modify_y(i, ROOT, y1, y2);
		return;
	}
	Modify_x(LCHILD, x1, x2, y1, y2);
	Modify_x(RCHILD, x1, x2, y1, y2);
}

void Query_y(int root_x, NODE, int y)
{
	if(l > y || y > r) return;
	ans ^= T[root_x][i];
	if(l == y && r == y) return;
	Query_y(root_x, LCHILD, y);
	Query_y(root_x, RCHILD, y);

}

void Query_x(NODE, int x, int y)
{
	if(l > x || x > r) return;
	Query_y(i, ROOT, y);
	if(l == x && r == x) return;
	Query_x(LCHILD, x, y);
	Query_x(RCHILD, x, y);
}

void solve()
{
	memset(T, 0, sizeof(T));
	int query_num, x1, y1, x2, y2;
	scanf("%d %d", &n, &query_num);
	while(query_num --)
	{
		char ctrl;
		scanf("\n%c", &ctrl);
		if(ctrl == 'C')
		{
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			Modify_x(ROOT, x1, x2, y1, y2);
		}
		else
		{
			scanf("%d %d", &x1, &y1);
			ans = 0;
			Query_x(ROOT, x1, y1);
			printf("%d\n", ans);
		}
	}
	scanf("\n");
	printf("\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	int case_num;
	scanf("%d\n", &case_num);
	while(case_num --)
		solve();
}
