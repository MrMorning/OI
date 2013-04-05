#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int N_MAX = 10010;
const int inf = 0x3f3f3f3f;

struct Edge {
	int to, len;
	Edge *next, *inv;
	bool on;
} edge[2 * N_MAX], *begin[N_MAX];
int edge_cnt = 0;
int depth[N_MAX], size[N_MAX];
int seq[N_MAX], n_seq;
int upper, n_node;

Edge *make_edge(int u, int v, int w) {
	Edge *e = edge + edge_cnt ++;
	e->on = true;
	e->to = v, e->next = begin[u], e->len = w;
	return begin[u] = e;
}

void add_edge(int u, int v, int w) {
	Edge *e1 = make_edge(u, v, w),
		 *e2 = make_edge(v, u, w);
	e1->inv = e2, e2->inv = e1;
}

int best_val, best_node;
void find_root(int x, int tot) {
	size[x] = 1;
	int val = 0;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			find_root(y, tot);
			e->inv->on = true;
			val = max(val, size[y]);
			size[x] += size[y];
		}
	val = max(val, tot - size[x]);
	if ( val < best_val ) {
		best_val = val;
		best_node = x;
	}
}

void dfs(int x, Edge *te) {
	size[x] = 1;
	depth[x] = te ? depth[te->inv->to] + te->len : 0;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			dfs(y, e);
			e->inv->on = true;
			size[x] += size[y];
		}
}

void get_seq(int x) {
	seq[n_seq ++] = x;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			e->inv->on = false;
			get_seq(e->to);
			e->inv->on = true;
		}
}

bool cmp_depth(int i, int j) {
	return depth[i] < depth[j];
}

int work(int x) {
	int res = 0;
	dfs(x, NULL);
	int tot = size[x];
	best_val = inf;
	find_root(x, tot);
	int r = best_node;


	for ( Edge *e = begin[r]; e; e = e->next ) 
		if ( e->on ) {
			e->inv->on = false;
			res += work(e->to);
			e->inv->on = true;
		}
	dfs(r, NULL);
	static int over[N_MAX];
	int n_over = 0;
	for ( Edge *e = begin[r]; e; e = e->next ) 
		if ( e->on ) {
			e->inv->on = false;
			n_seq = 0;
			get_seq(e->to);
			e->inv->on = true;
			sort(seq, seq + n_seq, cmp_depth);
			if ( n_over != 0 ) {
				int i = 0, j = -1;
				while ( j + 1 < n_over && depth[over[j + 1]] + depth[seq[i]] <= upper )
					j ++;
				for ( ; i < n_seq; i ++ ) {
					while ( j >= 0 && depth[over[j]] + depth[seq[i]] > upper )
						j --;
					res += j + 1;
				}
			}
			static int arr[N_MAX];
			int n_arr = merge(over, over + n_over, seq, seq + n_seq, arr, cmp_depth) - arr;
			memcpy(over, arr, sizeof(int) * n_arr);
			n_over = n_arr;
		}
	for ( int i = 0; i < n_over; i ++ )
		if ( depth[over[i]] <= upper )
			res ++;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d%d", &n_node, &upper), n_node ) {
		edge_cnt = 0;
		memset(begin, 0, sizeof(Edge*) * n_node);
		for ( int i = 0; i < n_node - 1; i ++ ) {
			int a, b, l;
			scanf("%d%d%d", &a, &b, &l);
			a --, b --;
			add_edge(a, b, l);
		}
		printf("%d\n", work(0));
	}
}
