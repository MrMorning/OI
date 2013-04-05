#include <cstdio>
#include <cassert>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
const int N_MAX = 1010;
int n, m;
ll w[N_MAX][N_MAX], s[N_MAX][N_MAX], f[N_MAX][N_MAX],
   g[N_MAX][N_MAX], h[N_MAX][N_MAX], d[N_MAX][N_MAX],
   u[N_MAX][N_MAX], tu[N_MAX][N_MAX], td[N_MAX][N_MAX], th[N_MAX][N_MAX];
ll get_sum(int x1, int y1, int x2, int y2) {
	if ( x1 > x2 || y1 > y2 )
		return 0LL;
	assert(x2 <= n && y2 <= m);
	return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		static char str[1111];	
		scanf("%s", str + 1);
		for ( int j = 1; j <= m; j ++ )
			w[i][j] = str[j] == '.';
	}
	for ( int i = 1; i <= n ;i ++ )
		for ( int j = 1; j <= m; j ++ )
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + w[i][j];

	for ( int i = 1; i <= n; i ++ ) 
		for ( int j = 1; j <= m; j ++ ) {
			th[i][j] = th[i][j - 1] + get_sum(i, 1, i, j - 1);
			if ( w[i][j - 1] == 0 )
				h[i][j] = j == 1 ? 0 : (h[i][j - 2] + get_sum(i, 1, i, j - 2) * 4);
			else
				h[i][j] = h[i][j - 1] + get_sum(i, 1, i, j - 1);
		}
	for ( int j = 1; j <= m; j ++ )
		for ( int i = 1; i <= n; i ++ ) {
			tu[i][j] = tu[i - 1][j] + get_sum(1, j, i - 1, j);
			if ( w[i - 1][j] == 0 )
				u[i][j] = i == 1 ? 0 : (u[i - 2][j] + get_sum(1, j, i - 2, j) * 4);
			else
				u[i][j] = u[i - 1][j] + get_sum(1, j, i - 1, j);
		}
	for ( int j = 1; j <= m; j ++ )
		for ( int i = n; i >= 1; i -- ) {
			td[i][j] = td[i + 1][j] + get_sum(i + 1, j, n, j);
			if ( w[i + 1][j] == 0 )
				d[i][j] = i == n ? 0 : (d[i + 2][j] + get_sum(i + 2, j, n, j) * 4);
			else
				d[i][j] = d[i + 1][j] + get_sum(i + 1, j, n, j);
		}
	for ( int i = 1; i <= n; i ++ ) 
		for ( int j = 1; j <= m; j ++ )
			f[i][j] = f[i - 1][j - 1] + get_sum(1, 1, i - 1, j - 1) * 2
				+ h[i][j] + u[i][j];
	for ( int i = n; i >= 1; i -- ) 
		for ( int j = 1; j <= m; j ++ )
			g[i][j] = g[i + 1][j - 1] + get_sum(i + 1, 1, n, j - 1) * 2
				+ h[i][j] + d[i][j];
	ll res = 0;
	for ( int i = 1; i <= n; i ++)
		for ( int j = 1; j <= m; j ++ )
			if ( w[i][j] ) {
				ll tmp = f[i - 1][j - 1] + get_sum(1, 1, i - 1, j - 1) * 2 + g[i + 1][j - 1] + get_sum(i + 1, 1, n, j - 1) * 2;
				tmp += h[i][j] + u[i][j];
				res += 2 * tmp;
			}
	long double ans = (long double)res / (get_sum(1, 1, n, m) * get_sum(1, 1, n, m));
	cout << ans;
}
