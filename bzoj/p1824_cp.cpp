#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int N_MAX = 5010;
const int INFINITY = 0x3f3f3f3f;

struct Point
{
	int x, y;
	Point(int _x, int _y): x(_x), y(_y){}
};

int x[N_MAX], y[N_MAX];
vector<Point> point[2][2];
int n, mtx[2][N_MAX];

void read_data()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d%d", &x[i], &y[i]);
}

void discrete()
{
	static set<int> Sx, Sy;
	static map<int, int> Mx, My;
	static int x_idx = 0, y_idx = 0;

	for(int i = 0; i < n; i ++)
		Sx.insert(x[i]), Sy.insert(y[i]);
	for(set<int>::iterator it = Sx.begin(); it != Sx.end(); it ++)
		Mx[*it] = x_idx ++;
	for(set<int>::iterator it = Sy.begin(); it != Sy.end(); it ++)
		My[*it] = y_idx ++;
	for(int i = 0; i < n; i ++)
		x[i] = Mx[x[i]], y[i] = My[y[i]];
}

int count(int t, int s, int x)
{
	int ret = 0;
	int last = s ? -INFINITY : INFINITY;
	for(int i = x + 1; i < n; i ++)
		if(mtx[t][i] != -1)
		{
			if((mtx[t][i] < mtx[t][x]) ^ s)
				continue;
			if((mtx[t][i] < last) ^ s)
			{
				ret ++;
				last = mtx[t][i];
				point[t][s].push_back(Point(i, mtx[t][i]));
			}
		}
	return ret;
}

int clear(int t)
{
	if(! point[t][0].size())
		return 0;
	int qh = 0, qt = -1, ret = 0;
	int x_min = - INFINITY, y_min = - INFINITY;
	for(int i = 0, j = -1, k = -1; i < (int) point[t][0].size(); i ++)
	{
		Point &now = point[t][0][i];
		while(j + 1 < (int)point[t][1].size() && (point[t][1][j + 1].x < now.x))
			j ++, y_min = point[t][1][j].y;
		while(k + 1 < (int)point[!t][0].size() && (point[!t][0][k + 1].y < now.y))
			k ++, x_min = point[!t][0][k].x;
		while(qt + 1 < (int)point[!t][1].size() && point[!t][1][qt + 1].x > x_min)
			qt ++;
		while(qh <= qt && point[!t][1][qh].y < y_min)
			qh ++;
		assert(qt - qh + 1 >= 0);
		ret += qt - qh + 1;
	}
	return ret;
}

#define INV(x) (n - 1 - (x))
int score[2];
void solve()
{
	memset(mtx, -1, sizeof(mtx));
	int now_score = 0;
	for(int i = 0; i < n; i ++)
	{
		mtx[0][x[i]] = y[i];
		mtx[1][INV(x[i])] = y[i];
		for(int t = 0; t < 2; t ++)
			for(int s = 0; s < 2; s ++)
			{
				point[t][s].clear();
				now_score += count(t, s, t ? INV(x[i]) : x[i]);
			}
		for(int t = 0; t < 2; t ++)
			now_score -= clear(t);
		score[i & 1] += now_score;
	//	printf("*%d\n", now_score);
	}
	printf("%d %d\n", score[0], score[1]);
}

int main()
{
	freopen("t.in", "r", stdin);
	read_data();
	discrete();
	solve();
}
