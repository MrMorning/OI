#include <cstdio>
#include <algorithm>
#define MAXN 500001
#define MAXL 10000001
int tree[10000001];
int nPlant, nQuery, nPoint;
struct plant_t
{
	int x, y;
	bool operator< (const plant_t &t) const
	{return x < t.x || (x == t.x && y < t.y);}
} plant[MAXN];
struct
{
	int x1, y1, x2, y2, ans;
} query[MAXN];
struct point_t
{
	int x, y, qryIdx, flag;
	point_t(){};
	point_t(int _x, int _y, int _qryIdx, int _flag): x(_x), y(_y), qryIdx(_qryIdx), flag(_flag){};
	bool operator< (const point_t &t) const
	{return x < t.x || (x == t.x && y < t.y);}
} point[MAXN << 2];
inline int lowbit(int i)
{return i & (- i);}
int sum(int x)
{
	int cnt = 0;
	for(int i = x; i >= 1; i -= lowbit(i))
		cnt += tree[i];
	return cnt;
}
void add(int x, int val)
{
	for(int i = x; i < MAXL; i += lowbit(i))
		tree[i] += val;
}
int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%d%d", &nPlant, &nQuery);
	for(int i = 0, x, y; i < nPlant; i ++)
	{
		scanf("%d%d", &x, &y);
		plant[i].x = ++ x, plant[i].y = ++ y;
	}
	std::sort(plant, plant + nPlant);
	for(int i = 0, x1, y1, x2, y2; i < nQuery; i ++)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		query[i].x1 = ++ x1, query[i].x2 = ++ x2, query[i].y1 = ++ y1, query[i].y2 = ++ y2; 
		point[nPoint ++] = point_t(x1 - 1, y1 - 1, i, 1), point[nPoint ++] = point_t(x2, y2, i, 1);
		point[nPoint ++] = point_t(x1 - 1, y2, i, -1), point[nPoint ++] = point_t(x2, y1 - 1, i, -1);
	}
	std::sort(point, point + nPoint);
	int j = 0;
	for(int i = 0; i < nPoint; i ++)
	{
		point_t &p = point[i];
		if(p.x < plant[j].x || (p.x == plant[j].x && p.y < plant[j].y))
		{
			query[p.qryIdx].ans += p.flag * sum(p.y);
			continue;
		}
		while(j < nPlant && (p.x > plant[j].x || (p.x == plant[j].x && p.y >= plant[j].y)))
		{
			add(plant[j].y ,1);
			j ++;
		}
		query[p.qryIdx].ans += p.flag * sum(p.y);
	}
	for(int i = 0; i < nQuery; i ++)
		printf("%d\n", query[i].ans);
}
