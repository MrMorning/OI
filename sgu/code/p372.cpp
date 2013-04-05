#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
#define ALL(X) X.begin(), X.end()
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const ll kInf = 0x3f3f3f3f3f3f3f3fLL;

int m, n;
vector<pair<int, int> > que[2];
ll f[1010][1010][2][2];
int g[1010][1010][2][2];
int out[1010], nOut;

void output(int i, int j, int s0, int s1) {
	int tmp = g[i][j][s0][s1];
	if ( tmp == -1 ) return;
	output(i-1, j-(s0==0), s1, tmp);
	if ( s0 == 0 )
		out[nOut++] = que[0][j-1].second;
	else
		out[nOut++] = que[1][i-j-2].second;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &m, &n);
	for ( int i = 1; i <= n; i ++ ) {
		int c, s;
		scanf("%d%d", &c, &s);
		que[s].pb(mp(c, i));
	}
	sort(ALL(que[0]));
	sort(ALL(que[1]));
	int sz0 = que[0].size(), sz1 = que[1].size();

	memset(g, -1, sizeof(g));
	memset(f, 0x3f, sizeof(f));
	f[1][0][0][0] = 0;
	for ( int i = 1; i <= m; i ++ )
		for ( int j = 0; j < i; j ++ )
			for ( int s0 = 0; s0 <= 1; s0 ++ )
				for ( int s1 = 0; s1 <= 1; s1 ++ )
					if ( f[i][j][s0][s1] != kInf ) {
						ll val = f[i][j][s0][s1];
						int k = i - j - 1;
						if ( i > 2 && s0 == s1 ) {
							if ( s0 == 0 ) {
								if ( k < sz1 ) {
									ll tmp = val + (ll)(m-i+1) * que[1][k].first;
									if ( f[i+1][j][1][s0] > tmp ) {
										f[i+1][j][1][s0] = tmp;
										g[i+1][j][1][s0] = s1;
									}
								}
							} else {
								if ( j < sz0 ) {
									ll tmp = val + (ll)(m-i+1) * que[0][j].first;
									if ( f[i+1][j+1][0][s0] > tmp ) {
										f[i+1][j+1][0][s0] = tmp;
										g[i+1][j+1][0][s0] = s1;
									}
								}
							}
						} else {
							if ( j < sz0 ) {
								ll tmp = val + (ll)(m-i+1) * que[0][j].first;
								if ( f[i+1][j+1][0][s0] > tmp ) {
									f[i+1][j+1][0][s0] = tmp;
									g[i+1][j+1][0][s0] = s1;
								}
							}
							if ( k < sz1 ) {
								ll tmp = val + (ll)(m-i+1) * que[1][k].first;
								if ( f[i+1][j][1][s0] > tmp ) {
									f[i+1][j][1][s0] = tmp;
									g[i+1][j][1][s0] = s1;
								}
							}
						}
					}

	ll ans = kInf;
	int memoJ, memoS0, memoS1;
	for ( int j = 0; j <= m; j ++ )
		for ( int s0 = 0; s0 <= 1; s0 ++ )
			for ( int s1 = 0; s1 <= 1; s1 ++ )
				if ( f[m+1][j][s0][s1] < ans ) {
					ans = f[m+1][j][s0][s1];
					memoS0 = s0, memoS1 = s1, memoJ = j;
				}
	if ( ans == kInf )
		printf("Impossible");
	else {
		output(m+1, memoJ, memoS0, memoS1);
		for ( int i = 0; i < nOut; i ++ )
			printf("%d ", out[i]);
	}
}
