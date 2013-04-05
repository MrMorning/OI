#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int M[10];
int CP(int s, int i) { return s & ~(3 << M[i]); }
int CP(int s, int i, int j) { return s & ~(3 << M[i]) & ~(3 << M[j]); }
int CP(int s, int i, int j, int k) { return s & ~(3 << M[i]) & ~(3 << M[j]) & ~(3 << M[k]); }
int getP(int s, int i) { return (s >> M[i]) & 3; }
int MP(int i, int p) { return p << M[i]; }
void upd(int &a, int b) { if ( a < b ) a = b; }
int cntSP(int s) {
	int res = 0;
	while ( s ) res += (s & 3) == 3, s >>= 2;
	return res;
}
int getLP(int s, int i) {
	int cnt = 0;
	for ( ; ; i -- ) if ( getP(s, i) == 1 || getP(s, i) == 2 ) {
		cnt += getP(s, i) == 1 ? -1 : 1;
		if ( !cnt )
			return i;
	}
}
int getRP(int s, int i) {
	int cnt = 0;
	for ( ; ; i ++ ) if ( getP(s, i) == 1 || getP(s, i) == 2 ) {
		cnt += getP(s, i) == 2 ? -1 : 1;
		if ( !cnt )
			return i;
	}
}
struct HashMap {
#define MSKSIZE 300000
#define HSHSIZE 65536
#define HTMP 65535
	int begin[HSHSIZE], dp[MSKSIZE], next[MSKSIZE], tomsk[MSKSIZE], msksz;
	void clear() {
		msksz = 0;
		memset(begin, -1, sizeof(begin));
	}
	void push(int msk, int val) {
		int code = msk & HTMP;
		for ( int it = begin[code]; it != -1; it = next[it] )
			if ( tomsk[it] == msk ) {
				upd(dp[it], val);
				return;
			}
		tomsk[msksz] = msk;
		dp[msksz] = val;
		next[msksz] = begin[code];
		begin[code] = msksz ++;
	}
} HM[2], *cur, *nxt;
int n, m, wt[10][10];

int plugDP() {
	cur = HM, nxt = HM + 1;
	cur->clear();
	cur->push(0, 0);
	int ans = 0;
	for ( int i = 0; i < n; i ++ ) {
		for ( int j = 0; j < m; j ++ ) {
			nxt->clear();
			for ( int k = 0; k < cur->msksz; k ++ ) {
				int s = cur->tomsk[k];
				int nxtval = cur->dp[k] + wt[i][j];
				int p = getP(s, j), q = getP(s, j + 1);
				if ( !wt[i][j] ) {
					if ( p == 0 && q == 0 ) nxt->push(s, nxtval);
					continue;
				}
				if ( !p && !q ) {
					nxt->push(s, cur->dp[k]);
					if ( cntSP(s) < 2 ) {
						nxt->push(s | MP(j, 3), nxtval);
						nxt->push(s | MP(j + 1, 3), nxtval);
					}
					nxt->push(s | MP(j, 1) | MP(j + 1, 2), nxtval);
					if ( s == 0 ) upd(ans, wt[i][j]);
				} else if ( !p || !q ) {
					int r = p + q;
					nxt->push(CP(s, j, j + 1) | MP(j, r), nxtval);
					nxt->push(CP(s, j, j + 1) | MP(j + 1, r), nxtval);
					if ( r == 3 ) {
						if ( CP(s, j, j + 1) == 0 ) upd(ans, nxtval);
					} else {
						int t = p ? j : j + 1,
							u = r == 1 ? getRP(s, t) : getLP(s, t);
						nxt->push(CP(s, j, j + 1) | MP(u, 3), nxtval);
					}
				} else {
					if ( p == 3 && q == 3 ) {
						if ( CP(s, j, j + 1) == 0 ) upd(ans, nxtval);
					} else if ( p < 3 && q < 3 ) {
						if ( p == q ) {
							int u = p == 1 ? getRP(s, j + 1) : getLP(s, j);
							nxt->push(CP(s, j, j + 1, u) | MP(u, p), nxtval);
						} else if ( p == 2 && q == 1 )
							nxt->push(CP(s, j, j + 1), nxtval);
					} else {
						int t = p == 3 ? q : p,
							v = p == 3 ? j  + 1 : j,
							u = t == 1 ? getRP(s, v) : getLP(s, v);
						nxt->push(CP(s, j, j + 1) | MP(u, 3), nxtval);
					}	
				}
			}
			swap(cur, nxt);
		}
		nxt->clear();
		for ( int k = 0; k < cur->msksz; k ++ ) {
			int s = cur->tomsk[k];
			if ( getP(s, m) == 0 )
				nxt->push(s << 2, cur->dp[k]);
		}
		swap(cur, nxt);
	}
	return ans;
}

int main() {
	for ( int i = 0; i < 10; i ++ )
		M[i] = i << 1;
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		scanf("%d%d", &n, &m);
		for ( int i = 0; i < n; i ++ )
			for ( int j = 0; j < m; j ++ )
				scanf("%d", &wt[i][j]);
		printf("%d\n", plugDP());
	}
}
