#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int V_MAX = 200010, E_MAX = 2 * V_MAX;

struct Edge;

struct Element {
	int key, id;
	Edge *e;
	Element(){}
	Element(int _key, int _id, Edge* _e):
		key(_key), id(_id), e(_e){}
	bool operator< (const Element &t) const {
		return key < t.key;
	}
};

struct Edge {
	int to, len;
	bool on;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX];
int edge_cnt = 0;
bool is_black[V_MAX];
int size[V_MAX], dep[V_MAX];
int best_val, best_node;
int n_node, upper, n_crowd;

Edge *make_edge(int u, int v, int w) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], e->len = w;
	e->on = true;
	return begin[u] = e;
}

void add_edge(int u, int v, int w) {
	Edge *e1 = make_edge(u, v, w),
		 *e2 = make_edge(v, u, w);
	e1->inv = e2, e2->inv = e1;
}

void calc_size(int x) {
	size[x] = 1;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			calc_size(y);
			size[x] += size[y];
			e->inv->on = true;
		}
}

void find_root(int x, int tot) {
	size[x] = 1;
	int val = 0;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			find_root(y, tot);
			val = max(val, size[y]);
			size[x] += size[y];
			e->inv->on = true;
		}
	val = max(val, tot - size[x]);
	if ( val < best_val ) {
		best_val = val;
		best_node = x;
	}
}

void calc_dep(int x) {
	dep[x] = is_black[x];
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			calc_dep(y);
			dep[x] = max(dep[x], dep[y] + is_black[x]);
			e->inv->on = true;
		}
}

void calc_g(int x, int acc, int black_cnt, int *res) {
	black_cnt += is_black[x];
	res[black_cnt] = max(res[black_cnt], acc);
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			calc_g(y, acc + e->len, black_cnt, res);
			e->inv->on = true;
		}
}

int work(int x) {
	int res = 0;
	calc_size(x);
	int tot = size[x];
	best_val = n_node + 1;
	find_root(x, tot);
	int r = best_node;

	for ( Edge *e = begin[r]; e; e = e->next )
		if ( e->on ) {
			e->inv->on = false;
			res = max(res, work(e->to));
			e->inv->on = true;
		}

	static int g[V_MAX], g2[V_MAX];
	static Element arr[V_MAX];
	int n_arr = 0;
	for ( Edge *e = begin[r]; e; e = e->next )
		if ( e->on ) {
			e->inv->on = false;
			calc_dep(e->to);
			arr[n_arr ++] = Element(dep[e->to], e->to, e);
			e->inv->on = true;
		}
	sort(arr, arr + n_arr);
	int n_g = -1;
	for ( int i = 0; i < n_arr; i ++ ) {
		int s = arr[i].id;
		memset(g2, 0, sizeof(int) * (arr[i].key + 1));

		arr[i].e->inv->on = false;
		calc_g(s, arr[i].e->len, 0, g2);
		arr[i].e->inv->on = true;
		for ( int k = 1; k <= arr[i].key; k ++ )
			g2[k] = max(g2[k - 1], g2[k]);

		res = max(res, upper - is_black[r] >= 0 ? g2[min(upper - is_black[r], arr[i].key)] : 0);
		for ( int k = 0; k <= arr[i].key; k ++ ) {
			int t = min(upper - k - is_black[r], n_g);
			if ( t >= 0 )
				res = max(res, g2[k] + g[t]);
		}

		if ( n_g >= 0 )
			for ( int k = n_g + 1; k <= arr[i].key; k ++ )
				g[k] = g[n_g];
		else
			for ( int k = n_g + 1; k <= arr[i].key; k ++ )
				g[k] = 0;
		for ( int k = 0; k <= arr[i].key; k ++ ) 
			g[k] = max(g[k], g2[k]);
		n_g = arr[i].key;
	}
	return res;
}

int main() {
	scanf("%d%d%d", &n_node, &upper, &n_crowd);
	for ( int i = 0; i < n_crowd; i ++ ) {
		int x;
		scanf("%d", &x);
		x --;
		is_black[x] = true;
	}
	for ( int i = 0; i < n_node - 1; i ++ ) {
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		a --, b --;
		add_edge(a, b, w);
	}
	printf("%d\n", work(0));
}
