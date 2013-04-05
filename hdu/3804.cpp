#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 100010;
#define ADD 0
#define ASK 1

struct Edge {
	int to;
	Edge *next;
} edge[N_MAX * 2], *begin[N_MAX];
int edge_cnt = 0;

void add_edge(int u, int v) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], begin[u] = e;
}

struct Node {
	int start, end;
} node[N_MAX];

struct Event {
	int u, v, id, key, type;
	bool operator< (const Event &t) const {
		return key < t.key || (key == t.key && type < t.type);
	}
} event[2 * N_MAX];
int seq_cnt = 0, pre[N_MAX];
int tag[4 * N_MAX];
int n_node, n_query, ans[N_MAX];

void dfs(int x) {
	seq_cnt ++;
	node[x].start = seq_cnt - 1;
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( y != pre[x] ) {
			pre[y] = x;
			dfs(y);
		}
	}
	node[x].end = seq_cnt - 1;
}

void init() {
	pre[0] = -1;
	dfs(0);
}

void cover(int i, int l, int r, int ql, int qr, int val) {
	if ( l > qr || r < ql )
		return;
	if ( ql <= l && r <= qr )
		tag[i] = val;
	else {
		int mid = (l + r) / 2;
		cover(i * 2, l, mid, ql, qr, val);
		cover(i * 2 + 1, mid + 1, r, ql, qr, val);
	}
}

int ask_max(int pos) {
	int c = 1, cl = 0, cr = n_node - 1;
	int res = -1;
	while ( 1 ) {
		res = max(res,  tag[c]);
		if ( cl == cr )
			break;
		int mid = (cl + cr) / 2;
		if ( pos <= mid ) 
			c *= 2, cr = mid;
		else
			c = c * 2 + 1, cl = mid + 1;
	}
	return res;
}

int main() {
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		edge_cnt = seq_cnt = 0;
		memset(begin, 0, sizeof(begin));
		scanf("%d", &n_node);
		for ( int i = 0; i < n_node - 1; i ++ ) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u --, v --;
			add_edge(u, v);
			add_edge(v, u);
			event[i].type = ADD;
			event[i].key = w;
			event[i].u = u, event[i].v = v;
		}
		int event_cnt = n_node - 1;
		init();
		memset(tag, -1, sizeof(tag));
		scanf("%d", &n_query);
		for ( int i = 0; i < n_query; i ++ ) {
			int id, lim;
			scanf("%d%d", &id, &lim);
			id --;
			event[event_cnt].type = ASK;
			event[event_cnt].key = lim;
			event[event_cnt].u = id;
			event[event_cnt].v = i;
			event_cnt ++;
		}
		sort(event, event + event_cnt);
		for ( int i = 0; i < event_cnt; i ++ ) {
			if ( event[i].type == ADD ) {
				int u = event[i].u, v = event[i].v, w = event[i].key;
				if ( pre[v] == u ) 
					swap(u, v);
				cover(1, 0, n_node - 1, node[u].start, node[u].end, w);
			} else 
				ans[event[i].v] = ask_max(node[event[i].u].start);
		}

		for ( int i = 0; i < n_query; i ++ )
			printf("%d\n", ans[i]);
	}
}
