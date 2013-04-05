//by NotOnlySuccess
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
using namespace std;
int M[10];
const int HSize = 30007;
int n , m;
int maze[7][7];
bool vis[8][8];
inline int CP(int p, int i) { return p & ( ~( 3 << M[i] ) ); }
inline int CP(int p, int i, int j) { return p & ( ~( 3 << M[i] ) ) & ( ~( 3 << M[j] ) ); }
inline int CP(int p, int i, int j, int k) { return p & ( ~( 3 << M[i] ) ) & ( ~( 3 << M[j] ) ) & ( ~( 3 << M[k] ) ); }
inline int getP(int p, int i) { return 3 & ( p >> M[i] ); }
inline int PP(int i, int k) { return k << M[i]; }
inline int cntSP(int p, int cnt = 0) {
	for ( ; p ; p >>= 2 )
		cnt += ( ( p & 3 ) == 3 );
	return cnt;
}
inline int getLP(int p, int j) {
	for ( int it = j - 1 , cnt = 1 ; ; it -- ) {
		int Pi = getP(p, it);
		if ( Pi == 1 ) cnt --;
		else if ( Pi == 2 ) cnt ++;
		if ( cnt == 0 ) return it;
	}
}
inline int getRP(int p, int j) {
	for ( int it = j + 2 , cnt = 1 ; ; it ++ ) {
		int Pi = getP(p, it);
		if ( Pi == 2 ) cnt --;
		else if ( Pi == 1 ) cnt ++;
		if ( cnt == 0 ) return it;
	}
}
inline void checkmax(int &a, const int &b) { if ( a < b ) a = b; }
struct HashMap {
	int Chart[HSize] , dp[HSize] , MSK[HSize] , next[HSize] , sz;
	void clear() {
		sz = 0;
		memset(Chart, -1, sizeof( Chart ));
	}
	inline void push(int msk, int val) {
		int x = msk % HSize;
		for ( int it = Chart[x] ; it != -1 ; it = next[it] ) {
			if ( MSK[it] == msk ) {
				checkmax(dp[it], val);
				return;
			}
		}
		MSK[sz] = msk;
		dp[sz] = val;
		next[sz] = Chart[x];
		Chart[x] = sz ++;
	}
} HM[2] , *src , *des;
int PlugDP() {
	src = HM;
	des = src + 1;
	src->clear();
	src->push(0, 0);
	int ret = 0;
	for ( int i = 0 ; i < n ; i ++ ) {
		for ( int k = 0 ; k < src->sz ; k ++ )
			src->MSK[k] <<= 2;
		for ( int j = 0 ; j < m ; j ++ ) {
			if ( !vis[i][j] ) continue;
			checkmax(ret, maze[i][j]);
			des->clear();
			for ( int k = 0 ; k < src->sz ; k ++ ) {
				int msk = src->MSK[k];
				int val = src->dp[k] + maze[i][j];
				int left = getP(msk, j);
				int up = getP(msk, j + 1);
				if ( !left && !up ) {
					des->push(msk, src->dp[k]);
					if ( vis[i][j + 1] && vis[i + 1][j] ) des->push(msk | PP(j, 1) | PP(j + 1, 2), val);
					if ( cntSP(msk) > 1 ) continue;
					if ( vis[i + 1][j] ) des->push(msk | PP(j, 3), val);
					if ( vis[i][j + 1] ) des->push(msk | PP(j + 1, 3), val);
				} else if ( !left || !up ) {
					int w = left + up;
					int temp = CP(msk, j, j + 1);
					if ( vis[i + 1][j] ) des->push(temp | PP(j, w), val);
					if ( vis[i][j + 1] ) des->push(temp | PP(j + 1, w), val);
					if ( w != 3 && cntSP(msk) <= 1 ) {
						int it = ( w == 1 ) ? getRP(msk, j) : getLP(msk, j);
						des->push(CP(temp, it) | PP(it, 3), val);
					} else if ( w == 3 && temp == 0 ) checkmax(ret, val);
				} else if ( left == up ) {
					if ( left < 3 ) {
						int it = ( left == 1 ) ? getRP(msk, j) : getLP(msk, j);
						des->push(CP(msk, j, j + 1, it) | PP(it, left), val);
					} else if ( CP(msk, j, j + 1) == 0 ) checkmax(ret, val);
				} else if ( left == 3 || up == 3 ) {
					int it = ( left + up - 3 == 1 ) ? getRP(msk, j) : getLP(msk, j);
					des->push(CP(msk, j, j + 1, it) | PP(it, 3), val);
				} else if ( left == 2 && up == 1 ) des->push(CP(msk, j, j + 1), val);
			}
			swap(src, des);
		}
	}
	return ret;
}
int main() {
	freopen("t.in", "r", stdin);
	for ( int i = 0 ; i < 10 ; i ++ )
		M[i] = ( i << 1 );
	int T;
	scanf("%d", &T);
	while ( T -- ) {
		scanf("%d%d", &n, &m);
		for ( int i = 0 ; i < n ; i ++ )
			for ( int j = 0 ; j < m ; j ++ )
				scanf("%d", &maze[i][j]);
		if ( n < m ) {
			for ( int i = 0 ; i < n ; i ++ )
				for ( int j = i + 1 ; j < m ; j ++ )
					swap(maze[i][j], maze[j][i]);
			swap(n, m);
		}
		memset(vis, false, sizeof( vis ));
		for ( int i = 0 ; i < n ; i ++ )
			for ( int j = 0 ; j < m ; j ++ )
				if ( maze[i][j] ) vis[i][j] = true;
		printf("%d\n", PlugDP());
	}
	return 0;
}
