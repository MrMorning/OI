#include <cstdio>
#include <algorithm>
using namespace std;

int f[201][201][201], g[40011];
int dis[40000], n_dis;
int mat[201][201];
int n, m;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			scanf("%d", &mat[i][j]);
			dis[n_dis ++] = mat[i][j];
		}
	sort(dis, dis + n_dis);
	n_dis = unique(dis, dis + n_dis) - dis;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) 
			mat[i][j] = lower_bound(dis, dis + n_dis, mat[i][j]) - dis;
	if ( n_dis <= 200 ) {
		for ( int i = 1; i <= n; i ++ )
			for ( int j = 1; j <= m; j ++ )
				for ( int k = 0; k < n_dis; k ++ ) {
					f[i][j][k] = f[i - 1][j][k] + f[i][j - 1][k] - f[i - 1][j - 1][k];
					if ( mat[i][j] == k )
						f[i][j][k] ++;
				}
		int q;
		scanf("%d", &q);
		while ( q -- ) {
			int x1, x2, y1, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if ( x1 > x2 )
				swap(x1, x2);
			if ( y1 > y2 )
				swap(y1, y2);
			int res = 0;
			for ( int k = 0; k < n_dis; k ++ ) {
				int cnt = f[x2][y2][k];
				cnt -= f[x1 - 1][y2][k];
				cnt -= f[x2][y1 - 1][k];
				cnt += f[x1 - 1][y1 - 1][k];
				res += cnt * cnt;
			}
			printf("%d\n", res);
		}
	} else {
		int q;
		scanf("%d", &q);
		while ( q -- ) {
			static int arr[201];
			static bool vis[201];
			int x1, x2, y1, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if ( x1 > x2 )
				swap(x1, x2);
			if ( y1 > y2 )
				swap(y1, y2);
			int n_arr = 0;
			for ( int i = x1; i <= x2; i ++ )
				for ( int j = y1; j <= y2; j ++ ) {
					g[mat[i][j]] = 0;
					if ( !vis[mat[i][j]] ) {
						arr[n_arr ++] = mat[i][j];
						vis[mat[i][j]] = true;
					}
				}
			int res = 0;
			for ( int i = x1; i <= x2; i ++ )
				for ( int j = y1; j <= y2; j ++ ) {
					res += g[mat[i][j]];
					g[mat[i][j]] ++;
					vis[mat[i][j]] = false;
				}
			int same = 0;
			for ( int i = 0; i < n_arr; i ++ )
				same += g[arr[i]];
			printf("%d\n", res * 2 + same);
		}
	}
}
