#include <cstdio>
#include <cassert>
#include <cstdlib>

const int kNMax = 1010;

struct Stuff {
	int i, j;
	bool isv;
	Stuff(){}
	Stuff(int ii, int jj, bool vv):
		i(ii), j(jj), isv(vv){}
} que[kNMax * kNMax];
int qt = 0;

bool vis[kNMax][kNMax][2];
int color[kNMax][kNMax];
int bd[kNMax][kNMax];
int n, m;

void append(int i, int j, bool isv) {
	if ( !vis[i][j][isv] ) {
		vis[i][j][isv] = true;
		que[qt++] = Stuff(i, j, isv);
	}
}

void paint(int i, int j, bool isv) {
	int msk = 0;
	if ( isv ) {
		for ( int dx = -1; dx <= 1; dx ++ )
			for ( int dy = -1; dy <= 1; dy += 2 )
				msk |= 1 << color[i+dx][j+dy];
		if ( i-2 >= 1 )
			msk |= 1 << color[i-2][j];
		if ( i+2 <= n )
			msk |= 1 << color[i+2][j];
		msk >>= 1;
		//assert(msk != 15);
		for ( int k = 0; k < 4; k ++ )
			if ( !(msk & (1 << k)) ) {
				color[i][j] = color[i-1][j] = color[i+1][j] = k+1;
				break;
			}
	} else {
		for ( int dx = -1; dx <= 1; dx +=2 )
			for ( int dy = -1; dy <= 1; dy ++ )
				msk |= 1 << color[i+dx][j+dy];
		if ( j-2 >= 1 )
			msk |= 1 << color[i][j-2];
		if ( j+2 <= m )
			msk |= 1 << color[i][j+2];
		msk >>= 1;
		//assert(msk != 15);
		for ( int k = 0; k < 4; k ++ )
			if ( !(msk & (1 << k)) ) {
				color[i][j] = color[i][j-1] = color[i][j+1] = k+1;
				break;
			}
	}
}

void expand(int i, int j) {
	//assert(color[i][j] != 0);
	if ( !color[i-1][j] && bd[i-1][j] == 2 ) {
		if ( !color[i-1][j-1] && bd[i-1][j-1] == 1 
				&& !color[i-1][j+1] && bd[i-1][j+1] == 1 ) 
			append(i-1, j, 0);
	} 
	if ( !color[i+1][j] && bd[i+1][j] == 2 ) {
		if ( !color[i+1][j-1] && bd[i+1][j-1] == 1
				&& !color[i+1][j+1] && bd[i+1][j+1] == 1 )
			append(i+1, j, 0);
	} 
	if ( !color[i][j-1] && bd[i][j-1] == 2 ) {
		if ( !color[i-1][j-1] && bd[i-1][j-1] == 1
				&& !color[i+1][j-1] && bd[i+1][j-1] == 1 )
			append(i, j-1, 1);
	} 
	if ( !color[i][j+1] && bd[i][j+1] == 2 ) {
		if ( !color[i-1][j+1] && bd[i-1][j+1] == 1 
				&& !color[i+1][j+1] && bd[i+1][j+1] == 1 )
			append(i, j+1, 1);
	}
}

void noSol() {
	puts("NO");
	exit(0);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		static char str[kNMax];
		scanf("%s", str);
		for ( int j = 0; j < m; j ++ ) {
			if ( str[j] == 'w' ) 
				bd[i][j+1] = 1;
			else if ( str[j] == 'b' )
				bd[i][j+1] = 2;
		}
	}

	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) 
			if ( bd[i][j] == 2 ) {
				int bv = 0, bh = 0;
				if ( bd[i-1][j]==1 && bd[i+1][j]==1 )
					bv = 1;
				if ( bd[i][j-1]==1 && bd[i][j+1]==1 )
				   	bh = 1;
				if ( bv ^ bh ) {
					append(i, j, bv);
				}
			}

	for ( int qh = 0; qh < qt; qh ++ ) {
		Stuff T = que[qh];
		paint(T.i, T.j, T.isv);
		if ( T.isv ) {
			expand(T.i-1,T.j);
			expand(T.i+1,T.j);
		} else {
			expand(T.i,T.j-1);
			expand(T.i,T.j+1);
		}
	}

	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( bd[i][j] && !color[i][j] ) 
				noSol();
	puts("YES");
	for ( int i = 1; i <= n; i ++, puts("") )
		for ( int j = 1; j <= m; j ++ )
			if ( !bd[i][j] )
				printf(".");
			else
				printf("%c", 'a'+color[i][j]-1);
}
