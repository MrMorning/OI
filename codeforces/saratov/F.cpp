/*
 * $Date: Wed Oct 19 10:39:06 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem F
 * $Method:	BFS
 */
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int V_MAX = 111;
struct Edge{
	int to;
	Edge *next;
} edge[V_MAX * 2], *begin[V_MAX];
int dist[V_MAX];
int edgeCnt;

void addEdge(int u, int v){
	Edge *e = edge + (edgeCnt ++);
	e->to = v, e->next = begin[u], begin[u] = e;
}

void bfs(int st){
	static int Q[V_MAX];
	int qt = 0;
	Q[qt ++] = st;
	memset(dist, -1, sizeof(dist));
	dist[st] = 0;
	for(int qh = 0; qh < qt; qh ++){
		int u = Q[qh];
		for(Edge *e = begin[u]; e; e = e->next){
			int v = e->to;
			if(dist[v] != -1)
				continue;
			dist[v] = dist[u] + 1;
			Q[qt ++] = v;
		}
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	int res = 0;
	while(T --){
		int n;
		scanf("%d", &n);
		edgeCnt = 0;
		memset(begin, 0, sizeof(begin));
		for(int i = 0; i < n - 1; i ++){
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
		}
		bfs(1);
		int best = 0;
		for(int i = 1; i <= n; i ++)
			if(best == 0 || dist[best] < dist[i])
				best = i;
		bfs(best);
		int tmp = 0;
		for(int i = 1; i <= n ;i ++)
			tmp = max(tmp, dist[i]);
		res += tmp;
	}
	printf("%d\n", res);
}
