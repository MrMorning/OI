#include <cassert>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int V_MAX = 100010;
const int E_MAX = 2 * V_MAX;
const int inf = 0x3f3f3f3f;

struct Edge {
	int to, len, cost, id;
	Edge *next, *inv;
	bool on;
} edge[E_MAX], *begin[V_MAX];
int edge_cnt = 0;
int n_node;
vector<Edge*> dia;
vector<int> res_vec;
int res_val;
int dist[V_MAX];
Edge *prev[V_MAX];

bool done[V_MAX];
int memo[V_MAX], dep[V_MAX];

Edge *make_edge(int id, int u, int v, int l, int c) {
	Edge *e = edge + edge_cnt ++;
	e->on = true;
	e->id = id;
	e->to = v, e->next = begin[u], e->cost = c, e->len = l;
	return begin[u] = e;
}

void add_edge(int id, int u, int v, int l, int c) {
	Edge *e1 = make_edge(id, u, v, l, c),
		 *e2 = make_edge(id, v, u, l, c);
	e1->inv = e2; e2->inv = e1;
}

void get_dist(int x) {
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			int y = e->to;
			dist[y] = dist[x] + e->len;
			prev[y] = e;
			e->inv->on = false;
			get_dist(y);
			e->inv->on = true;
		}
}

void find_diameter() {
	dist[1] = 0;
	get_dist(1);
	int max_idx = 0;
	for ( int i = 1; i <= n_node; i ++ )
		if ( max_idx == 0 || dist[i] > dist[max_idx] )
			max_idx = i;
	dist[max_idx] = 0;
	int root = max_idx;
	memset(prev, 0, sizeof(prev));
	get_dist(root);
	max_idx = 0;
	for ( int i = 1; i <= n_node; i ++ )
		if ( max_idx == 0 || dist[i] > dist[max_idx] )
			max_idx = i;
	for ( Edge *e = prev[max_idx]; e; e = prev[e->inv->to] )
		dia.push_back(e->inv);
}

int dp(int x) {
	if ( done[x] )
		return memo[x];
	done[x] = true;
	int &res = memo[x] = 0;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			e->inv->on = false;
			dp(e->to);
			e->inv->on = true;
		}
	dep[x] = 0;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			e->inv->on = false;
			dep[x] = max(dep[x], dep[e->to] + e->len);
			e->inv->on = true;
		}
	bool inside = false;
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			if ( dep[e->to] + e->len == dep[x] ) {
				inside = true;
				e->inv->on = false;
				res += min(e->cost, dp(e->to));
				e->inv->on = true;
			}
		}
	if ( !inside )
		res = inf;
	return res;
}

void output(vector<int> &res, int x) {
	for ( Edge *e = begin[x]; e; e = e->next ) 
		if ( e->on ) {
			if ( dep[e->to] + e->len == dep[x] ) {
				e->inv->on = false;
				if ( e->cost < dp(e->to) )
					res.push_back(e->id);
				else
					output(res, e->to);
				e->inv->on = true;
			}
		}
}

void work() {
	int tot_len = 0;
	for ( vector<Edge*>::iterator it = dia.begin();
			it != dia.end(); it ++ )
		tot_len += (*it)->len;
	int acc = 0;
	int mid_point = 0;
	Edge *mid_edge = NULL;
	for ( vector<Edge*>::iterator it = dia.begin();
			it != dia.end(); it ++ ) {
		if ( acc + (*it)->len == tot_len / 2 ) {
			mid_point = (*it)->to;
			break;
		}
		if ( acc + (*it)->len > tot_len / 2 ) {
			mid_edge = (*it);
			break;
		}
		acc += (*it)->len;
	}
	if ( mid_point != 0 ) {
		dp(mid_point);
		res_val = 0;
		int max_val = 0;
		for ( Edge *e = begin[mid_point]; e; e = e->next ) {
			int s = e->to;
			if ( dep[mid_point] != dep[s] + e->len )
				continue;
			e->inv->on = false;
			int fee = min(dp(s) == 0 ? inf : dp(s), e->cost);
			res_val += fee;
			max_val = max(max_val, fee);
			e->inv->on = true;
		}
		res_val -= max_val;
		for ( Edge *e = begin[mid_point]; e; e = e->next ) {
			int s = e->to;
			if ( dep[mid_point] != dep[s] + e->len )
				continue;
			e->inv->on = false;
			int fee = min(dp(s) == 0 ? inf : dp(s), e->cost);
			if ( fee == max_val ) 
				max_val = 0;
			else {
				if ( fee == e->cost )
					res_vec.push_back(e->id);
				else
					output(res_vec, s);
			}
			e->inv->on = true;
		}
	} else {
		res_val = mid_edge->cost;
		res_vec.push_back(mid_edge->id);
		int u = mid_edge->to, v = mid_edge->inv->to;
		mid_edge->on = mid_edge->inv->on = false;
		if ( dp(u) < res_val ) {
			res_val = dp(u);
			res_vec.clear();
			output(res_vec, u);
		}
		if ( dp(v) < res_val ) {
			res_val = dp(v);
			res_vec.clear();
			output(res_vec, v);
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n_node);
	for ( int i = 0; i < n_node - 1; i ++ ) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		c *= 2; //avoid float
		add_edge(i + 1, a, b, c, d);
	}
	find_diameter();
	work();
	printf("%d\n", res_val);
	printf("%d\n", (int)res_vec.size());
	for ( vector<int>::iterator it = res_vec.begin();
			it != res_vec.end(); it ++ )
		printf("%d ", *it);
}
