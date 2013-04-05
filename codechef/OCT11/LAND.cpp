#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
//const double EPS = 1;
const int Q_MAX = 10000;
const int IN_Q_TIMES_MAX = 5000;
const double INIT_TEMP = 1;
const double FINAL_TEMP = 0.01;
const double FREEZE = 0.998;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
double a[100][100];
bool fixed[100][100];
int n, m;
pair<int, int> Q[Q_MAX];
bool inQ[100][100];
double curTemp;

int tmpCnt;
double tmp[4];
double f(double val)
{
	double res = 0;
	for(int i = 0; i < tmpCnt; i ++)
		res += pow(2, fabs(tmp[i] - val));
	return res;
}
double calc(int i, int j)
{
	tmpCnt = 0;
	for(int d = 0; d < 4; d ++)
	{
		int ni = i + dx[d],
			nj = j + dy[d];
		if(0 <= ni && ni < n)
			if(0 <= nj && nj < m)
				tmp[tmpCnt ++] = a[ni][nj];
	}
	double lb = 1, rb = 50;
	for(; rb - lb > curTemp; )
	{
		double lmid = lb + (rb - lb) / 3,
			   rmid = lb + (rb - lb) / 3 * 2;
		if(f(lmid) < f(rmid))
			rb = rmid;
		else
			lb = lmid;
	}
	return rb;
}

void solve()
{
	memset(fixed, 0, sizeof(fixed));
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
		{
			int t;
			scanf("%d", &t);
			a[i][j] = (double)t;
			fixed[i][j] = a[i][j] != 0;
		}

	int qh = 0, qt = 0;
	curTemp = INIT_TEMP;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			if(!fixed[i][j])
			{
				double tmp = calc(i, j);
				if(fabs(tmp - a[i][j]) > curTemp)
				{
					inQ[i][j] = true;
					Q[qt ++] = make_pair(i, j);
				}
				a[i][j] = tmp;
			}

	while(qh != qt && curTemp > FINAL_TEMP)
	{
		curTemp *= FREEZE;
		pair<int, int> u = Q[qh];
		inQ[u.first][u.second] = false;
		qh = (qh + 1) % Q_MAX;

		for(int d = 0; d < 4; d ++)
		{
			int ni = u.first + dx[d],
				nj = u.second + dy[d];
			if(0 <= ni && ni < n)
				if(0 <= nj && nj < m)
					if(!fixed[ni][nj])
					{
						double tmp = calc(ni, nj);
						if(fabs(tmp - a[ni][nj]) > curTemp)
						{
							if(!inQ[ni][nj])
							{
								Q[qt] = make_pair(ni, nj);
								qt = (qt + 1) % Q_MAX;
								inQ[ni][nj] = true;
							}
						}
						a[ni][nj] = tmp;
					}
		}
	}

	for(int i = 0; i < n; i ++, printf("\n"))
		for(int j = 0; j < m; j ++)
		{
			int t = (int)round(a[i][j]);
			if(t == 0)
				t = 1;
			if(t > 50)
				t = 50;
			printf("%d ", t);
		}
	printf("\n");
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
