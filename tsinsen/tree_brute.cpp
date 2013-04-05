#include <cstdio>
#include <algorithm>
using namespace std;
const int V_MAX = 50010;
const int E_MAX = 100010;
int n_vtx, n_edge, need;

struct Edge {
	int u, v, w, c;
} edge[E_MAX];

int fa[V_MAX];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int count_bits(int s) {
	int res = 0;
	while ( s ) 
		res += s & 1, s >>= 1;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n_vtx, &n_edge, &need);
	for ( int i = 0; i < n_edge; i ++ ) 
		scanf("%d%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w, &edge[i].c);
	int res = 0x3f3f3f3f;
	for ( int i = 0, lim = 1 << n_edge; i < lim; i ++ ) 
		if ( count_bits(i) == n_vtx - 1 ) {
			int white_cnt = 0;
			for ( int j = 0; j < n_edge; j ++ )
				if ( i & (1 << j) )
					if ( edge[j].c == 0 )
						white_cnt ++;
			if ( white_cnt != need )
				continue;
			for ( int j = 0; j < n_vtx; j ++ )
				fa[j] = j;
			int val = 0;
			bool fail = false;
			for ( int j = 0; j < n_edge; j ++ )
				if ( i & (1 << j) ) {
					int u = edge[j].u, v = edge[j].v;
					if ( find(u) == find(v) ) {
						fail = true;
						break;
					}
					fa[find(u)] = find(v);
					val += edge[j].w;
				}
			if ( !fail )
				res = min(res, val);
		}
	printf("%d\n", res);
}
