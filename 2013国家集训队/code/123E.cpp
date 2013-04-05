#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kNMax = 100005;
int n;
vector<int> adj[kNMax];
long double x[kNMax], y[kNMax], totX, totY;
int sz[kNMax];

void build(int cur, int pa) {
	sz[cur] = 1;
	foreach(it, adj[cur])
		if ( *it != pa ) {
			build(*it, cur);
			sz[cur] += sz[*it];
		}
}

long double res;
void dfs(int cur, int pa, long double ans) {
	res += (n-ans-1)*x[cur];
	foreach(it, adj[cur])
		if ( *it != pa ) {
			int nxt = *it;
			int preCur = sz[cur],
				preNxt = sz[nxt];
			sz[cur] = n-sz[nxt];
			sz[nxt] = n;
			dfs(nxt, cur, ans+(sz[cur]-preCur)*y[cur]+(sz[nxt]-preNxt)*y[nxt]);
			sz[cur] = preCur;
			sz[nxt] = preNxt;
		}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i < n; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for ( int i = 1; i <= n; i ++ ) {
		int xx, yy;
		scanf("%d%d", &xx, &yy);
		x[i] = xx, y[i] = yy;
		totX += x[i], totY += y[i];
	}
	for ( int i = 1; i <= n; i ++ )
		x[i] /= totX, y[i] /= totY;
	build(1, 0);
	long double initAns = 0;
	for ( int i = 1; i <= n; i ++ )
		initAns += (sz[i]-1)*y[i];
	dfs(1, 0, initAns);
	cout << setprecision(15) << setiosflags(ios::fixed) << res;
}
