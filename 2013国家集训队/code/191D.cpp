#include <cstdio>
#include <vector>
#define pb(x) push_back(x)
using namespace std;
int n, m;
vector<int> adj[100010];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < m; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b); adj[b].pb(a);
	}
	int ans = 0;
	for ( int i = 1; i <= n; i ++ ) 
		ans += adj[i].size()&1;
	ans /= 2;
	for ( int i = 1; i <= n; i ++ )
		if ( adj[i].size() == 2 ) {
			int x = adj[i][0], y = adj[i][1];
			if ( x == y ) { 
				adj[x].clear();
				ans++;
				continue;
			}
			adj[x][i == adj[x][1]] = y;
			adj[y][i == adj[y][1]] = x;
		}
	printf("%d %d\n", ans, m);
}
