#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int kMod = 51123987;
inline void upd(int &a, int b) {
	a += b;
	if ( a > kMod ) a -= kMod;
}
char str[155];
int f[2][155][155][155];
int next[155][3];
int n;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", str);
	memset(next, -1, sizeof(next));
	for ( int i = 0; i < n; i ++ ) {
		for ( int j = i; j < n; j ++ ) {
			if ( str[j] == 'a' && next[i][0] == -1 )
				next[i][0] = j;
			if ( str[j] == 'b' && next[i][1] == -1 )
				next[i][1] = j;
			if ( str[j] == 'c' && next[i][2] == -1 )
				next[i][2] = j;
		}
	}

	f[0][0][0][0] = 1;
	int cur = 0;
	for ( int i = 0; i < n; i ++ ) {
		memset(f[!cur], 0, sizeof(f[!cur]));
		for ( int j = 0; j < n; j ++ )
			for ( int na = 0; na <= i; na ++ )
				for ( int nb = 0; nb + na <= i; nb ++ )
					if ( f[cur][j][na][nb] ) {
						int val = f[cur][j][na][nb];
						if ( next[j][0] != -1 ) 
							upd(f[!cur][next[j][0]][na+1][nb], val);
						if ( next[j][1] != -1 ) 
							upd(f[!cur][next[j][1]][na][nb+1], val);
						if ( next[j][2] != -1 ) 
							upd(f[!cur][next[j][2]][na][nb], val);
					}
		cur ^= 1;
	}
	int ans = 0;
	for ( int na = 0; na <= n; na ++ )
		for ( int nb = 0; nb <= n; nb ++ ) {
			int nc = n - na - nb;
			if ( abs(na-nb) <= 1 && abs(nb-nc) <= 1 && abs(na-nc) <= 1 )
				for ( int k = 0; k < n; k ++ )
					upd(ans, f[cur][k][na][nb]);
		}
	printf("%d\n", ans);
}
