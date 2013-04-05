#include <cstdio>
#include <cassert>
#include <cstring>
typedef unsigned int uint;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

uint f[19][19][55][37];
uint bino[37][37];
uint pow9[37], pow10[37];

inline void upd(uint &a, uint b) {
	a += b;
}

void prework() {
	bino[0][0] = 1;
	for ( int i = 1; i <= 36; i ++ ) {
		bino[i][0] = 1;
		for ( int j = 1; j <= i; j ++ )
			bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
	}

	f[0][0][0][0] = 1;
	for ( int i = 0; i <= 18; i ++ )
		for ( int j = 0; j <= 0; j ++ )
			for ( int k = 0; k <= 54; k ++ )
				for ( int l = 0; l <= 36; l ++ )
					if ( f[i][j][k][l] ) {
						if ( j == 0 && i < 18 ) {
							assert(k+3<=54&&l+2<=36);
							upd(f[i+1][0][k][l], f[i][j][k][l]);
							upd(f[i+1][0][k+1][l], f[i][j][k][l]);
							upd(f[i+1][0][k][l+1], f[i][j][k][l]);
							upd(f[i+1][0][k+2][l], f[i][j][k][l]);
							upd(f[i+1][0][k+1][l+1], f[i][j][k][l]);
							upd(f[i+1][0][k+3][l], f[i][j][k][l]);
							upd(f[i+1][0][k][l+2], f[i][j][k][l]);
						}
					}
	for ( int i = 0; i <= 18; i ++ )
		for ( int j = 0; j <= 18; j ++ )
			for ( int k = 0; k <= 54; k ++ )
				for ( int l = 0; l <= 36; l ++ )
					if ( f[i][j][k][l] ) {
						if ( j < 18 ) {
							upd(f[i][j+1][k][l], f[i][j][k][l]);
							if ( k >= 1 )
								upd(f[i][j+1][k-1][l], f[i][j][k][l]);
							if ( l >= 1 )
								upd(f[i][j+1][k][l-1], f[i][j][k][l]);
							if ( k >= 2 )
								upd(f[i][j+1][k-2][l], f[i][j][k][l]);
							if ( k >= 1 && l >= 1 )
								upd(f[i][j+1][k-1][l-1], f[i][j][k][l]);
							if ( k >= 3 )
								upd(f[i][j+1][k-3][l], f[i][j][k][l]);
							if ( l >= 2 )
								upd(f[i][j+1][k][l-2], f[i][j][k][l]);
						}
					}
	pow9[0] = pow10[0] = (uint)1;
	for ( int i = 1; i <= 36; i ++ )
		pow9[i] = (uint)9 * pow9[i-1], pow10[i] = (uint)10 * pow10[i-1];
}

int main() {
	freopen("t.in", "r", stdin);
	prework();
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		int L;
		ll V;
		scanf("%d" LL_FMT, &L, &V);
		int nl = L-L/2, nr = L/2;
		uint res = 0;
		if ( V == 0 ) {
			for ( int i = 2; i <= nl; i ++ )
				res += pow9[i-1] * pow10[nl-i] * pow9[nr];
		}
		else {
			int cnt[4];
			memset(cnt, 0, sizeof(cnt));
			while ( V % 2 == 0 )
				V /= 2, cnt[0]++;
			while ( V % 3 == 0 )
				V /= 3, cnt[1]++;
			while ( V % 5 == 0 )
				V /= 5, cnt[2]++;
			while ( V % 7 == 0 )
				V /= 7, cnt[3]++;
			if ( V > 1 ) {
				res = 0;
			} else {
				for ( int i = 0; i <= nl; i ++ ) {
					int j = nr+cnt[2]+cnt[3]+i-nl;
					if ( 0 <= j && j <= nr ) {
						for ( int x5 = 0; x5 <= nl-i; x5 ++ ) {
							int x7 = nl-i-x5;
							int y5 = x5 - cnt[2], y7 = x7 - cnt[3];
							assert(y5+y7 == nr-j);
							if ( 0 <= y5 && 0 <= y7 ) {
								uint tmp = f[i][j][cnt[0]][cnt[1]] * bino[nl][i] * bino[nr][j];
								tmp *= bino[nl-i][x5];
								assert(nl-i-x5==x7);
								tmp *= bino[nr-j][y5];
								assert(nr-j-y5==y7);
								res += tmp;
							}
						}
					}
				}
			}
		}
		printf("%u\n", res);
	}
}
