#include <cstdio>
#include <cstring>
#include <algorithm>
const int N_MAX = 2020;
const int Z_MAX = 26;
using namespace std;

short z, sz[2], en[2][N_MAX], go[2][N_MAX][Z_MAX];
bool check() {
	static bool vis[N_MAX][N_MAX];
	static pair<short, short> Q[N_MAX * N_MAX];
	memset(vis, 0, sizeof(vis));
	int qt = 0;
	Q[qt ++] = make_pair(0, 0);
	vis[0][0] = true;
	for ( int qh = 0; qh < qt; qh ++ ) {
		pair<short, short> u = Q[qh];
		int i = u.first, j = u.second;
		if ( en[0][i] != en[1][j] )
			return false;
		for ( int a = 0; a < z; a ++ ) {
			short ni = go[0][i][a],
				nj = go[1][j][a];
			if ( !vis[ni][nj] ) {
				vis[ni][nj] = true;
				Q[qt ++] = make_pair(ni, nj);
			}
		}
	}
	return true;
}
int main() {
	freopen("t.in", "r", stdin);
	int TST = 0;
	while ( scanf("%hd", &z), z ) {
		printf("Case #%d: ", ++ TST);
		for ( int t = 0; t < 2; t ++ ) {
			scanf("%hd", &sz[t]);
			for ( int i = 0; i < sz[t]; i ++ ) {
				scanf("%hd", &en[t][i]);
				for ( int a = 0; a < z; a ++ ) {
					scanf("%hd", &go[t][i][a]);
					if ( go[t][i][a] == -1 )
						go[t][i][a] = sz[t];
				}
				for ( int a = 0; a < z; a ++ )
					go[t][sz[t]][a] = sz[t];
				en[t][sz[t]] = 0;
			}
		}
		if ( check() )
			puts("Yes");
		else
			puts("No");
	}
}
