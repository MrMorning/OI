#include <cstdio>
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
int n, T, d[kRange];

void addEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

int f[kRange][kRange][kRange], g[kRange][kRange];

void add(int &a, int b) {
	if ( a + b > kInf )
		a = kInf;
	else
		a += b;
}

void work(int cur, int fat) {
	for ( Edge *e = begin[cur]; e; e = e->next ) {
		if ( e->to != fat ) { 
			work(e->to, cur);
			son[cur][nSon[cur]++] = e->to;
		}
	}


	//build station on cur
	for ( int j = 1; j <= n; j ++ ) {
		f[cur][j][0] = T;
		for ( int t = 0; t < nSon[cur]; t ++ ) {
			int s = son[cur][t];
			add(f[cur][j][0], g[s][1]);
		}
	}

	if ( nSon[cur] == 0 ) {
		//no sons
		for ( int j = 0; j <= n; j ++ ) {
			f[cur][j][n] = d[j];
		}
	} else {
		for ( int j = 1; j <= n; j ++ )
			for ( int k = 1; k <= n; k ++ ) {
				//tmp1:link to ancestor
				int tmp1 = d[j];
				for ( int t = 0; t < nSon[cur]; t ++ ) {
					int s = son[cur][t];
					add(tmp1, g[s][min(n,j+1)]);
				}
				//tmp2:link to offsprings
				int tmp2 = d[k], tmp3 = kInf;
				for ( int t = 0; t < nSon[cur]; t ++ ) {
					int s = son[cur][t];
					add(tmp2, g[s][min(n,j+1)]);
					tmp3 = min(tmp3, f[s][min(n,j+1)][k-1] - g[s][min(n,j+1)]);
				}
				add(tmp2, tmp3);
				f[cur][j][k] = min(tmp1, tmp2);
			}
	}

	for ( int j = 1; j <= n; j ++ ) {
		g[cur][j] = kInf;
		for ( int k = 0; k <= n; k ++ )
			g[cur][j] = min(g[cur][j], f[cur][j][k]);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &T);
	for ( int i = 1; i < n; i ++ )
		scanf("%d", &d[i]);
	d[n] = kInf;
	for ( int i = 0; i < n - 1; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		addEdge(u, v); addEdge(v, u);
	}
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < kRange; j ++ ) {
			g[i][j] = kInf;
			for ( int k = 0; k < kRange; k ++ )
				f[i][j][k] = kInf;
		}
	work(0, -1);
	printf("%d\n", g[0][n]);
}
