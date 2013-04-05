#include <cstdio>
#include <cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

namespace Solve
{
	const int MAXN = 210;
	const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
	const int INFINITY = 0x3f3f3f3f;
	struct State
	{
		int idx, val;
		State(){};
		State(int _idx, int _val): idx(_idx), val(_val){};	
	};
	struct Interval
	{
		int s, t, d;
	} interv[MAXN];
	int n, m, nInterv;
	int f[MAXN][MAXN][MAXN];
	char obs[MAXN][MAXN];
	void solve();
	void calc(int, int, int, int, int);
	void workMono();
}

void Solve::solve()
{
	memset(f, -0x3f, sizeof(f));
	int sx, sy;
	scanf("%d %d %d %d %d\n", &n, &m, &sx, &sy, &nInterv);
	f[0][sx][sy] = 0;
	for(int i = 1; i <= n; i ++)
		gets(obs[i]);
	for(int i = 1; i <= nInterv; i ++)
		scanf("%d %d %d\n", &interv[i].s, &interv[i].t, &interv[i].d);
	workMono();
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			ans = MAX(ans, f[nInterv][i][j]);
	printf("%d\n", ans);
}

void Solve::calc(int k, int i, int j, int d, int t)
{
	int qh = 0, qt = 0, pos = 0;
	State q[MAXN];
	while(i >= 1 && i <= n && j >= 1 && j <= m)
	{
		if(obs[i][j - 1] == 'x')
			qh = qt = 0;
		else
		{
			if(qh != qt && pos - q[qh].idx > t)
				qh ++;
			while(qh < qt && q[qt - 1].val < f[k - 1][i][j] - pos)
				qt --;
			q[qt ++] = State(pos, f[k - 1][i][j] - pos);
			f[k][i][j] = q[qh].val + pos;
		}
		i += dx[d], j += dy[d], pos ++;
	}
}

void Solve::workMono()
{
	for(int k = 1; k <= nInterv; k ++)
	{
		int t = interv[k].t - interv[k].s + 1;
		switch(interv[k].d)
		{
			case 1:
				for(int j = 1; j <= m; j ++)
					calc(k, n, j, 0, t);
				break;
			case 2:
				for(int j = 1; j <= m; j ++)
					calc(k, 1, j, 1, t);
				break;
			case 3:
				for(int i = 1; i <= n; i ++)
					calc(k, i, m, 2, t);
				break;
			case 4:
				for(int i = 1; i <= n; i ++)
					calc(k, i, 1, 3, t);
				break;
		}
	}
}

int main()
{
#ifndef STDIO
	freopen("t.in", "r", stdin);
#endif
	Solve::solve();
}
