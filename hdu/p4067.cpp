#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int V_MAX = 500, E_MAX = 10000;
const int INF = 0x3f3f3f3f;

struct Edge{
	int to, cost, cap;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX], *prev[V_MAX];
int edgeCnt;
int ind[V_MAX], outd[V_MAX];
int dist[V_MAX];
int nv, ne, ssv, stv, sv, tv;

Edge *makeEdge(int u, int v, int c, int d){
	Edge *e = edge + (edgeCnt ++);
	e->to = v, e->next = begin[u], begin[u] = e;
	e->cost = d, e->cap = c;
	return e;
}

void addEdge(int u, int v, int c, int d){
	Edge *e1 = makeEdge(u, v, c, d),
		 *e2 = makeEdge(v, u, 0, -d);
	e1->inv = e2, e2->inv = e1;
}

void spfa(){
	static int Q[V_MAX];
	static bool inQ[V_MAX];
	memset(inQ, 0, sizeof(inQ));
	memset(dist, 0x3f, sizeof(dist));
	memset(prev, 0, sizeof(prev));
	dist[ssv] = 0;
	int qh = 0, qt = 0;
	Q[qt ++] = ssv;
	inQ[ssv] = true;

	while(qh != qt){
		int u = Q[qh];
		inQ[u] = false;
		qh = (qh + 1) % V_MAX;
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap){
				int v = e->to;
				if(dist[v] > dist[u] + e->cost){
					dist[v] = dist[u] + e->cost;
					prev[v] = e;
					if(!inQ[v]){
						inQ[v] = true;
						Q[qt] = v;
						qt = (qt + 1) % V_MAX;
					}
				}
			}
	}
}

int mincost(){
	int res = 0;
	while(1){
		spfa();
		if(prev[stv] == NULL)
			break;
		int flow = INF;
		for(Edge *e = prev[stv]; e; e = prev[e->inv->to])
			flow = min(flow, e->cap);
		for(Edge *e = prev[stv]; e; e = prev[e->inv->to]){
			res += flow * e->cost;
			e->cap -= flow;
			e->inv->cap += flow;
		}
	}
	return res;
}

void init(){
	memset(begin, 0, sizeof(begin));
	memset(ind, 0, sizeof(ind));
	memset(outd, 0, sizeof(outd));
	edgeCnt = 0;
}

void solve(){
	scanf("%d%d%d%d", &nv, &ne, &sv, &tv);
	ssv = nv + 1, stv = nv + 2;
	nv += 2;
	int sum = 0;
	for(int i = 1; i <= ne; i ++){
		int u, v, a, b;
		scanf("%d%d%d%d", &u, &v, &a, &b);
		if(b >= a){
			sum += a;
			addEdge(v, u, 1, b - a);
			ind[v] ++, outd[u] ++;
		}
		else{
			sum += b;
			addEdge(u, v, 1, a - b);
		}
	}
	ind[sv] ++, outd[tv] ++;

	for(int i = 1; i <= nv; i ++){
		int delta = ind[i] - outd[i];
		if(delta > 0){
			addEdge(ssv, i, delta, 0);
		}
		else if(delta < 0)
			addEdge(i, stv, -delta, 0);
	}

	int res = mincost();
	for(Edge *e = begin[ssv]; e; e = e->next)
		if(e->cap){
			printf("impossible\n");
			return;
		}
	printf("%d\n", sum + res);
}

int main(){
	int TST;
	scanf("%d", &TST);
	for(int i = 1; i <= TST; i ++){
		init();
		printf("Case %d: ", i);
		solve();
	}
}
