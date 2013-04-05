#include <cstdio>
#include <cstring>
#include <cmath>
const int V_MAX = 55, E_MAX = V_MAX * V_MAX, T_MAX = 5010;
struct Edge
{
	short t, c, to;
	Edge *next;
} edge[E_MAX], *begin[V_MAX];
struct State
{
	short vtx, t;
	State(){}
	State(short vv, short tt):
		vtx(vv), t(tt){}
};
int dist[V_MAX][T_MAX];
int timeMat[V_MAX][V_MAX];
short prev[V_MAX][T_MAX];
int out[V_MAX], nout;
int nv, ne;

void addEdge(int a, int b, int c, int d)
{
	static int edgeCnt = 0;
	Edge *e = edge + (edgeCnt ++);
	e->to = b, e->next = begin[a], e->c = c, e->t = d;
	begin[a] = e;
}

double spfa(int sv)
{
	static State Q[V_MAX * T_MAX];
	static bool inQ[V_MAX][T_MAX];
	int qh = 0, qt = 0;
	memset(dist, 0, sizeof(dist));
	Q[qt ++] = State(sv, 0);
	inQ[sv][0] = true;
	int mod = V_MAX * T_MAX;
	while(qh != qt)
	{
		State u = Q[qh];
		qh = (qh + 1) % mod;
		inQ[u.vtx][u.t] = false;
		for(Edge *e = begin[u.vtx]; e; e = e->next)
		{
			int v = e->to;
			int tmp = dist[u.vtx][u.t] + e->c;
			if(u.t + e->t > T_MAX)
				continue;
			if(tmp > dist[v][u.t + e->t])
			{
				dist[v][u.t + e->t] = tmp;
				prev[v][u.t + e->t] = u.vtx;
				if(!inQ[v][u.t + e->t])
				{
					inQ[v][u.t + e->t] = true;
					Q[qt] = State(v, u.t + e->t);
					qt = (qt + 1) % mod;
				}
			}
		}
	}
	double res = -10e100;
	for(int i = 1; i < T_MAX; i ++)
		if((double)dist[sv][i] / i > res)
			res = (double)dist[sv][i] / i;
	return res;
}

void output(int st, int u, int t)
{
	if(u != st)
		output(st, prev[u][t], t - timeMat[prev[u][t]][u]);
	out[nout ++] = u;
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
		addEdge(a, b, c, d);
		timeMat[a][b] = d;
	}
	double ansBest = -10e100;
	int ansVtx = -1;
	for(int i = 0; i < nv; i ++)
	{
		double tmp = spfa(i);
		if(ansBest < tmp)
			ansBest = tmp, ansVtx = i;
	}
	if(fabs(ansBest) < 10e-8)
	{
		printf("0\n");
		return 0;
	}
	spfa(ansVtx);
	for(int time = 1; time < T_MAX; time ++)
		if(fabs((double)dist[ansVtx][time] / time - ansBest) < 10e-8)
		{
			output(ansVtx, prev[ansVtx][time], time - timeMat[prev[ansVtx][time]][ansVtx]);
			break;
		}
	printf("%d\n", nout);
	for(int i = 0; i < nout; i ++)
		printf("%d ", out[i] + 1);
}
