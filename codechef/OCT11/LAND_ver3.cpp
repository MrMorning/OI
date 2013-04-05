#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
const double EPS = 1.4;
const int ITERATION_TIMES = 3;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
double a[100][100];
bool fixed[100][100];
int n, m;

int tmpCnt;
double tmp[4];
double f(double val)
{
	double res = 0;
	for(int i = 0; i < tmpCnt; i ++)
		res += pow(2, fabs(tmp[i] - val));
	return res;
}
double calc()
{
	/*double lb = 1, rb = 50;
	for(; rb - lb > EPS; )
	{
		double lmid = lb + (rb - lb) / 3,
			   rmid = lb + (rb - lb) / 3 * 2;
		if(f(lmid) < f(rmid))
			rb = rmid;
		else
			lb = lmid;
	}
	return rb;*/
	double minVal = 10e100;
	double best = -1;
	for(double k = 1; k <= 50; k += 1)
	{
		double tmp = f(k);
		if(tmp < minVal)
			minVal = tmp, best = k;
	}
	return best;
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
	for(int repTimes = 0; repTimes < ITERATION_TIMES; repTimes ++)
	{
		double changeVal = 0;
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < m; j ++)
				if(!fixed[i][j])
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
					double tmp = calc();
					changeVal += fabs(tmp - a[i][j]);
					a[i][j] = tmp;
				}
		if(changeVal < 1)
			break;
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
