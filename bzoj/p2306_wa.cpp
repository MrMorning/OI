#include <cstdio>
#include <cassert>
#include <algorithm>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int N_VTX_MAX = 100;
const int STEP_BASE = 18;
const int STEP_LENGTH = 1 << STEP_BASE;
const int STEP_MAX = 7000000;
const int STEP_NUM = STEP_MAX / STEP_LENGTH + 1;
const double INFINITY = 10E100;

bool e[N_VTX_MAX][N_VTX_MAX];
double weight[N_VTX_MAX];
double g[STEP_BASE + 1][N_VTX_MAX][N_VTX_MAX];
double f[STEP_NUM + 1][N_VTX_MAX];
double p, p_pow[STEP_LENGTH + 1];
int n_vtx;

double pow(double a, int n)
{
	double ret = (n & 1) ? a : 1;
	n >>= 1;
	while(n)
	{
		a *= a;
		if(n & 1)
			ret *= a;
		n >>= 1;
	}
	return ret;
}
int main()
{
	freopen("t.in", "r", stdin);
	int m, s_vtx;
	scanf("%d%d", &n_vtx, &m);
	for(int u = 0; u < n_vtx; u ++)
		for(int v = 0; v < n_vtx; v ++)
			g[0][u][v] = -INFINITY;
	for(int i = 0; i < n_vtx; i ++)
		scanf("%lf", &weight[i]);
	scanf("%d", &s_vtx);
	scanf("%lf", &p);
	p_pow[0] = 1;
	for(int i = 1; i <= STEP_LENGTH; i ++)
		p_pow[i] = p_pow[i - 1] * p;
	s_vtx --;
	while(m --)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u --, v --;
		e[u][v] = true;
		g[0][u][v] = p * weight[v];
	}
	for(int k = 1; k <= STEP_BASE; k ++)
		for(int i = 0; i < n_vtx; i ++)
			for(int j = 0; j < n_vtx; j ++)
			{
				g[k][i][j] = -INFINITY;
				for(int l = 0; l < n_vtx; l ++)
				{
					if(g[k - 1][i][l] != -INFINITY && g[k - 1][l][j] != -INFINITY)
					{
						double tmp = g[k - 1][i][l] + p_pow[1 << (k - 1)] * g[k - 1][l][j];
						g[k][i][j] = MAX(g[k][i][j], tmp); 
					}
				}
			}
	for(int i = 0; i < n_vtx; i ++)
		f[0][i] = -INFINITY;
	f[0][s_vtx] = weight[s_vtx];

	double ans = f[0][s_vtx];

	for(int k = 1; k <= STEP_NUM; k ++)
		for(int i = 0; i < n_vtx; i ++)
		{
			f[k][i] = -INFINITY;
			for(int j = 0; j < n_vtx; j ++)
				if(g[STEP_BASE][j][i] != -INFINITY && f[k - 1][j] != -INFINITY)
				{
					double tmp = f[k - 1][j] + pow(p, (k - 1) * STEP_LENGTH) * g[STEP_BASE][j][i];
					f[k][i] = MAX(f[k][i], tmp);
				}
			ans = std::max(ans, f[k][i]);
		}
	//do not pass a cycle
	for(int i = 0; i < n_vtx; i ++)
		f[0][i] = -INFINITY;
	f[0][s_vtx] = weight[s_vtx];
	for(int k = 1; k < n_vtx; k ++)
		for(int i = 0; i < n_vtx; i ++)
		{
			f[k][i] = -INFINITY;
			for(int j = 0; j < n_vtx; j ++)
				if(f[k - 1][j] != -INFINITY && g[0][j][i] != -INFINITY)
				{
					double tmp = f[k - 1][j] + pow(p, k - 1) * g[0][j][i];
					f[k][i] = MAX(f[k][i], tmp);
				}
			ans = std::max(ans, f[k][i]);
		}
	printf("%.1lf\n", ans);
}
