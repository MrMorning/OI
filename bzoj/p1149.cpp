#include <cstdio>
#include <algorithm>
using namespace std;
int n, lc[111111], rc[111111], f[111111][2]; 
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) 
		scanf("%d%d", &lc[i], &rc[i]);

	int ans = 0;
	for ( int i = n; i >= 1; i -- ) {
		f[i][0] = min(lc[i] == -1 ? 1 : f[lc[i]][0] + 1, rc[i] == -1 ? 1 : f[rc[i]][0] + 1);
		f[i][1] = max(lc[i] == -1 ? 1 : f[lc[i]][1] + 1, rc[i] == -1 ? 1 : f[rc[i]][1] + 1);
		if ( f[i][1] - f[i][0] > 1 ) {
			puts("-1");
			return 0;
		} 
		if ( lc[i] != -1 && rc[i] != -1 && f[lc[i]][0] != f[lc[i]][1] && f[rc[i]][0] != f[rc[i]][1] ) {
			puts("-1");
			return 0;
		}
		if ( f[lc[i]][0] < f[rc[i]][1] )
			ans ++;
	}

	printf("%d\n", ans);
}
