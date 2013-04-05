#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N, M, HP, MP, SP, DH, DM, DS, X;
int N1, N2, A[1111], B[11], C[11], Y[11], Z[11];
int fhp[1111][1111], fmp[1111][1111], fsp[1111][1111];

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

		memset(fhp, -0x3f, sizeof(fhp));
		fhp[0][HP] = 0;
		for ( int i = 0; i < N; i ++ )
			for ( int hp = 1; hp <= HP; hp ++ )
				if ( fhp[i][hp] >= 0 ) {
					if ( min(hp+DH,HP) > A[i+1] )
						upd(fhp[i+1][min(hp+DH,HP)-A[i+1]], fhp[i][hp]);
					if ( hp > A[i+1] )
						upd(fhp[i+1][hp-A[i+1]], fhp[i][hp]+1);
				}

		memset(fmp, -0x3f, sizeof(fmp));
		fmp[0][MP] = 0;
		for ( int i = 0; i < N; i ++ )
			for ( int mp = 0; mp <= MP; mp ++ ) 
				if ( fmp[i][mp] >= 0 ) {
					upd(fmp[i+1][min(mp+DM,MP)], fmp[i][mp]);
					for ( int k = 1; k <= N1; k ++ )
						if ( mp >= B[k] )
							upd(fmp[i+1][mp-B[k]], fmp[i][mp]+Y[k]);
				}
		memset(fsp, -0x3f, sizeof(fsp));
		fsp[0][SP] = 0;
		for ( int i = 0; i < N; i ++ ) 
			for ( int sp = 0; sp <= SP; sp ++ )
				if ( fsp[i][sp] >= 0 ) {
					upd(fsp[i+1][min(SP,sp+DS)], fsp[i][sp]+X);
					for ( int k = 1; k <= N2; k ++ )
						if ( sp >= C[k] )
							upd(fsp[i+1][sp-C[k]], fsp[i][sp]+Z[k]);
				}

		for ( int i = 0; i <= N; i ++ ) {
			for ( int j = MP-1; j >= 0; j -- ) upd(fmp[i][j], fmp[i][j+1]);
			for ( int j = SP-1; j >= 0; j -- ) upd(fsp[i][j], fsp[i][j+1]);
		}

		bool gameOver = false; int ans = -1;
		for ( int ed = 1; ans == -1 && !gameOver && ed <= N; ed ++ ) {
			int spare = 0;
			for ( int hp = 1; hp <= HP; hp ++ )
				upd(spare, fhp[ed-1][hp]);
			for ( int kmp = 0; kmp <= spare; kmp ++ ) {
				int ksp = spare - kmp;
				//enum last hit
				if ( X + fmp[kmp][0] + fsp[ksp][0] >= M ) 
					ans = ed;
				for ( int k = 1; k <= N1; k ++ )
					if ( Y[k] + fmp[kmp][B[k]] + fsp[ksp][0] >= M ) 
						ans = ed;
				for ( int k = 1; k <= N2; k ++ )
					if ( Z[k] + fmp[kmp][0] + fsp[ksp][C[k]] >= M )
						ans = ed;
			}
		}
		if ( ans == -1 ) {
			bool okay = false;
			for ( int hp = 1; hp <= HP; hp ++ )
				if ( fhp[N][hp] >= 0 )
					okay = true;
			if ( !okay ) gameOver = true;
		}

		if ( gameOver ) puts("No");
		else if ( ans == -1 ) puts("Tie");
		else printf("Yes %d\n", ans);
	}
}

