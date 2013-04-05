#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
const int N_MAX = 55;
const double EPS = 10e-8;
int C[N_MAX][N_MAX];
int T[N_MAX][N_MAX];
bool E[N_MAX][N_MAX];
double W[N_MAX][N_MAX];
int nv, ne;
double dist[N_MAX];
int Q[N_MAX * N_MAX];
bool inQ[N_MAX];
int times[N_MAX];
bool vis[N_MAX];
int prev[N_MAX];
int out[N_MAX];

bool negExist(double lamda)
{
	for(int i = 0; i < nv; i ++)
		for(int j = 0; j < nv; j ++)
			if(E[i][j])
				W[i][j] = T[i][j] - lamda * C[i][j];

	memset(inQ, 0, sizeof(inQ));
	memset(times, 0, sizeof(times));
	for(int i = 0; i < nv; i ++)
		dist[i] = 0;
	int qh = 0, qt = 0;
	for(int i = 0; i < nv; i ++)
		Q[qt ++] = i, inQ[i] = true, times[i] = 1;
	while(qh != qt)
	{
		int u = Q[qh];
		qh = (qh + 1) % (N_MAX * N_MAX);
		inQ[u] = false;
		for(int v = 0; v < nv; v ++)
			if(E[u][v])
			{
				double tmp = dist[u] + W[u][v];
				if(tmp < dist[v])
				{
					dist[v] = tmp;
					if(!inQ[v])
					{
						inQ[v] = true;
						if(times[v] > nv)
							return true;
						times[v] ++;
						Q[qt] = v;
						qt = (qt + 1) % (N_MAX * N_MAX);
					}
				}
			}
	}
	return false;
}
int found;
bool dfs(int u, int term)
{
	vis[u] = true;
	for(int v = 0; v < nv; v ++)
		if(E[u][v] && (dist[u] + W[u][v] - dist[v]) <= 0)
		{
			if(v == term)
			{
				prev[v] = u;
				return true;
			}
			if(!vis[v])
			{
				prev[v] = u;
				if(dfs(v, term))
					return true;
			}
		}
	return false;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nv, &ne);
	for(int i = 0; i < ne; i ++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a --, b --;
		C[a][b] = c, T[a][b] = d;
		E[a][b] = true;
	}
	double lb = 0, rb = 5000;
	for(double mid = (lb + rb) / 2; rb - lb > EPS; mid = (lb + rb) / 2)
		if(negExist(mid))
			rb = mid;
		else
			lb = mid;
	negExist(rb);
	memset(prev, -1, sizeof(prev));
	found = -1;
	for(int u = 0; u < nv; u ++)
	{
		memset(vis, 0, sizeof(vis));
		memset(prev, -1, sizeof(prev));
		if(dfs(u, u))
		{
			found = u;
			break;
		}
	}
	if(found == -1)
		printf("0\n");
	else
	{
		int u = found;
		int top = 0;
		while(1)
		{
			out[top ++] = u;
			if(prev[u] == found)
				break;
			u = prev[u];
		}
		printf("%d\n", top);
		for(int i = top - 1; i >= 0; i --)
			printf("%d ", out[i] + 1);
		double rval = 0, lval = 0;
		int p = out[0];
		for(int i = top - 1; i >= 0; i --)
		{
			rval += C[p][out[i]];
			lval += T[p][out[i]];
			p = out[i];
		}
		assert(fabs(lval / rval - rb) < EPS);
	}
}
