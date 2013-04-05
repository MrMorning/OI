
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define FOR(I, A, B)	for(int I = (A); I < (B); I ++)
#define REP(I, N)	FOR(I, 0, N)
#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
#define ALL(I) (I).begin(), (I).end()
#define PB(X) push_back(X)

using namespace std;

typedef long long ll;

// }}}

const int oo = 0x3f3f3f3f;
const int V_MAX = 200, E_MAX = V_MAX * V_MAX;
struct Edge
{
	int to, dist, color;
	Edge *next;
} edge[E_MAX], *begin[V_MAX];

int nv, ne, sv, tv;

void addEdge(int u, int v, int w, int c)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], e->dist = w;
	e->color = c;
	begin[u] = e;
}

int spfa()
{
	static int queue[V_MAX][4];
	static int inQ[V_MAX][4];
	static int dist[V_MAX][4];
	memset(dist, 0x3f, sizeof(dist));
	dist[sv][0] = 0;
	inQ[sv][0] = true;
	int qh = 0, qt = 0;
	queue[qt ++][0] = sv;
	while(qh != qt)
	{
		int u = queue[qh][0], c = queue[qh][1];
		inQ[u][c] = false;
		qh = (qh + 1) % nv;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			if(c != e->color)
			{
				int k = e->color;
				int tmp = e->dist + dist[u][c];
				if(tmp < dist[v][k])
				{
					dist[v][k] = tmp;
					if(!inQ[v][k])
					{
						queue[qt][0] = v, queue[qt][1] = k;
						qt = (qt + 1) % nv;
						inQ[v][k] = true;
					}
				}
			}
		}
	}
	int res = oo;
	REP(k, 4)
		res = min(res, dist[tv][k]);
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nv, &ne);
	sv = 0, tv = nv - 1;
	REP(i, ne)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		u --, v --;
		addEdge(u, v, 1, c);
	}
	int res = spfa();
	if(res == oo)
		printf("-1\n");
	else
		cout << res;
}
