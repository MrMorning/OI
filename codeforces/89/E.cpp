#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int V_MAX = 100000, E_MAX = 3 * 100000;

struct Edge{
	int to, dir;
	Edge *next, *inv;
} edge[E_MAX * 2], *begin[V_MAX];
int edgeCnt = 0;
int father[V_MAX], dfn[V_MAX], low[V_MAX];
int N, M;

Edge *makeEdge(int u, int v){
	Edge *e = edge + (edgeCnt ++);
	e->to = v, e->next = begin[u];
	e->dir = -1;
	return begin[u] = e;
}

void addEdge(int u, int v){
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inv = e2, e2->inv = e1;
}

void dfs(int x){
	static int dfnIdx = 0;
	dfn[x] = low[x] = dfnIdx ++;
	for(Edge *e = begin[x]; e; e = e->next){
		int y = e->to;
		if(dfn[y] == -1){
			father[y] = x;
			dfs(y);
			e->dir = y;
		   	low[x] = min(low[x], low[y]);
			if(low[y] > dfn[x]){
				printf("0\n");
				exit(0);
			}
		}
		else if(y != father[x] && dfn[y] < dfn[x]){
			low[x] = min(low[x], dfn[y]);
			e->dir = y;
		}
	}
}

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for(int i = 0; i < M; i ++){
		int u, v;
		scanf("%d%d", &u, &v);
		u --, v --;
		addEdge(u, v);
	}
	memset(dfn, -1, sizeof(dfn));
	memset(low, -1, sizeof(low));
	memset(father, -1, sizeof(father));
	for(int i = 0, cnt = 0; i < N; i ++)
		if(dfn[i] == -1){
			cnt ++;
			if(cnt > 1){
				printf("0\n");
				return 0;
			}
			dfs(i);
		}
	for(int i = 0; i < edgeCnt; i += 2)
		if(edge[i].dir == edge[i].to)
			printf("%d %d\n", edge[i].inv->to + 1, edge[i].to + 1);
		else
			printf("%d %d\n", edge[i].to + 1, edge[i].inv->to + 1);
}
