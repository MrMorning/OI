#include <cstdio>
#include <vector>
#include <algorithm>
#define foreach(I, C) for ( __typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++ )
using namespace std;

const int V_MAX = 100010, E_MAX = 2 * V_MAX;
const int inf = 0x3f3f3f3f;

struct Edge {
	int to, len;
	bool on;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX];
int edge_cnt = 0;

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

template<typename T>
struct MonoQueue {
	pair<int, T> ele[V_MAX];
	int qh, qt;
	int size() {
		return qt - qh;
	}
	void clear() {
		qh = qt = 0;
	}
	void push(int i, const T &t) {
		while ( qh < qt && t > ele[qt - 1].second )
			qt --;
		ele[qt ++] = make_pair(i, t);
	}
	void refresh(int t) {
		while ( qh < qt && ele[qh].first < t )
			qh ++;
	}
	T get_max() {
		return ele[qh].second;
	}
};

struct Answer {
	int val, u, v;
} ans;

int average, l_bound, r_bound;
#define EVAL(x) ((x) >= average ? 1 : -1)

namespace find_root {
	int best_node, best_val, tot_size;
	int size[V_MAX];
	void calc_size(int x) {
		size[x] = 1;
		for ( Edge *e = begin[x]; e; e = e->next )
			if ( e->on ) {
				int y = e->to;
				e->inv->on = false;
				calc_size(y);
				e->inv->on = true;
				size[x] += size[y];
			}
	}
	void find(int x) {
		int val = tot_size - size[x];	
		for ( Edge *e = begin[x]; e; e = e->next )
			if ( e->on ) {
				int y = e->to;
				e->inv->on = false;
				find(y);
				e->inv->on = true;
				val = max(val, size[y]);
			}
		if ( val < best_val ) {
			best_val = val;
			best_node = x;
		}
	}
	int main(int x) {
		best_val = inf;
		calc_size(x);
		tot_size = size[x];
		find(x);
		return best_node;
	}
}

int dep[V_MAX];
void calc_dep(int x) {
	dep[x] = 0;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			calc_dep(y);
			e->inv->on = true;
			dep[x] = max(dep[x], dep[y] + 1);
		}
}

void calc_g(int x, int d, int val, pair<int, int> *g) {
	if ( g[d] < make_pair(val, x) )
		g[d] = make_pair(val, x);
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->on ) {
			int y = e->to;
			e->inv->on = false;
			calc_g(y, d + 1, val + EVAL(e->len), g);
			e->inv->on = true;
		}
}

void work(int x) {
	if ( ans.val >= 0 )
		return;
	int r = find_root::main(x);
	for ( Edge *e = begin[r]; e; e = e->next ) 
		if ( e->on ) {
			int s = e->to;
			e->inv->on = false;
			work(s);
			e->inv->on = true;
		}

	static vector<pair<int, Edge*> > son;
	son.clear();
	for ( Edge *e = begin[r]; e; e = e->next ) 
		if ( e->on ) {
			int s = e->to;
			e->inv->on = false;
			calc_dep(s);
			son.push_back(make_pair(dep[s] + 1, e));
			e->inv->on = true;
		}
	if ( son.size() == 0 )
		return;
	sort(son.begin(), son.end());

	static pair<int, int> f[V_MAX], g[V_MAX];
	
	for ( int i = 1; i <= son.back().first; i ++ )
		f[i].first = -inf;
	f[0].first = 0, f[0].second = r;
	int pre_dep = 0;

	static MonoQueue<pair<int, int> > MQ;

	foreach(it, son) {
		g[0].first = 0, g[0].second = r;
		for ( int i = 1; i <= it->first; i ++ )
			g[i].first = -inf;

		MQ.clear();
		int last = -1;
		int s = it->second->to;
		it->second->inv->on = false;
		calc_g(s, 1, EVAL(it->second->len), g);
		it->second->inv->on = true;

		for ( int l1 = it->first; l1 >= 0; l1 -- )
			if ( g[l1].first != -inf ) {
				int p = l_bound - l1, q = r_bound - l1;
				p = max(0, p);
				q = min(pre_dep, q);
				if ( p > q )
					continue;

				while ( last < q ) {
					last ++;
					MQ.push(last, f[last]);
				}
				MQ.refresh(p);
				if ( !MQ.size() )
					continue;
				pair<int, int> tp = MQ.get_max();
				if ( tp.first == -inf )
					continue;
				if ( tp.first + g[l1].first > ans.val ) {
					ans.val = tp.first + g[l1].first;
					ans.u = tp.second, ans.v = g[l1].second;
				}
			}
		for ( int i = 0; i <= it->first; i ++ )
			f[i] = max(f[i], g[i]);
		pre_dep = it->first;
	}
}

bool check(int mid) {
	average = mid;
	ans.val = -inf;
	work(1);
	return ans.val >= 0;
}

int n_node;
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n_node, &l_bound, &r_bound);
	int max_beauty = 0;
	for ( int i = 1; i < n_node; i ++ ) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add_edge(a, b, c);
		max_beauty = max(max_beauty, c);
	}
	int lb = 0, rb = max_beauty + 1;
	for ( int mid = (lb + rb) / 2;
			lb < rb - 1; mid = (lb + rb) / 2 ) 
		if ( check(mid) )
			lb = mid;
		else
			rb = mid;
	check(lb);
	printf("%d %d\n", ans.u, ans.v);
}
