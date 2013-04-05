#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;

const int inf = 0x3f3f3f3f;

void upd(int &x, int y) {
	x = min(x, y);
}

int N, S[1010], X[1010];
struct F {
	int ele[16];
	int& operator[] (int i) {
		return ele[i + 8];
	}
} f[1010][1 << 8];

void solve() {

	scanf("%d", &N);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d%d", &S[i], &X[i]);

	memset(f, 0x3f, sizeof(f));
	for ( int d = 0; d < 8; d ++ )
		f[1][1 << d][d] = 0;
	for ( int i = 1; i <= N; i ++ ) 
		for ( int j = 0, lim = 1 << 8; j < lim; j ++ ) 
			for ( int d = -8; d <= 7; d ++ ) 
				if ( f[i][j][d] != inf ) {
					if ( j & 1 ) {
						assert(d != -8);
						upd(f[i + 1][j >> 1][d - 1], f[i][j][d]);
						continue;
					}
					int m = i - 1;
					for ( int t = 0; t < 8 && i + t <= N; t ++ )
						if ( j & (1 << t) )
							m = max(m, i + t);
					for ( int t = 0; t < 8 && i + t <= N; t ++ )
						if ( !(j & (1 << t)) ) 
							if ( i + t + X[i + t] >= m )
								upd(f[i][j | (1 << t)][t], f[i][j][d] + (S[i + t] ^ S[i + d]));	
				}
	int res = inf;
	for ( int d = -8; d <= 0; d ++ )
		upd(res, f[N][1][d]);
	printf("%d\n", res);
}

int main() {
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
