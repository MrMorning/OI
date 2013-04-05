#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int TEAM_MAX = 22;
const int VTX_MAX = 100000;
const int EDGE_MAX = 1000000;
const int inf = 0x3f3f3f3f;
int nTeam, won[TEAM_MAX], rem[TEAM_MAX];
int mat[TEAM_MAX][TEAM_MAX];
int nVtx, src, des;

struct Edge {
	int to, cap;
	Edge *next, *inv;
} edge[EDGE_MAX], *begin[VTX_MAX];
int level[VTX_MAX];
int edgeCnt = 0;

Edge *makeEdge(int u, int v, int cap) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], e->cap = cap;
	return begin[u] = e;
}

void addEdge(int u, int v, int cap) {
	Edge *e1 = makeEdge(u, v, cap),
		 *e2 = makeEdge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
}

bool relable(int src, int des) {
	static int Q[VTX_MAX];
	memset(level, -1, sizeof(level));
	level[src] = 0;
	int qt = 0;
	Q[qt ++] = src;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		for ( Edge *e = begin[u]; e; e = e->next ) 
			if ( e->cap ) {
				int v = e->to;
				if ( level[v] != -1 )
					continue;
				level[v] = level[u] + 1;
				Q[qt ++] = v;
			}
	}
	return level[des] != -1;
}

int findAug(int u, int des, int flow) {
	if ( u == des )
		return flow;
	Edge *e;
	int res = 0;
	for ( e = begin[u]; e; e = e->next )
		if ( e->cap ) {
			int v = e->to;
			if ( level[v] == level[u] + 1 ) {
				int tmp = findAug(v, des, min(flow, e->cap));
				e->cap -= tmp, e->inv->cap += tmp;
				flow -= tmp, res += tmp;
				if ( !flow )
					break;
			}
		}
	if ( !e )
		level[u] = -1;
	return res;
}

void dinic(int src, int des) {
	while ( relable(src, des) )
		findAug(src, des, inf);
}

int main() {
	scanf("%d", &nTeam);
	for ( int i = 0; i < nTeam; i ++ )
		scanf("%d", &won[i]);
	for ( int i = 0; i < nTeam; i ++ )
		scanf("%d", &rem[i]);
	int base = won[0] + rem[0];
	for ( int i = 0; i < nTeam; i ++ )
		for ( int j = 0; j < nTeam; j ++ )
			scanf("%d", &mat[i][j]);
	nVtx = nTeam + 2;
	src = nVtx - 2, des = nVtx - 1;
	for ( int i = 0; i < nTeam; i ++ ) {
		if ( base < won[i] ) {
			puts("NO");
			return 0;
		}
		addEdge(i, des, base - won[i]);
	}
	for ( int i = 1; i < nTeam; i ++ )
		for ( int j = i + 1; j < nTeam; j ++ ) 
			if ( mat[i][j] > 0 ) {
				addEdge(src, nVtx, mat[i][j]);
				addEdge(nVtx, i, inf);
				addEdge(nVtx, j, inf);
				nVtx++;
			}
	dinic(src, des);
	for ( Edge *e = begin[src]; e; e = e->next )
		if ( e->cap != 0 ) {
			puts("NO");
			return 0;
		}
	puts("YES");
}
