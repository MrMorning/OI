#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int conv[55][55];
int dist[55 * 55];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PQ;

struct Edge {
	int to, len;
	Edge *next;
} edge[4444 * 55], *begin[55 * 55];
int edge_cnt = 0;

void add_edge(int u, int v, int c) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->len = c, e->next = begin[u];
	begin[u] = e;
}


void dijkstra(int s_vtx) {
	memset(dist, 0x3f, sizeof(dist));
	dist[s_vtx] = 0;
	PQ.push(make_pair(0, s_vtx));

	while ( !PQ.empty() ) {
		pair<int, int> u = PQ.top(); PQ.pop();
		if ( u.first != dist[u.second] )
			continue;
		for ( Edge *e = begin[u.second]; e; e = e->next ) {
			pair<int, int> v = make_pair(u.first + e->len, e->to);
			if ( v.first < dist[v.second] ) {
				dist[v.second] = v.first;
				PQ.push(v);
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int N, M, K;

	scanf("%d%d%d", &N, &M, &K);
	int idx = 0;
	for ( int k = 0; k <= K; k ++ )
		for ( int i = 0; i < N; i ++ )
			conv[k][i] = idx ++;

	for ( int i = 0; i < M; i ++ ) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a --, b --;
		c *= 2;
		for ( int k = 0; k <= K; k ++ ) {
			add_edge(conv[k][a], conv[k][b], c);
			add_edge(conv[k][b], conv[k][a], c);
		}
		for ( int k = 0; k < K; k ++ ) {
			add_edge(conv[k][a], conv[k + 1][b], c / 2);
			add_edge(conv[k][b], conv[k + 1][a], c / 2);
		}
	}

	dijkstra(conv[0][0]);
	int res = inf;
	for ( int k = 0; k <= K; k ++ )
		res = min(res, dist[conv[k][N - 1]]);
	printf("%d\n", res / 2);
}
