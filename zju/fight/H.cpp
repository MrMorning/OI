#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 1011;

struct Edge {
	int to;	
	Edge *next;
} edge[N_MAX * N_MAX], *begin[N_MAX];
int edge_cnt = 0;
int N, M, C;
int done[N_MAX], memo[N_MAX];
int a[N_MAX], b[N_MAX], x[N_MAX], y[N_MAX], h[N_MAX];

void add_edge(int u, int v) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], begin[u] = e;
}

int dfs(int x) {
	if ( done[x] )
		return memo[x];
	done[x] = true;
	int &res = memo[x] = 0;
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		res = max(res, dfs(y));
	}
	res += h[x];
	return res;
}

bool intersected(int a, int b, int c, int d) {
	if ( a > c ) {
		swap(a, c);
		swap(b, d);
	}
	return b > c;
}
bool intersected(int i, int j) {
	bool bver = intersected(x[i], x[i] + a[i], x[j], x[j] + a[j]);
	bool bhor = intersected(y[i], y[i] + b[i], y[j], y[j] + b[j]);
	return bver && bhor;
}
int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d%d%d", &N, &M, &C) != EOF ) {
		memset(begin, 0, sizeof(begin));
		memset(done, 0, sizeof(done));
		edge_cnt = 0;
		for ( int i = 0; i < C; i ++ )
			scanf("%d%d%d%d%d", &a[i], &b[i], &h[i], &x[i], &y[i]);
		for ( int i = 0; i < C; i ++ )
			for ( int j = i + 1; j < C; j ++ ) {
				if ( intersected(i, j) )
					add_edge(j, i);
			}
		int res = 0;
		for ( int i = 0; i < C; i ++ )
			res = max(res, dfs(i));
		printf("%d\n", res);
	}
}
