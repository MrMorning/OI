#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
//#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
const int inf = 0x3f3f3f3f;

inline int rand2(){static int x=1;x+=(x<<2)+1; x&=(0x7fffffff);return (x&(65536))>0;}

int kshort;
int distbase;

namespace dia {
	const int DIA_EDGE_MAX = 500000;
	const int DIA_VTX_MAX = 500000;
	typedef pair<int, int> pair_t;
	struct Edge {
		int to, len;
		Edge *next;
	} edge[DIA_EDGE_MAX], *begin[DIA_VTX_MAX];
	int edgeCnt = 0;
	int src;
	priority_queue<pair_t, vector<pair_t>, greater<pair_t> > PQ;

	void addEdge(int u, int v, int w) {
		Edge *e = edge + edgeCnt++;
		e->to = v, e->len = w, e->next = begin[u];
		begin[u] = e;
	}

	void main() {
		PQ.push(make_pair(0, src));
		int left = kshort;
		while ( !PQ.empty() && left ) {
			pair_t u = PQ.top(); PQ.pop();
			printf("%d\n", distbase + u.first);
			left --;
			for ( Edge *e = begin[u.second]; e; e = e->next ) {
				pair_t v = make_pair(u.first + e->len, e->to);
				PQ.push(v);
			}
		}
		while ( left -- ) 
			puts("NO");
	}
}

namespace prework {
	//maintainable mergable heap
	const int HEAP_NODE_MAX = 500000;
	const int REAL_EDGE_MAX = 100000;
	const int REAL_VTX_MAX = 10000;

	struct HeapNode {
		HeapNode *ch[2];
		int key, id, ed;
	} heapMemo[HEAP_NODE_MAX];
	int freePos = 0;

	HeapNode *alloc() {
		HeapNode *x = &heapMemo[freePos++];
		x->id = freePos - 1;
		return x;
	}

	HeapNode *merge(HeapNode *p, HeapNode *q){
		if ( p == NULL || q == NULL )
			return p == NULL ? q : p;
		if ( p->key > q->key ) 
			swap(p, q);
		HeapNode *np = alloc();
		np->key = p->key, np->ed = p->ed;
	   	np->ch[0] = p->ch[0], np->ch[1] = p->ch[1];
		int t = rand2();
		np->ch[t] = merge(np->ch[t], q);
		if ( np->ch[0] )
			dia::addEdge(np->id, np->ch[0]->id, np->ch[0]->key - np->key);
		if ( np->ch[1] )
			dia::addEdge(np->id, np->ch[1]->id, np->ch[1]->key - np->key);
		return np;
	}


	typedef pair<int, int> pair_t;
	struct Edge {
		int to, len, id;
		bool isRev;
		Edge *next, *inv;
	} edge[REAL_EDGE_MAX], *begin[REAL_VTX_MAX];
	int edgeCnt = 0;
	int src, des;
	priority_queue<pair_t, vector<pair_t>, greater<pair_t> > PQ;
	int dist[REAL_VTX_MAX];
	Edge *prev[REAL_VTX_MAX];
	int nVtx, nEdge;
	HeapNode *root[REAL_VTX_MAX];

	Edge *makeEdge(int u, int v, int w) {
		Edge *e = edge + edgeCnt++;
		e->to = v, e->len = w, e->next = begin[u];
		e->id = edgeCnt-1;
		return begin[u] = e;
	}

	void addEdge(int u, int v, int w) {
		Edge *e1 = makeEdge(u, v, w),
			 *e2 = makeEdge(v, u, w);
		e1->inv = e2, e2->inv = e1;
		e2->isRev = true;
	}

	void dijkstra() {
		memset(dist, 0x3f, sizeof(dist));
		PQ.push(make_pair(0, des));
		dist[des] = 0;
		while ( !PQ.empty() ) {
			pair_t u = PQ.top(); PQ.pop();
			if ( u.first != dist[u.second] ) 
				continue;
			for ( Edge *e = begin[u.second]; e; e = e->next ) 
				if ( e->isRev ) {
					pair_t v = make_pair(e->len + u.first, e->to);
					if ( v.first < dist[v.second] ) {
						dist[v.second] = v.first;
						prev[v.second] = e;
						PQ.push(v);
					}
				}
		}
	}

	bool cmpDist(int i, int j) {
		return dist[i] < dist[j];
	}

	void main() {
		scanf("%d%d%d", &nVtx, &nEdge, &kshort);

		scanf("%d%d", &src, &des);
		src--, des--;
		for ( int i = 0; i < nEdge; i ++ ) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a --, b --;
			addEdge(a, b, c);
		}

		dijkstra();
		if ( dist[src] == inf ) {
			while ( kshort -- ) 
				puts("NO");
			exit(0);
		}
		distbase = dist[src];
		static int arr[REAL_VTX_MAX];
		for ( int i = 0; i < nVtx; i ++ ) 
			arr[i] = i;
		sort(arr, arr + nVtx, cmpDist);
		for ( int i = 0; i < nVtx; i ++ ) 
			if ( dist[arr[i]] != inf ) {
				int u = arr[i];
				root[u] = NULL;
				if ( prev[u] )
					root[u] = root[prev[u]->inv->to];
				for ( Edge *e = begin[u]; e; e = e->next )
					if ( !e->isRev && (prev[u] == NULL || e != prev[u]->inv) 
							&& dist[e->to] != inf ) {
						int delta = dist[e->to] + e->len - dist[u];
						HeapNode *x = alloc();
						x->key = delta;
						x->ch[0] = x->ch[1] = NULL;
						x->ed = e->id;
						root[u] = merge(root[u], x);
					}
			}
		for ( int i = 0; i < freePos; i ++ ) {
			HeapNode *x = heapMemo + i,
					 *y = root[(edge + x->ed)->to];
			if ( y )
				dia::addEdge(x->id, y->id, y->key);
		}
		if ( root[src] )
			dia::addEdge(freePos, root[src]->id, root[src]->key);
		dia::src = freePos;
	}
}

int main() {
	freopen("t.in", "r", stdin);
	prework::main();
	dia::main();
}
