
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}


const int N_VTX_MAX = 5000;
const int N_EDGE_MAX = 100000;
const int inf = 0x3f3f3f3f;
 
struct Edge
{
    int cap, cost, vtx;
    Edge *next, *inverse;
};
 
Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *prev[N_VTX_MAX], *pe[N_VTX_MAX];
int n_edge, n_vtx, s_vtx, t_vtx;
 
int dist[N_VTX_MAX];
 
Edge *make_edge(int u, int v, int cap, int cost)
{
    Edge *e = &edge[n_edge ++];
    e->vtx = v, e->next = begin[u], e->cap = cap, e->cost = cost;
    return begin[u] = e;
}
 
void add_edge(int u, int v, int cap, int cost)
{
    Edge *e1 = make_edge(u, v, cap, cost),
         *e2 = make_edge(v, u, 0, -cost);
    e1->inverse = e2, e2->inverse = e1;
}
 
bool spfa(int s_vtx, int t_vtx)
{
    static int queue[N_VTX_MAX];
    static bool in_q[N_VTX_MAX];
    for(int i = 0; i < n_vtx; i ++)
        dist[i] = inf;
    dist[s_vtx] = 0;
    memset(in_q, 0, sizeof(in_q));
    memset(prev, 0, sizeof(Edge *) * n_vtx);
    int qt = 0, qh = 0;
 
    queue[qt ++] = s_vtx, in_q[s_vtx] = true;
    while(qt != qh)
    {
        int u = queue[qh];
        in_q[u] = false;
        qh = (qh + 1) % n_vtx;
        for(Edge *e = begin[u]; e; e = e->next)
            if(e->cap)
            {
                int v = e->vtx;
                if(dist[v] > dist[u] + e->cost)
                {
                    dist[v] = dist[u] + e->cost;
                    prev[v] = e;
                    if(! in_q[v])
                    {
                        in_q[v] = true;
                        queue[qt] = v;
                        qt = (qt + 1) % n_vtx;
                    }
                }
            }
    }
    return dist[t_vtx] != inf;
}
 
int min_cost_flow(int s_vtx, int t_vtx)
{
    int cost = 0;
    while(spfa(s_vtx, t_vtx))
    {
        int u = t_vtx;
        int flow = 0x3f3f3f3f;
        while(1)
        {
            if(prev[u] == NULL)
                break;
            flow = std::min(flow, prev[u]->cap);
            u = prev[u]->inverse->vtx;
        }
        u = t_vtx;
        while(1)
        {
            if(prev[u] == NULL)
                break;
            Edge *e = prev[u];
            e->cap -= flow, e->inverse->cap += flow;
            cost += e->cost * flow;
            u = prev[u]->inverse->vtx;
        }
    }
    return cost;
}

const int N_MAX = 1010;
int axis[N_MAX * 2], axis_cnt = 0;
int S[N_MAX], T[N_MAX], C[N_MAX];
int N, K;
int main(){
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%d%d%d", &S[i], &T[i], &C[i]);
		axis[axis_cnt ++] = S[i];
		axis[axis_cnt ++] = S[i] + T[i];
	}
	sort(axis, axis + axis_cnt);
	n_vtx = axis_cnt + 2;
	s_vtx = n_vtx - 2, t_vtx = n_vtx - 1;
	add_edge(s_vtx, 0, K, 0);
	add_edge(axis_cnt - 1, t_vtx, K, 0);
	for ( int i = 0; i < axis_cnt - 1; i ++ )
		add_edge(i, i + 1, inf, 0);
	for ( int i = 1; i <= N; i ++ ) {
		int l = lower_bound(axis, axis + axis_cnt, S[i]) - axis,
			r = lower_bound(axis, axis + axis_cnt, S[i] + T[i]) - axis;
		add_edge(l, r, 1, -C[i]);
		pe[i] = edge + n_edge - 2;
	}
	min_cost_flow(s_vtx, t_vtx);
	for ( int i = 1; i <= N; i ++ )
		if ( pe[i]->cap == 0 )
			printf("1 ");
		else
			printf("0 ");
}
