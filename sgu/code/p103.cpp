#include <cstdio>
#include <algorithm>
#define BLUE 0
#define PURPLE 1
using namespace std;

const int V_MAX = 310, E_MAX = 30010;
const int oo = 0x3f3f3f3f;

int dist[V_MAX], initC[V_MAX], initRT[V_MAX];
int T[2][V_MAX];
int nv, ne, sv, tv, edgeCnt;
int prev[V_MAX];

struct Edge
{
	Edge *next;
	int to, len;
} edge[E_MAX], *begin[V_MAX];

void addEdge(int u, int v, int l)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], begin[u] = e;
	e->len = l;
}

inline void getColor(int i, int curT, int &curC, int &RT)
{/*{{{*/
	if(curT < initRT[i])
	{
		curC = initC[i];
		RT = initRT[i] - curT;
	}
	else
	{
		curT = (curT - initRT[i]) % (T[BLUE][i] + T[PURPLE][i]);
		int ic = initC[i];
		if(curT < T[!ic][i])
		{
			curC = !ic;
			RT = T[!ic][i] - curT;
		}
		else
		{
			curC = ic;
			RT = T[BLUE][i] + T[PURPLE][i] - curT;
		}
	}
}/*}}}*/

inline int getWaitTime(int i, int j, int curT)
{/*{{{*/
	int res = 0;
	for(int cnt = 0; cnt < 14; cnt ++)
	{
		int ci, cj, RTi, RTj;
		getColor(i, curT, ci, RTi);
		getColor(j, curT, cj, RTj);
		if(ci == cj)
			return res;
		if(RTi != RTj)
		{
			if(RTi > RTj)
				swap(RTi, RTj), swap(ci, cj);
			return res + RTi;
		}
		else
			res += RTi, curT += RTi;
	}
	return -1;
}/*}}}*/

void spfa(int sv)
{
	static int queue[V_MAX];
	static bool inQ[V_MAX];
	for(int i = 1; i <= nv; i ++)
		dist[i] = oo;
	int qh = 0, qt = 0;
	queue[qt ++] = sv;
	dist[sv] = 0;
	inQ[sv] = true;

	while(qh != qt)
	{
		int u = queue[qh];
		inQ[u] = false;
		qh = (qh + 1) % nv;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			int tmp = getWaitTime(u, v, dist[u]);
			if(tmp == -1)
				continue;
			tmp += dist[u] + e->len;
			if(tmp < dist[v])
			{
				dist[v] = tmp, prev[v] = u;
				if(!inQ[v])
				{
					inQ[v] = true;
					queue[qt] = v;
					qt = (qt + 1) % nv;
				}
			}
		}
	}
}

void output(int u)
{
	if(u == 0)
		return;
	output(prev[u]);
	printf("%d ", u);
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d", &sv, &tv);
	scanf("%d%d", &nv, &ne);
	for(int i = 1; i <= nv; i ++)
	{
		char str[5];
		scanf("%s%d%d%d", str, &initRT[i], &T[BLUE][i], &T[PURPLE][i]);
		initC[i] = (str[0] == 'B' ? BLUE : PURPLE);
	}
	while(ne --)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	spfa(sv);
	if(dist[tv] == oo)
		printf("0\n");
	else
	{
		printf("%d\n", dist[tv]);
		output(prev[tv]);
		printf("%d\n", tv);
	}
}
