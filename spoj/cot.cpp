#include <cstdio>
#include <algorithm>
using namespace std;
const int NODE_MAX = 100010, K_MAX = 20;

struct Edge {
	int to;
	Edge *next;
} edge[NODE_MAX * 2], *begin[NODE_MAX];

void addEdge(int u, int v) {
	static int freeCnt = 0;
	Edge *e = edge + freeCnt ++;
	e->to = v, e->next = begin[u], begin[u] = e;
}

struct Node {
	Node *ch[2];
	int sum;
	void update() {
		sum = ch[0]->sum + ch[1]->sum;
	}
} pool[NODE_MAX * K_MAX], *sgt[NODE_MAX];

int father[NODE_MAX], dep[NODE_MAX], pos[NODE_MAX], weight[NODE_MAX];
int seq[NODE_MAX * 2], seqCnt;
int axis[NODE_MAX], axisCnt;
int st[K_MAX][NODE_MAX * 2], log2[NODE_MAX * 2];

Node *alloc() {
	static int freePos = 0;
	return &pool[freePos ++];
}

Node *build(int l, int r) {
	Node *ret = alloc();
	if ( l != r ) {
		int mid = (l + r) / 2;
		ret->ch[0] = build(l, mid);
		ret->ch[1] = build(mid + 1, r);
	}
	return ret;
}

Node *add(Node *cur, int l, int r, int pos) {
	Node *ret = alloc();
	if ( l == r ) 
		ret->sum = cur->sum + 1;
	else {
		int mid = (l + r) / 2;
		if ( pos <= mid ) {
			ret->ch[1] = cur->ch[1];
			ret->ch[0] = add(cur->ch[0], l, mid, pos);
			ret->update();
		} else {
			ret->ch[0] = cur->ch[0];
			ret->ch[1] = add(cur->ch[1], mid + 1, r, pos);
			ret->update();
		}
	}
	return ret;
}

int ask(Node *u, Node *v, Node *p, int l, int r, int k, int it) {
	if ( l == r ) 
		return l;
	int mid = (l + r) / 2;
	int lval = u->ch[0]->sum + v->ch[0]->sum - 2 * p->ch[0]->sum + (it <= mid && it >= l);
	if ( k <= lval )
		return ask(u->ch[0], v->ch[0], p->ch[0], l, mid, k, it);
	else
		return ask(u->ch[1], v->ch[1], p->ch[1], mid + 1, r, k - lval, it);
}

void dfs(int root) { 
	static pair<int, Edge*> stk[NODE_MAX];
	int top = 0;
	sgt[0] = build(1, axisCnt);
	stk[top ++] = make_pair(root, begin[root]);
	seq[++ seqCnt] = root;
	pos[root] = seqCnt;
	dep[root] = 1;
	sgt[root] = add(sgt[0], 1, axisCnt, weight[root] + 1);

	while ( top ) {
		int u = stk[top - 1].first;
		Edge *&e = stk[top - 1].second;
		if ( e == NULL ) {
			if ( father[u] ) 
				seq[++ seqCnt] = father[u];
			top --;
		} else {
			int v = e->to;
			e = e->next;

			if ( v == father[u] )
				continue;
			father[v] = u;
			dep[v] = dep[u] + 1;
			seq[++ seqCnt] = v;
			pos[v] = seqCnt;
			stk[top ++] = make_pair(v, begin[v]);
			sgt[v] = add(sgt[u], 1, axisCnt, weight[v] + 1);
		}
	}
} 

void rmqInit() {
	for ( int k = 0; (1 << k) < 2 * NODE_MAX; k ++ ) 
		log2[1 << k] = k;
	for ( int i = 1; i < 2 * NODE_MAX; i ++ )
		if ( log2[i] == 0 )
			log2[i] = log2[i - 1];
	for ( int i = 1; i <= seqCnt; i ++ )
		st[0][i] = seq[i];
	for ( int k = 1; (1 << k) <= seqCnt; k ++ )
		for ( int i = 1; i <= seqCnt; i ++ ) {
			st[k][i] = st[k - 1][i];
			int t = (1 << (k - 1)) + i;
			if ( t <= seqCnt && dep[st[k - 1][t]] < dep[st[k][i]] )
				st[k][i] = st[k - 1][t];
		}
}

int lca(int u, int v) {
	int l = pos[u], r = pos[v];
	if ( l > r )
		swap(l, r);
	int k = log2[r - l + 1];
	int ret = st[k][l];
	int t = st[k][r - (1 << k) + 1];
	if ( dep[t] < dep[ret] )
		ret = t;
	return ret;
}

int main() {
	int N, M;
	scanf("%d%d", &N, &M);
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%d", &weight[i]);
		axis[axisCnt ++] = weight[i];
	}
	sort(axis, axis + axisCnt);
	axisCnt = unique(axis, axis + axisCnt) - axis;
	for ( int i = 1; i <= N; i ++ ) 
		weight[i] = lower_bound(axis, axis + axisCnt, weight[i]) - axis;
	for ( int i = 1; i < N; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(1);
	rmqInit();

	while ( M -- ) {
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		int p = lca(u, v);
		int ret = ask(sgt[u], sgt[v], sgt[p], 1, axisCnt, k, weight[p] + 1);
		printf("%d\n", axis[ret - 1]);
	}
}
