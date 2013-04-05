#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
const char LUCKPAL[10] = "luckykcul";
const int N_MAX = 1010;
const int oo = 0x3f3f3f3f;
char str[N_MAX];
int f[N_MAX][N_MAX][2], g[N_MAX][N_MAX][2];
char h[N_MAX][N_MAX][2];
char res[N_MAX];

void construct(int i, int j, int flag)
{
	if(i == 0)
		return;
	if(i == 1)
	{
		res[j] = str[j];
		return;
	}
	if(flag == 0)
	{
		res[j] = res[i + j - 1] = h[i][j][flag];
		construct(i - 2, j + 1, flag);
	}
	else
	{
		if(i == 9)
		{
			for(int t = 0; t < 9; t ++)
				res[j + t] = LUCKPAL[t];
			return;
		}
		if(g[i][j][1] == 0)
		{
			res[j] = res[i + j - 1] = h[i][j][flag];
			construct(i - 2, j + 1, flag);
			return;
		}
		for(int t = 0; t < 5; t ++)
			res[j + t] = res[j + i - 1 - t] = LUCKPAL[t];
		construct(i - 10, j + 5, 0);
	}
}

void backtrace(int i, int j, int flag, int now)
{
	if(now == 5)
		return;
	if(i == 0)
		assert(0);
	if(i == 1)
	{
		res[now] = str[j];
		return;
	}
	if(!flag)
	{
		res[now] = h[i][j][0];
		backtrace(i - 2, j + 1, 0, now + 1);
	}
	else
	{
		if(i != 9 && g[i][j][1] == 0)
		{
			res[now] = h[i][j][1];
			backtrace(i - 2, j + 1, 1, now + 1);
		}
		else
			for(int t = now; t < 5; t ++)
				res[t] = LUCKPAL[t - now];
	}
}

void solve()
{
	scanf("%s", str);
	int n = strlen(str);
	if(n < 9)
	{
		printf("unlucky\n");
		return;
	}
	for(int j = 0; j < n; j ++)
		f[1][j][0] = 0, f[1][j][1] = oo;
	for(int i = 2; i <= n; i ++)
		for(int j = 0; j + i - 1 < n; j ++)
		{
			f[i][j][0] = f[i - 2][j + 1][0] + (str[j] != str[j + i - 1]);
			h[i][j][0] = min(str[j], str[j + i - 1]);
			if(i < 9)
				f[i][j][1] = oo;
			else if(i == 9)
			{
				int cnt = 0;
				for(int k = 0; k < 9; k ++)
					cnt += str[k + j] != LUCKPAL[k];
				f[i][j][1] = cnt;
			}
			else
			{
				f[i][j][1] = oo;
				if(f[i - 2][j + 1][1] != oo)
				{
					f[i][j][1] = f[i - 2][j + 1][1] + (str[j] != str[j + i - 1]);
					h[i][j][1] = min(str[j], str[j + i - 1]);
					g[i][j][1] = 0;
				}
				int cnt = 0;
				for(int k = 0; k < 5; k ++)
				{
					cnt += str[j + k] != LUCKPAL[k];
					cnt += str[j + i - 1 - k] != LUCKPAL[k];
				}
				if(cnt + f[i - 10][j + 5][0] < f[i][j][1])
				{
					f[i][j][1] = cnt + f[i - 10][j + 5][0];
					g[i][j][1] = 1;
				}
				else if(cnt + f[i - 10][j + 5][0] == f[i][j][1])
				{
					backtrace(i, j, 1, 0);
					res[5] = 0;
					if(strcmp("lucky", res) < 0)
						g[i][j][1] = 1;
				}
			}
		}
	construct(n, 0, 1);
	res[n] = 0;
	int diff = 0;
	for(int i = 0; i < n; i ++)
	{
		assert(res[i] == res[n - i - 1]);
		diff += res[i] != str[i];
	}
	assert(diff == f[n][0][1]);
	printf("%s %d\n", res, f[n][0][1]);
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
