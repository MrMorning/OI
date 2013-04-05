#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N_MAX = 105;
int mat[N_MAX][N_MAX];

void elim(int mat[N_MAX][N_MAX], int n, int m) {
	int j = 1;
	for ( int i = 1; i < m; i ++ ) {
		int p;
		for ( p = j; p <= n; p ++ )
			if ( mat[p][i] != 0 )
				break;
		if ( p == n + 1 )
			continue;
		for ( int k = 1; k <= m; k ++ )
			swap(mat[j][k], mat[p][k]);
		for ( p = 1; p <= n; p ++ )
			if ( p != j && mat[p][i] ) {
				for ( int k = 1; k <= m; k ++ )
					mat[p][k] ^= mat[j][k];
			}
		j ++;
	}
}

int n;
int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d", &n), n ) {
		memset(mat, 0, sizeof(mat));
		for ( int i = 1; i <= n; i ++ ) 
			mat[i][i] = mat[i][n + 1] = 1;
		for ( int i = 0; i < n - 1; i ++ ) {
			int a, b;
			scanf("%d%d", &a, &b);
			mat[a][b] = mat[b][a] = 1;
		}
		elim(mat, n, n + 1);
		int ans = 0;
		for ( int i = 1; i <= n; i ++ ) {
			bool all_zero = true;
			for ( int j = 1; j <= n + 1; j ++ )
				if ( mat[i][j] != 0 )
					all_zero = false;
			if ( all_zero )
				continue;
			ans += mat[i][n + 1];
		}
		for ( int i = 1; i <= n; i ++ , puts(""))
			for ( int j = 1; j <= n + 1; j ++ )
				fprintf(stderr, "%d ", mat[i][j]);
		printf("%d\n", ans);
	}
}
