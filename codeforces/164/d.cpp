#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int kMod = 1000000009;
int n, h, f[2][32][32][32][32];

void upd(int &a, int b) {
	a = a+b;
	if ( a >= kMod ) a -= kMod;
}
int main() {
	freopen("t.in", "r", stdin);
	int n, h;
	scanf("%d%d", &n, &h);
	int cur = 1;
	f[cur][1][1][1][1] = 1;
	for ( int i = 1; i <= n; i ++, cur ^= 1 ) {
		memset(f[!cur], 0, sizeof(f[0]));
		for ( int j = 1; j <= h+1; j ++ )
			for ( int k = j; k <= h+1; k ++ )
				for ( int l = k; l <= h+1; l ++ )
					for ( int m = l; m <= h+1; m ++ ) 
						if ( f[cur][j][k][l][m] ) {
							int val = f[cur][j][k][l][m];
							if ( j != h+1 )
								upd(f[!cur][j==h+1?h+1:1][min(h+1,k+1)][min(h+1,l+1)][min(h+1,m+1)], val);
							else
								upd(f[!cur][h+1][h+1][h+1][h+1], val);

							if ( k != h+1 )
								upd(f[!cur][1][min(h+1,j+1)][min(h+1,l+1)][min(h+1,m+1)], val);
							else
								upd(f[!cur][min(h+1,j+1)][h+1][h+1][h+1], val);

							if ( l != h+1 )
								upd(f[!cur][1][min(h+1,j+1)][min(h+1,k+1)][min(h+1,m+1)], val);
							else
								upd(f[!cur][min(h+1,j+1)][min(h+1,k+1)][h+1][h+1], val);

							if ( m != h+1 )
								upd(f[!cur][1][min(h+1,j+1)][min(h+1,k+1)][min(h+1,l+1)], val);
							else
								upd(f[!cur][min(h+1,j+1)][min(h+1,k+1)][min(h+1,l+1)][h+1], val);
						}
	}
	int ans = 0;
	for ( int j = 1; j <= h; j ++ )
		for ( int k = j; k <= h+1; k ++ )
			for ( int l = k; l <= h+1; l ++ )
				for ( int m = l; m <= h+1; m ++ ) 
					upd(ans, f[cur][j][k][l][m]);
	printf("%d\n", ans);
}
