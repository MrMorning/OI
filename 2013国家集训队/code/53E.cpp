#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
int e[11][11];
ll f[1<<10][1<<10][3];
int n, m, k;

int countbit(int s) {
	int res = 0;
	while ( s ) {
		res += s & 1;
		s >>= 1;
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	for ( int i = 0; i < m; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		e[u][v] = e[v][u] = true;
	}

	int upperlim = 1<<n;
	f[1][1][0] = 1; //fix the root
	for ( int s1 = 1; s1 < upperlim; s1 ++ )
		for ( int s2 = s1; s2; s2 = (s2-1) & s1 )
			for ( int s3 = 0; s3 <= 2; s3 ++ )
				if ( f[s1][s2][s3] ) {
					f[s1][s2][s3] /= countbit(s2);
					for ( int x = 0; x < n; x ++ ) 
						if ( !(s1 & (1 << x)) )
							for ( int y = 0; y < n; y ++ )
								if ( s1 & (1 << y) )
									if ( e[x][y] ) 
										f[s1 | (1<<x)][(s2 & (~(1<<y))) | (1<<x)][min(2,s3+(y==0))] += f[s1][s2][s3];
				}
	ll ans = 0;
	for ( int s2 = 0; s2 < upperlim; s2 ++ )
		for ( int s3 = 0; s3 <= 2; s3 ++ )
			if ( (countbit(s2) + (s3<=1) ) == k ) ans += f[upperlim-1][s2][s3];
	cout << ans;
}
