#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
using namespace std;

int n, m;
vector<int> c[100010];
pair<int, int> rail[100010];
int nRail;
bool mark[100010];

void noSol() {
	puts("No solution");
	exit(0);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	if ( n > m ) noSol();
	int nc = m-n+1;
	if ( n < 1+2*nc ) noSol();
	int tot = 1, pre = 1;
	for ( int i = 1; i <= nc; i ++ ) {
		c[i].pb(pre);
		for ( int k = 1; k <= 2; k ++ )
			c[i].pb(++tot);
		mark[c[i][1]] = true;
		pre = tot;
	}
	mark[1] = true; mark[tot] = true;
	if ( n < tot ) noSol();
	n -= tot;
	for ( int i = 1; n > 0 && i <= nc; i ++ ) {
		int need = min(7, n);
		n -= need;
		for ( int t = 0; t < need; t ++ ) {
			c[i].pb(++tot);
			mark[tot] = true;
		}
	}
	if ( n > 0 ) {
		int lim = tot;
		for ( int i = 1; n > 0 && i <= lim; i ++ )
			if ( mark[i] ) {
				rail[nRail++] = mp(i, ++tot);
				n--;
			}
	}
	if ( n > 0 ) noSol();
	printf("%d\n", nc);
	for ( int i = 1; i <= nc; i ++ ) {
		int sz = c[i].size();
		printf("%d", sz);
		for ( int k = 0; k < sz; k ++ )
			printf(" %d", c[i][k]);
		printf("\n");
	}
	printf("%d\n", nRail);
	for ( int i = 0; i < nRail; i ++ )
		printf("%d %d\n", rail[i].first, rail[i].second);
}
