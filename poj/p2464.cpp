#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>

#define MAXN 201000
#define MAX_VAL 201000

using std::map;

struct Point
{
	int x, y, left, right, up, down;
	int left_same, right_same, up_same, down_same;
} p[MAXN];
int n, tree[MAXN];

int comp_int(const void *a, const void *b)
{return *(int*)a - *(int*)b;}

int comp_x(const void *a, const void *b)
{
	Point &pa = *(Point*)a;
	Point &pb = *(Point*)b;
	if(pa.x > pb.x || (pa.x == pb.x && pa.y > pb.y))
		return 1;
	else
		return -1;
}

int comp_y(const void *a, const void *b)
{
	Point &pa = *(Point*)a;
	Point &pb = *(Point*)b;
	if(pa.y > pb.y || (pa.y == pb.y && pa.x > pb.x))
		return 1;
	else
		return -1;
}

void init()
{
	//for(int i = 1; i <= n; i ++)
	//	p[i].x = p[i].y = p[i].left = p[i].right = p[i].up = p[i].down = 0;
	memset(p, 0, sizeof(p));
	for(int i = 1; i <= n; i ++)
		scanf("%d %d\n", &p[i].x, &p[i].y);
	qsort(p + 1, n, sizeof(Point), comp_y);
	map<int, int> map_y;
	int idx = 0, cnt[MAX_VAL];
	memset(cnt, 0, sizeof(cnt));
	for(int i = 1; i <= n; i ++)
	{
		if(map_y.find(p[i].y) == map_y.end())
			map_y[p[i].y] = ++ idx;
		p[i].y = map_y[p[i].y];
		cnt[p[i].y] ++;
	}
	for(int i = 1; i <= n; i ++)
		if(p[i].y == p[i - 1].y)
			p[i].down = p[i - 1].down, p[i].left_same = p[i - 1].left_same + 1;
		else
			p[i].down = p[i - 1].down + cnt[p[i - 1].y];
	for(int i = n; i >= 1; i --)
		if(p[i].y == p[i + 1].y)
			p[i].up = p[i + 1].up, p[i].right_same = p[i + 1].right_same + 1;
		else
			p[i].up = p[i + 1].up + cnt[p[i + 1].y];
	qsort(p + 1, n, sizeof(Point), comp_x);
	map<int, int> map_x;
	idx = 0;
	memset(cnt, 0, sizeof(cnt));
	for(int i = 1; i <= n; i ++)
	{
		if(map_x.find(p[i].x) == map_x.end())
			map_x[p[i].x] = ++ idx;
		p[i].x = map_x[p[i].x];
		cnt[p[i].x] ++;
	}
	for(int i = 1; i <= n; i ++)
		if(p[i].x == p[i - 1].x)
			p[i].left = p[i - 1].left, p[i].down_same = p[i - 1].down_same + 1;
		else
			p[i].left = p[i - 1].left + cnt[p[i - 1].x];
	for(int i = n; i >= 1; i --)
		if(p[i].x == p[i + 1].x)
			p[i].right = p[i + 1].right, p[i].up_same = p[i + 1].up_same + 1;
		else
			p[i].right = p[i + 1].right + cnt[p[i + 1].x];
}

inline int lowbit(int i)
{return i & (- i);}

void Add(int i, int val)
{
	while(i <= MAX_VAL)
	{
		tree[i] += val;
		i += lowbit(i);
	}
}

int Sum(int i)
{
	int cnt = 0;
	while(i > 0)
	{
		cnt += tree[i];
		i -= lowbit(i);
	}
	return cnt;
}

void solve()
{
	init();
	memset(tree, 0, sizeof(tree));
	int Stan_Score, Stan_MaxScore = -1, Stan_MinScore;
	int Ollie_Score, Ollie_MaxCnt, Ollie_MaxScore[MAXN], Ollie_MinCnt, Ollie_MinScore[MAXN];
	for(int i = 1; i <= n; i ++)
	{
		int j = i;
		while(p[j].x == p[j + 1].x) j ++;
		Stan_MinScore = MAX_VAL;
		for(int k = i; k <= j; k ++)
		{
			Add(p[k].y, 1);
			int count = Sum(p[k].y) - p[k].left_same - p[k].down_same - 1;
			Stan_Score = count + p[k].up - (p[k].left - count - p[k].left_same) - p[k].up_same;
			Ollie_Score = p[k].left - count - p[k].left_same + p[k].down - p[k].down_same - count;
			if(Stan_Score < Stan_MinScore)
			{
				Stan_MinScore = Stan_Score;
				Ollie_MinCnt = 1;
				Ollie_MinScore[1] = Ollie_Score;
			}
			else if(Stan_Score == Stan_MinScore)
				Ollie_MinScore[++ Ollie_MinCnt] = Ollie_Score;
		}
		if(Stan_MinScore > Stan_MaxScore)
		{
			Stan_MaxScore = Stan_MinScore;
			Ollie_MaxCnt = Ollie_MinCnt;
			for(int k = 1; k <= Ollie_MinCnt; k ++)
				Ollie_MaxScore[k] = Ollie_MinScore[k];
		}
		else if(Stan_MinScore == Stan_MaxScore)
		{
			for(int k = 1; k <= Ollie_MinCnt; k ++)
				Ollie_MaxScore[Ollie_MaxCnt + k] = Ollie_MinScore[k];
			Ollie_MaxCnt += Ollie_MinCnt;
		}
		i = j;
	}
	qsort(Ollie_MaxScore + 1, Ollie_MaxCnt, sizeof(int), comp_int);
	printf("Stan: %d; Ollie:", Stan_MaxScore);
	for(int i = 1; i <= Ollie_MaxCnt; i ++)
		if(i == 1 || Ollie_MaxScore[i] != Ollie_MaxScore[i - 1])
			printf(" %d", Ollie_MaxScore[i]);
	printf(";\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		scanf("%d\n", &n);
		if(n == 0) break;
		solve();
	}
}
