#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N, M, HP, MP, SP, DH, DM, DS, X;
int N1, N2, A[111], B[11], C[11], Y[11], Z[11];
int f[102][71][71][71];
inline void upd(int &a, int b) {
	if ( b > a ) a = b;
}
int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		scanf("%d%d%d%d%d%d%d%d%d", &N, &M, &HP, &MP, &SP, &DH, &DM, &DS, &X);
		for ( int i = 1; i <= N; i ++ )
			scanf("%d", &A[i]);
		scanf("%d", &N1);
		for ( int i = 1; i <= N1; i ++ )
			scanf("%d%d", &B[i], &Y[i]);
		scanf("%d", &N2);
		for ( int i = 1; i <= N2; i ++ )
			scanf("%d%d", &C[i], &Z[i]);
		memset(f, -0x3f, sizeof(f));
		f[0][HP][MP][SP] = 0;
		int ans = -1;
		for ( int i = 0; ans==-1&&i < N; i ++ ) 
			for ( int j = 1; ans==-1&&j <= HP; j ++ )
				for ( int k = 0; ans==-1&&k <= MP; k ++ )
					for ( int l = 0; ans==-1&&l <= SP; l ++ )
						if ( f[i][j][k][l] >= 0 ) {
							int val = f[i][j][k][l];
							if ( val + X >= M )
								ans = i+1;
							for ( int t = 1; t <= N1; t ++ )
								if ( k >= B[t] && val + Y[t] >= M ) 
									ans = i+1;
							for ( int t = 1; t <= N2; t ++ )
								if ( l >= C[t] && val + Z[t] >= M )
									ans = i+1;
							if ( j - A[i+1] > 0 ) {
								upd(f[i+1][j-A[i+1]][k][min(SP,l+DS)], val + X);
								for ( int t = 1; t <= N1; t ++ )
									if ( k >= B[t] ) 
										upd(f[i+1][j-A[i+1]][k-B[t]][l], val + Y[t]);
								for ( int t = 1; t <= N2; t ++ )
									if ( l >= C[t] )
										upd(f[i+1][j-A[i+1]][k][l-C[t]], val + Z[t]);
								upd(f[i+1][j-A[i+1]][min(MP,k+DM)][l], val);
							}
							if ( j+DH - A[i+1] > 0 )
								upd(f[i+1][min(HP, j+DH)-A[i+1]][k][l], val);
						}
		if ( ans != -1 )
			printf("Yes %d\n", ans);
		else {
			bool found = false;
			for ( int j = 1; !found && j <= HP; j ++ )
				for ( int k = 0; !found && k <= MP; k ++ )
					for ( int l = 0; !found && l <= SP; l ++ )
						if ( f[N][j][k][l] >= 0 ) {
							found = true;
						}
			if ( found ) puts("Tie");
			else puts("No");
		}
	}
}

