#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
const double INIT_TEMP = 1;
const double FINAL_TEMP = 0.001;
const double FREEZE = 0.98;
//const int ITERATION_TIMES = 1111;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
double a[100][100];
bool fixed[100][100];
int n, m;
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
	int cnt = 0;
	for(double temp = INIT_TEMP; temp > FINAL_TEMP; temp *= FREEZE)
	{
		cnt ++;
		if(cnt & 1)
		{
			for(int i = 0; i < n; i ++)
				for(int j = 0; j < m; j ++)
					if(!fixed[i][j])
					{
						double acc = 0, cnt = 0;
						for(int d = 0; d < 4; d ++)
						{
							int ni = i + dx[d],
								nj = j + dy[d];
							if(0 <= ni && ni < n)
								if(0 <= nj && nj < m)
									acc += a[ni][nj], cnt += 1;
						}
						a[i][j] = (acc + (double)rand() / RAND_MAX * temp) / (cnt);
					}
		}
		else
		{
			for(int i = n - 1; i >= 0; i --)
				for(int j = m - 1; j >= 0; j --)
					if(!fixed[i][j])
					{
						double acc = 0, cnt = 0;
						for(int d = 0; d < 4; d ++)
						{
							int ni = i + dx[d],
								nj = j + dy[d];
							if(0 <= ni && ni < n)
								if(0 <= nj && nj < m)
									acc += a[ni][nj], cnt += 1;
						}
						a[i][j] = (acc + a[i][j] + (double)rand() / RAND_MAX * temp) / (cnt + 1);
					}
		}
	}
	for(int i = 0; i < n; i ++, printf("\n"))
		for(int j = 0; j < m; j ++)
		{
			int t = (int)floor(a[i][j]);
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
