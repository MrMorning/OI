#include <cstdio>
#include <queue>
#include <iostream>
#include <cstring>
using namespace std;

const int NODE_MAX = 100010, EDGE_MAX = 1000010;

typedef long long ll;

struct Edge {
	int to, cost;
	Edge *next;
} edge[EDGE_MAX * 2], *begin[NODE_MAX];
int edgeCnt = 0;

void addEdge(int u, int v, int w) {
	Edge *e = edge + edgeCnt ++;
	e->to = v, e->next = begin[u], e->cost = w;
	begin[u] = e;
}

struct Info {
	ll f[2];
	int id;
	Info(int _id, ll f0, ll f1) {
		id = _id;
		f[0] = f0;
		f[1] = f1;
	}
	bool operator< (const Info &t) const {
		return f[1] > t.f[1];
	}
};

priority_queue<Info> PQ;
int term;
ll dist[NODE_MAX][2];
int nNode, nEdge, nOut;
int out[NODE_MAX];
void dijkstra() {
	memset(dist, 0x3f, sizeof(dist));
	for ( int i = 0; i < nOut; i ++ ) {
		dist[out[i]][0] = 0;
		dist[out[i]][1] = 0;
		PQ.push(Info(out[i], 0, 0));
	}

	while ( !PQ.empty() ) {
		Info u = PQ.top(); PQ.pop();
		if ( u.f[0] != dist[u.id][0] || u.f[1] != dist[u.id][1] )
			continue;
		for ( Edge *e = begin[u.id]; e; e = e->next ) {
			ll tmp = u.f[1] + e->cost;
			if ( tmp < dist[e->to][0] ) {
				dist[e->to][1] = dist[e->to][0];
				dist[e->to][0] = tmp;
				PQ.push(Info(e->to, dist[e->to][0], dist[e->to][1]));
			} else if ( tmp < dist[e->to][1] ) {
				dist[e->to][1] = tmp;
				PQ.push(Info(e->to, dist[e->to][0], dist[e->to][1]));
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);

	scanf("%d%d%d", &nNode, &nEdge, &nOut);
	term = nNode;
	while ( nEdge -- ) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}

	for ( int i = 0; i < nOut; i ++ ) 
		scanf("%d", &out[i]);

	dijkstra();

	cout << dist[0][1];
}
