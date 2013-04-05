#include <cstdio>
#include <cstring>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
const int kLim = 10000000;
const int kDx[4] = {0, 0, 1, -1};
const int kDy[4] = {-1, 1, 0, 0};

int prime[1000000], primeCnt, primeId[kLim+1];
bool notprime[kLim+1];
int a[355][355];
bool vis[355][355];
int n;

void prework() {
	memset(primeId, -1, sizeof(primeId));
	for ( int i = 2; i <= kLim; i ++ ) {
		if ( !notprime[i] ) {
			prime[primeCnt] = i;
			primeId[i] = primeCnt++;
		}
		for ( int j = 0; j < primeCnt && i <= kLim / prime[j]; j ++ ) {
			notprime[prime[j] * i] = true;
			if ( i % prime[j] == 0 ) break;
		}
	}	
}

void dfs(int i, int j, int odd) {
	vis[i][j] = true;
	for ( int dir = 0; dir < 4; dir ++ ) {
		int ii = i + kDx[dir], jj = j + kDy[dir];
		if ( 0 <= ii && ii < n && 0 <= jj && jj < n )
			if ( primeId[a[ii][jj]]==-1 && (a[ii][jj]&1) == odd && !vis[ii][jj] )
				dfs(ii, jj, odd);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	prework();
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		scanf("%d", &n);
		for ( int i = 0; i < n; i ++ )
			for ( int j = 0; j < n; j ++ )
				scanf("%d", &a[i][j]);
		memset(vis, 0, sizeof(vis));
		ll ans = 0;
		for ( int i = 0; i < n; i ++ )
			for ( int j = 0; j < n; j ++ )
				if ( primeId[a[i][j]] != -1 ) {
					ans += primeId[a[i][j]];
				} else if ( !vis[i][j] ) {
					if ( a[i][j] & 1 )
						ans += a[i][j] / 2 + 2;
					else
						ans += a[i][j] / 2;
					dfs(i, j, a[i][j]&1);
				}
		printf(LL_FMT "\n", ans);
	}
}
