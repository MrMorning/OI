#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int VERT_MAX = 100010, EDGE_MAX =200010;
const int LOG_MAX = 18;
const int inf = 0x3f3f3f3f;

typedef pair<int, int> pair_t;

struct Edge {
	Edge *next;
	int to, cost;
} edge[EDGE_MAX * 2], *begin[VERT_MAX];
int edge_cnt = 0;

void add_edge(int u, int v, int c) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], e->cost = c;
	begin[u] = e;
}

struct Node {
	int key, tag, dist;
	pair_t info;
	Node *ch[2];
	void push_down(); 
	void add_val(int);
} node[2 * EDGE_MAX], *null;

int free_pos;

void Node::push_down() {
	if ( !tag ) return;
	for ( int t = 0; t < 2; t ++ )
		if ( ch[t] != null )
			ch[t]->key += tag;
	tag = 0;
}
void Node::add_val(int val) {
	key += val;
	tag += val;
}

Node *alloc(int _key, pair_t _info) {
	Node *x = node + free_pos ++;
	x->key = _key, x->info = _info;
	x->tag = x->dist = 0;
	x->ch[0] = x->ch[1] = null;
	return x;
}

Node *merge(Node *a, Node *b) {
	if ( a == null ) return b;
	if ( b == null ) return a;
	if ( a->key > b->key )
		swap(a, b);
	a->push_down();
	a->ch[1] = merge(a->ch[1], b);
	if ( a->ch[0]->dist < a->ch[1]->dist )
		swap(a->ch[0], a->ch[1]);
	a->dist = a->ch[1]->dist + 1;
	return a;
}

void insert(Node *&a, int _key, pair_t _info) {
	a = merge(a, alloc(_key, _info));
}
priority_queue<pair_t, vector<pair_t>, greater<pair_t> > PQ;
int min_dist[VERT_MAX];
pair_t pre[VERT_MAX];

void dijkstra() {
	memset(min_dist, 0x3f, sizeof(min_dist));
	min_dist[1] = 0;
	PQ.push(make_pair(0, 1));
	while ( !PQ.empty() ) {
		pair_t p = PQ.top(); PQ.pop();
		int u = p.second;
		if ( min_dist[u] != p.first )
			continue;
		for ( Edge *e = begin[u]; e; e = e->next ) {
			int v = e->to;
			if ( min_dist[v] > min_dist[u] + e->cost ) {
				min_dist[v] = min_dist[u] + e->cost;
				pre[v] = make_pair(u, e->cost);
				PQ.push(make_pair(min_dist[v], v));
			}
		}
	}
}

int nvt, ned;
vector<pair_t> son[VERT_MAX];

void build_tree() {
	for ( int i = 1; i <= nvt; i ++ )
		if ( pre[i].first ) 
			son[pre[i].first].push_back(make_pair(i, pre[i].second));
}

int seq[VERT_MAX * 2], pos[VERT_MAX], seq_len;
int depth[VERT_MAX];

void get_dfs_seq(int x, int dep) {
	seq[++ seq_len] = x;
	pos[x] = seq_len;
	depth[x] = dep;
	for ( int i = 0, sz = son[x].size(); i < sz; i ++ ) {
		int y = son[x][i].first;
		get_dfs_seq(y, dep + 1);
		seq[++ seq_len] = x;
	}
}

int st[LOG_MAX][VERT_MAX];
int log2[VERT_MAX * 2];
void init_st() {
	get_dfs_seq(1, 0);
	for ( int i = 0; (1 << i) <= seq_len; i ++ )
		log2[1 << i] = i;
	for ( int i = 1; i <= seq_len; i ++ )
		if ( !log2[i] )
			log2[i] = log2[i - 1];
	for ( int x = 1; x <= seq_len; x ++ )
		st[0][x] = seq[x];
	for ( int i = 1; (1 << i) <= seq_len; i ++ )
		for ( int j = 1; j <= seq_len; j ++ ) {
			st[i][j] = st[i - 1][j];
			int step = 1 << (i - 1);
			if ( j + step <= seq_len
					&& depth[st[i - 1][j + step]] < depth[st[i][j]])
				st[i][j] = st[i - 1][j + step];
		}
}

int get_lca(int x, int y) {
	int l = pos[x], r = pos[y];
	if ( l > r ) swap(l, r);
	int t = log2[r - l + 1];
	int res = st[t][l];
	if ( depth[st[t][r - (1 << t) + 1]] < depth[res] )
		res = st[t][r - (1 << t) + 1];
	return res;
}

Node *heap[VERT_MAX];
int ans[VERT_MAX];

void work(int x) {
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		insert(heap[x], min_dist[y] + e->cost, 
				make_pair(x, y));
	}
	for ( int i = 0, sz = son[x].size(); i < sz; i ++ ) {
		int y = son[x][i].first;
		work(y);
		heap[y]->add_val(son[x][i].second);
		heap[x] = merge(heap[x], heap[y]);
	}

	while ( 1 ) {
		if ( heap[x] == null ) {
			ans[x] = -1;
			break;
		}
		int a = heap[x]->info.first,
			b = heap[x]->info.second,
			w = heap[x]->key;
		if ( get_lca(x, get_lca(a, b)) == x
				|| ( a == x && b == pre[x].first)
				|| ( b == x && a == pre[x].first) ) {
			heap[x] = merge(heap[x]->ch[0], heap[x]->ch[1]);
		} else {
			ans[x] = w;
			break;
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	null = alloc(inf, make_pair(-1, -1));
	null->dist = -1;
	scanf("%d%d", &nvt, &ned);
	while ( ned -- ) {
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		add_edge(a, b, t);
		add_edge(b, a, t);
	} 
	dijkstra();
	build_tree();
	init_st();
	for ( int i = 1; i <= nvt; i ++ )
		heap[i] = null;
	work(1);
	for ( int i = 2; i <= nvt; i ++ )
		printf("%d\n", ans[i]);
}
