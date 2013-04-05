/*
 * $File: p2306_dd.cpp
 * $Date: Thu May 12 10:48:36 2011 +0800
 * $Source: BZOJ
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

const int MAXN = 100, MAXM = 1000;
const double EPS = 1E-6;

int n, m, cnt = 0, begin[MAXN + 1], end[MAXM + 1], next[MAXM + 1];
double w[MAXN + 1], p;
int s;
bool selfvis[MAXN + 1];

void add_edge(int u, int v)
{
	next[++cnt] = begin[u];
	begin[u] = cnt;
	end[cnt] = v;

	if (u == v) selfvis[u] = 1;
}

int dfn[MAXN + 1], low[MAXN + 1], dcnt = 0, bcnt = 0;
int b[MAXN + 1][MAXN + 1], b2[MAXN + 1], b3[MAXN + 1];
int stack[MAXN + 1], stop = 0;
bool vis[MAXN + 1];

void dfs(int u)
{
	dfn[u] = low[u] = ++dcnt;
	vis[u] = 1;
	stack[++stop] = u;

	for (int now = begin[u], v; now; now = next[now])
		if (!dfn[v = end[now]])
		{
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (vis[v]) low[u] = std::min(low[u], dfn[v]);

	if (low[u] == dfn[u])
	{
		b[++bcnt][0] = 0;
		do
		{
			b2[stack[stop]] = bcnt;
			b[bcnt][++b[bcnt][0]] = stack[stop];
			b3[stack[stop]] = b[bcnt][0];
			vis[stack[stop]] = 0;
		} while (stack[stop--] != u);
	}
}

double f[MAXN + 1][MAXN + 1];
double g[MAXN + 1][MAXN + 1];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lf", &w[i]);
	scanf("%d %lf", &s, &p);
	for (int u, v; m; m--)
	{
		scanf("%d %d", &u, &v);
		add_edge(u, v);
	}

	double pow[MAXN + 1];
	pow[0] = 1;
	for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * p;

	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= n; i++)
	{
		if (b[b2[i]][0] == 1)
		{
			if (!selfvis[i]) g[i][0] = w[i];
			else
				g[i][0] = w[i] / (1 - p);
		}
		else
		{
			for (int j = b3[i], k = 0; k < b[b2[i]][0]; j = j % b[b2[i]][0] + 1, k++)
				g[i][0] += w[b[b2[i]][j]] * pow[k];
			g[i][0] /= (1 - pow[b[b2[i]][0]]);
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = g[i][j - 1] * p;

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			f[i][j] = ~0U >> 1;
	f[0][s] = w[s];
	double ans = g[0][s], INF = f[0][0];

	for (int i = 0; i < n; i++)
		for (int j = 1; j <= n; j++)
			if (fabs(f[i][j] - INF) > EPS)
			{
				for (int now = begin[j], k; now; now = next[now])
				{
					k = end[now];
					if (fabs(f[i + 1][k] - INF) < EPS) f[i + 1][k] = 0;
					f[i + 1][k] = std::max(f[i + 1][k], f[i][j] + pow[i + 1] * w[k]);
					ans = std::max(ans, f[i][j] + g[k][i + 1]);
				}	
			}

	printf("%.1lf\n", ans);
	return 0;
}
