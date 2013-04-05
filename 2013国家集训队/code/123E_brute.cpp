#include <cstdio>
#include <cstring>
#include <vector>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kNMax = 100005;
int n;
vector<int> adj[kNMax];
double x[kNMax], y[kNMax], totX, totY;

double dfs(int cur, int pa, double acc) {
	double res = 0;
	foreach(it, adj[cur])
		if ( *it != pa ) {
			res += dfs(*it, cur, acc + y[cur]);
		}
	res += 1 - acc;
	return res;
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
	double res = 0;
	for ( int i = 1; i <= n; i ++ ) {
		res += (dfs(i, 0, 0)-1) * x[i];
	}
	printf("%.10lf\n", res);
}
