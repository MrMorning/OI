#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N_MAX = 105;
int mat[N_MAX][N_MAX];
bool state[N_MAX];
int n;
int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d", &n), n ) {
		memset(mat, 0, sizeof(mat));
		for ( int i = 0; i < n; i ++ )
			mat[i][i] = 1;
		for ( int i = 0; i < n - 1; i ++ ) {
			int a, b;
			scanf("%d%d", &a, &b);
			a --, b --;
			mat[a][b] = mat[b][a] = 1;
		}
		int ans = n;
		for ( int s = 0, lim = 1 << n; s < lim; s ++ ) {
			memset(state, 0, sizeof(state));
			int cnt = 0;
			for ( int i = 0; i < n; i ++ ) 
				if (s & (1 << i)) {
					cnt ++;
					for ( int j = 0; j < n; j ++ )
						if ( mat[i][j] )
							state[j] ^= 1;
				}
			bool suc = true;
			for ( int i = 0; i < n; i ++ )
				if ( state[i] == 0 ) {
					suc = false;
					break;
				}
			if ( suc )
				ans = min(ans, cnt);
		}
		printf("%d\n", ans);
	}
}
