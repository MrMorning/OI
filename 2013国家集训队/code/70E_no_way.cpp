#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int kInf = 0x3f3f3f3f;
const int kRange = 188;
const int kEdge = 2 * kRange;

struct Edge {
	int to;
	Edge *next;
} edge[kEdge], *begin[kRange];
int edgeCnt = 0;
int son[kRange][kRange], nSon[kRange];
int succ[kRange][kRange], nSucc[kRange];
int n, T, d[kRange];

void addEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

int f1[kRange], memo2[kRange][kRange][kRange];
bool done2[kRange][kRange][kRange];
int dist[kRange][kRange];

void add(int &a, int b) {
	if ( a + b > kInf )
		a = kInf;
	else
		a += b;
}

int dp2(int i, int j, int k) {
	if ( done2[i][j][k] ) return memo2[i][j][k];
	done2[i][j][k] = true;
	int &ret = memo2[i][j][k] = 0;

	for ( int t = 0; t < nSon[j]; t ++ ) {
		int z = son[j][t];
		ret += min(f1[z], dp2(i, z, k) + d[dist[z][k]]);
	}
	return ret;
}

void work(int cur) {
	for ( int k = 0; k < nSon[cur]; k ++ )
		work(son[cur][k]);
	f1[cur] = kInf;
	for ( int k = 0; k < nSucc[cur]; k ++ ) {
		int core = succ[cur][k];
		f1[cur] = min(f1[cur], dp2(cur, cur, core) + d[dist[cur][core]] + T);
	}
}

void initDfs(int cur, int fat) {
	for ( Edge *e = begin[cur]; e; e = e->next ) {
		if ( e->to != fat ) {
			initDfs(e->to, cur);
			son[cur][nSon[cur]++] = e->to;
			succ[cur][nSucc[cur]++] = e->to;

			for ( int k = 0; k < nSucc[e->to]; k ++ )
				succ[cur][nSucc[cur]++] = succ[e->to][k];
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &T);
	for ( int i = 1; i < n; i ++ )
		scanf("%d", &d[i]);
	d[0] = 0;
	memset(dist, 0x3f, sizeof(dist));
	for ( int i = 0; i < n - 1; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		addEdge(u, v); addEdge(v, u);
		dist[u][v] = dist[v][u] = 1;
	}
	for ( int i = 0; i < n; i ++ ) dist[i][i] = 0;
	for ( int k = 0; k < n; k ++ )
		for ( int i = 0; i < n; i ++ )
			for ( int j = 0; j < n; j ++ )
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	initDfs(0, -1);
	for ( int i = 0; i < n; i ++ )
		succ[i][nSucc[i]++] = i;
	work(0);
	printf("%d\n", f1[0]);
}
