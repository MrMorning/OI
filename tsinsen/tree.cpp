#include <cstdio>
#include <algorithm>
using namespace std;
const int V_MAX = 50010;
const int E_MAX = 100010;
int n_vtx, n_edge, need;

struct Edge {
	int u, v, c;
	int w;
	bool operator< (const Edge &tmp) const {
		return w < tmp.w || (w == tmp.w && c > tmp.c);
	}
} edge[E_MAX];

int fa[V_MAX];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

pair<int, int> calc(int delta) {
	for ( int i = 0; i < n_edge; i ++ )
		if ( edge[i].c == 0 )
			edge[i].w += delta;
	sort(edge, edge + n_edge);
	for ( int i = 0; i < n_vtx; i ++ )
		fa[i] = i;
	pair<int, int> res = make_pair(0, 0);
	for ( int i = 0; i < n_edge; i ++ ) {
		int u = edge[i].u, v = edge[i].v;
		if ( find(u) != find(v) ) {
			fa[find(u)] = find(v);
			res.first += edge[i].c == 0;
			res.second += edge[i].w;
		}
	}

	for ( int i = 0; i < n_edge; i ++ )
		if ( edge[i].c == 0 )
			edge[i].w -= delta;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n_vtx, &n_edge, &need);
	for ( int i = 0; i < n_edge; i ++ ) 
		scanf("%d%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w, &edge[i].c);
	int lb = -111, rb = 111;
	for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 ) {
		if ( calc(mid).first <= need )
			rb = mid;
		else
			lb = mid;
	}
	int res = (int)(calc(rb).second - need * rb);
	printf("%d\n", res);
}
