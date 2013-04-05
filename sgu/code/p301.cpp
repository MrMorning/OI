#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int VTX_MAX = 2010, EDGE_MAX = 400010;
struct Edge {
	int to, len;
	Edge *next;
} edge[EDGE_MAX], *begin[VTX_MAX];
int edgeCnt = 0;
int forward[VTX_MAX], backward[VTX_MAX];
int n, m, src, des;
#define QUERY 0
#define POINT 1
struct Event {
	int key, type;
	int l, id;
	Event(){}
	Event(int _type, int a, int b) {
		type = _type;
		if ( type == POINT ) {
			l = a, key = b;
		} else {
			id = a, key = b;
		}
	}
	bool operator< (const Event &e) const {
		return key > e.key || (key == e.key && type > e.type);
	}
} ev[EDGE_MAX];
int axis[EDGE_MAX];
int evCnt = 0, axisCnt = 0;

struct IndexTree {
	int ele[EDGE_MAX];
	void add(int x) {
		x += 2;
		for ( ; x < EDGE_MAX; x += x & -x )
			ele[x] ++;
	}
	int sum(int x) {
		x += 2;
		int res = 0;
		for ( ; x; x -= x & -x )
			res += ele[x];
		return res;
	}
} idt;

bool fine[VTX_MAX];
int ans[VTX_MAX];

void addEdge(int u, int v, int l) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->len = l, e->next = begin[u];
	begin[u] = e;
}

void expand(int x, int dist[]) {
	for ( Edge *e = begin[x]; e; e = e->next )
		dist[e->to] = min(dist[e->to], dist[x] + e->len);
}

void dijkstra(int src, int dist[]) {
	static bool done[VTX_MAX];
	memset(done, 0, sizeof(done));
	for ( int i = 1; i <= n; i ++ )
		dist[i] = 0x7f7f7f7f;
	dist[src] = 0;
	done[src] = true;
	expand(src, dist);
	for ( int i = 0; i < n - 1; i ++ ) {
		int best = 0;
		for ( int x = 1; x <= n; x ++ ) 
			if ( !done[x] ) {
				if ( !best || dist[best] > dist[x] )
					best = x;
			}
		done[best] = true;
		expand(best, dist);
	}
}

int main() {
	scanf("%d%d%d", &n, &src, &des);
	scanf("%d", &m);
	for ( int i = 0; i < m; i ++ ) {
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		addEdge(a, b, l);
		addEdge(b, a, l);
	}
	dijkstra(src, forward);
	dijkstra(des, backward);
	int target = forward[des];
	for ( int i = 1; i <= n; i ++ ) 
		fine[i] = forward[i] + backward[i] == target;
	for ( int i = 1; i <= n; i ++ )
		if ( fine[i] )
			ev[evCnt++] = Event(QUERY, i, forward[i]);
	for ( int i = 0; i < edgeCnt; i += 2 ) {
		int u = (edge + i)->to, v = (edge + i + 1)->to, l = (edge + i)->len;
		if ( fine[u] && fine[v] ) {
			if ( forward[u] > forward[v] )
				swap(u, v);
			if ( forward[u] + l == forward[v] ) 
				if ( forward[u] + 1 <= forward[v] - 1 )
					ev[evCnt++] = Event(POINT, forward[u] + 1, forward[v] - 1);
		}
	}
	for ( int i = 1; i <= n; i ++ )
		if ( fine[i] )
			ev[evCnt ++] = Event(POINT, forward[i], forward[i]);

	for ( int i = 0; i < evCnt; i ++ ) {
		if ( ev[i].type == POINT ) 
			axis[axisCnt++] = ev[i].l;
		else
			axis[axisCnt++] = ev[i].key;
	}

	sort(axis, axis + axisCnt);
	axisCnt = unique(axis, axis + axisCnt) - axis;
	sort(ev, ev + evCnt);
	for ( int i = 0; i < evCnt; i ++ ) {
		if ( ev[i].type == POINT ) 
			ev[i].l = lower_bound(axis, axis + axisCnt, ev[i].l) - axis;
		else
			ev[i].key = lower_bound(axis, axis + axisCnt, ev[i].key) - axis;
	}

	for ( int i = 0; i < evCnt; i ++ ) {
		if ( ev[i].type == POINT ) 
			idt.add(ev[i].l);
		else 
			ans[ev[i].id] = idt.sum(ev[i].key);
	}
	for ( int i = 1; i <= n; i ++ )
		printf("%d ", ans[i]);
}
