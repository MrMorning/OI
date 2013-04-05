#include <cstdio>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
#define pb(x) push_back(x)
using namespace std;

const int kNodeMax = 10010;

struct Node {
	Node *ch[2], *pre;
	int val[2], tag[2];
} node[kNodeMax];
struct Edge {
	int u, v;
} edge[kNodeMax];
int nNode, nEdge;
map<pair<int, int>, int> edgeIdx;

int color[kNodeMax], father[kNodeMax];
vector<int> adj[kNodeMax];
vector<int> ans;

void mark(Node *x, int *tag) {
	x->val[0] += tag[0];
	x->tag[0] += tag[0];
	x->val[1] += tag[1];
	x->tag[1] += tag[1];
}

void pushDown(Node *x) {
	for ( int c = 0; c <= 1; c ++ )
		if ( x->ch[c] ) {
			mark(x->ch[c], x->tag);
		}
	x->tag[0] = x->tag[1] = 0;
}

void rotate(Node *x, int dir) {
	Node *y = x->pre;
	x->pre = y->pre;
	if ( y->pre && y == y->pre->ch[y == y->pre->ch[1]] )
		y->pre->ch[y == y->pre->ch[1]] = x;
	y->ch[!dir] = x->ch[dir];
	if ( x->ch[dir] ) 
		x->ch[dir]->pre = y;
	x->ch[dir] = y, y->pre = x;
}

void splay(Node *x) {
	pushDown(x);
	while ( x->pre && x == x->pre->ch[x == x->pre->ch[1]] ) {
		Node *y = x->pre, *z = y->pre;
		if ( !z || y != z->ch[y == z->ch[1]] ) {
			pushDown(y);
			pushDown(x);
			rotate(x, x == y->ch[0]);
		} else {
			pushDown(z); pushDown(y); pushDown(x);
			if ( y == z->ch[0] ) {
				if ( x == y->ch[0] )
					rotate(y, 1), rotate(x, 1);
				else 
					rotate(x, 0), rotate(x, 1);
			} else {
				if ( x == y->ch[1] )
					rotate(y, 0), rotate(x, 0);
				else
					rotate(x, 1), rotate(x ,0);
			}
		}
	}
}

Node *expose(Node *x) {
	Node *y = NULL;
	while ( x != NULL ) {
		splay(x);
		pushDown(x);
		x->ch[1] = y;
		x = (y = x)->pre;
	}
	return y;
}

pair<int, int> askVal(int u) {
	Node *x = node + u;
	expose(x);
	splay(x);
	return make_pair(x->val[0], x->val[1]);
}

void change(int u, int v, int type) {
//	fprintf(stderr, "Add path(%d, %d), %d\n", u, v, type);
	int tmp[2];
	tmp[type] = 1, tmp[!type] = 0;
	Node *x = node + u, *y = node + v;
	if ( x == y ) 
		return;
	expose(x);
	Node *p = expose(y);
	if ( x != p ) {
		splay(x);
		mark(x, tmp);
	}
	if ( y != p && p->ch[1] ) {
		splay(p);
		pushDown(p);
		mark(p->ch[1], tmp);
	}
}


void bfsColor(int st) {
	static int Q[kNodeMax];
	int qt = 0;
	Q[qt++] = st;
	color[st] = 0;
	father[st] = -1;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		foreach(it, adj[u]) {
			int v = *it;
			if ( color[v] == -1 ) {
				color[v] = color[u] ^ 1;
				father[v] = u;
				Q[qt++] = v;
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nNode, &nEdge);
	for ( int i = 0; i < nEdge; i ++ ) {
		scanf("%d%d", &edge[i].u, &edge[i].v);
		edge[i].u--, edge[i].v--;
		edgeIdx[make_pair(edge[i].u, edge[i].v)] = i;
		edgeIdx[make_pair(edge[i].v, edge[i].u)] = i;
		adj[edge[i].u].pb(edge[i].v);
		adj[edge[i].v].pb(edge[i].u);
	}
	memset(color, -1, sizeof(color));
	for ( int i = 0; i < nNode; i ++ )
		if ( color[i] == -1 )
			bfsColor(i);
	for ( int i = 0; i < nEdge; i ++ ) {
		if ( father[edge[i].u] == edge[i].v )
			swap(edge[i].u, edge[i].v);
	}

	for ( int i = 0; i < nEdge; i ++ ) 
		if ( father[edge[i].v] == edge[i].u ) {
			Node *x = node + edge[i].v;
			x->pre = node + edge[i].u;
		}
	//dealing with non-tree edges
	int errEdgeCnt = 0;
	for ( int i = 0; i < nEdge; i ++ )
		if ( father[edge[i].v] != edge[i].u ) {
			int u = edge[i].u, v = edge[i].v;
			if ( color[u] == color[v] )
				errEdgeCnt++;
		}
	if ( errEdgeCnt == 0 ) {
		for ( int i = 0; i < nEdge; i ++ )
			if ( father[edge[i].v] != edge[i].u ) 
				ans.pb(i);
	} else if ( errEdgeCnt == 1 ) {
		for ( int i = 0; i < nEdge; i ++ )
			if ( father[edge[i].v] != edge[i].u ) {
				int u = edge[i].u, v = edge[i].v;
				if ( color[u] == color[v] )
					ans.pb(i);
			}
	} else {}

	//dealing with tree edges
	for ( int i = 0; i < nEdge; i ++ )
		if ( father[edge[i].v] != edge[i].u ) {
			int u = edge[i].u, v = edge[i].v;
			if ( color[u] == color[v] )
				change(u, v, 1);
			else
				change(u, v, 0);
		}
	for ( int i = 0; i < nNode; i ++ )
		if ( father[i] != -1 ) {
			pair<int, int> res = askVal(i);
			if ( errEdgeCnt == 0 || (res.first == 0 && res.second == errEdgeCnt) )
				ans.pb(edgeIdx[make_pair(i,father[i])]);
		}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	foreach(it, ans)
		printf("%d ", (*it)+1);
}
