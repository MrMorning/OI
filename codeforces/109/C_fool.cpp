#include <cstdio>
#include <set>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;
const int N_MAX = 1000010;
int n, m;
set<int> edge[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < m; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		u --, v --;
		edge[u].insert(v);
		edge[v].insert(u);
	}
	ll ans = 0;
	for ( int i = 0; i < n; i ++ )
		for ( int j = i + 1; j < n; j ++ ) {
			bool fail = false;
			for ( int k = 0; k < n; k ++ )
				if ( i != k && j != k ) {
					bool b1 = edge[k].lower_bound(i) != edge[k].end()
						&& *edge[k].lower_bound(i) == i ;
					bool b2 = edge[k].lower_bound(j) != edge[k].end()
						&& *edge[k].lower_bound(j) == j ;
					if ( b1 != b2 )
						fail = true;
				}
			ans += !fail;
		}
	cout << ans;

	return 0;
	for ( int i = 0; i < n; i ++ ) {
		int dgr = edge[i].size();
		if ( dgr != n - 1 )
			continue;
		if ( (ll)(dgr - 1) * (dgr - 2) > 2 * m )
			continue;
		static vector<int> adj;
		adj.clear();
		for ( set<int>::iterator it = edge[i].begin();
				it != edge[i].end(); it ++ )
			adj.push_back(*it);
		int sz = adj.size();
		for ( int p = 0; p < sz; p ++ ) {
			int u = adj[p];
			if ( (int)edge[u].size() != dgr )
				continue;
			bool fail = false;
			for ( int q = 0; q < sz; q ++ )
				if ( p != q ) {
					int v = adj[q];
					if ( edge[u].lower_bound(v) == edge[u].end() ) {
						fail = true;
						break;
					}
				}
			if ( !fail )
				ans ++;
		}
	}
	ans /= 2;

	int zero_cnt = 0;
	for ( int i = 0; i < n; i ++ )
		if ( !edge[i].size() )
			zero_cnt ++;
	ans += (ll)zero_cnt * (zero_cnt - 1) / 2;
	static vector<int> vec;
	for ( int i = 0; i < n; i ++ )
		if ( n > 2 && (int)edge[i].size() == n - 2 )
			vec.push_back(i);
	for ( int i = 0, sz = vec.size(); i < sz; i ++ )
		for ( int j = i + 1; j < sz; j ++ ) {
			int u = vec[i], v = vec[j];
			if ( edge[u].lower_bound(v) == edge[u].end() )
				ans ++;
		}
	cout << ans << '\n';
}
