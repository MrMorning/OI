#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> pair_t;

const int CITY_MAX = 210;
const int ROAD_MAX = 10010;
const double EPS = 10e-6;

struct Road {
	int u, v, a, b;
	double key;
	bool operator< (const Road &t) const {
		return key < t.key;
	}
} road[ROAD_MAX];
int par[CITY_MAX];
int n, m;

int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
void merge(int u, int v) { par[find(u)] = find(v); }

pair_t calc_mst() {
	sort(road, road + m);
	for ( int i = 0; i < n; i ++ )
		par[i] = i;
	pair_t res = make_pair(0, 0);
	for ( int i = 0; i < m; i ++ ) {
		int u = road[i].u, v = road[i].v;
		if ( find(u) != find(v) ) {
			merge(u, v);
			res.first += road[i].a, res.second += road[i].b;
		}
	}
	return res;
}

pair_t get_min(const pair_t &a, const pair_t &b) {
	if ( a.first == -1 ) return b;
	if ( b.first == -1 ) return a;
	int t1 = a.first * a.second,
		t2 = b.first * b.second;
	if ( t1 != t2 )
		return t1 < t2 ? a : b;
	return min(a, b);
}

pair_t dfs(const pair_t &pl, const pair_t &pr) {
	if ( pl.first < pr.first || pl.second > pr.second )
		return make_pair(-1, -1);
	if ( pr.first == pl.first ) return pr;
	if ( pr.second == pl.second ) return pl;
	pair_t best = get_min(pl, pr);
	double k = (double)(pr.first- pl.first) / (pr.second - pl.second);
	for ( int i = 0; i < m; i ++ )
		road[i].key = road[i].a - k * road[i].b;
	pair_t tmp = calc_mst();
	double r = pl.first - pl.second * k;
	if ( (int)(k * tmp.second + r + EPS) <= tmp.first )
		return best;
	//if ( get_min(tmp, best) == best ) 
	//	return best;
	best = get_min(best, dfs(pl, tmp));
	best = get_min(best, dfs(tmp, pr));
	return best;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < m; i ++ ) 
		scanf("%d%d%d%d", &road[i].u, &road[i].v, &road[i].a, &road[i].b);
	for ( int i = 0; i < m; i ++ ) 
		road[i].key = road[i].a;
	pair_t tmp1 = calc_mst();
	for ( int i = 0; i < m; i ++ ) 
		road[i].key = road[i].b;
	pair_t tmp2 = calc_mst();
	pair_t res = dfs(tmp2, tmp1);
	printf("%d %d\n", res.first, res.second);
}
