#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;
int have[111][111], f[111][2], rightmost[111], leftmost[111];

void solve() {
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		char str[111];
		scanf("%s", str + 1);
		for ( int j = 2; j <= m; j ++ ) 
			have[i][j] = str[j] == '*';
	}
	for ( int i = 1; i <= n; i ++ ) {
		rightmost[i] = 1, leftmost[i] = m;
		for ( int j = 2; j <= m; j ++ )
			if ( have[i][j] ) {
				rightmost[i] = max(rightmost[i], j);
				leftmost[i] = min(leftmost[i], j);
			}
	}
	f[1][0] = f[1][1] = 0;
	for ( int i = 2; i <= n + 1; i ++ ) {
		f[i][0] = f[i - 1][0] + 2 * (rightmost[i - 1] - 1) + 1;
		f[i][0] = min(f[i][0], f[i - 1][1] + 1 + m - 1);
		f[i][1] = f[i - 1][1] + 2 * (m - leftmost[i - 1]) + 1;
		f[i][1] = min(f[i][1], f[i - 1][0] + 1 + m - 1);
	}
	int res = min(f[n + 1][0] - 1, f[n + 1][1] - 1);
	printf("%d\n", res);
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for ( int t = 1; t <= TST; t ++ ) {
		printf("Case #%d: ", t);
		solve();
	}
}
