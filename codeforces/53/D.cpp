#include <iomanip>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int N_MAX = 1010;
int n, m;
ll ans = 0;
ll f[N_MAX], g[N_MAX];
int obs1[N_MAX], obs2[N_MAX];

ll arith(int a, int b) {
	if ( a > b )
		return 0LL;
	return (ll)(a + b) * (b - a + 1) / 2;
}

void solve(int n, int m, int *obs) {
	for ( int j = 1; j <= m; j ++ ) {
		int top = 0;
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		for ( int i = 1; i <= n; i ++ ) {
			if ( obs[i] == 0 || obs[i] > j ) {
				g[i] = f[i] = f[i - 1] + arith(1, j - 1);
				top = 0;
			} else {
				f[i] = f[i - 1] + arith(j - obs[i] + 1, j - 1) + arith(1, j - obs[i] - 1);
				if ( obs[i] > top ) 
					g[i] = g[i - 1] + arith(j - obs[i] + 1, j - 1) + 2 * (obs[i] - 1) + arith(1, j - obs[i] - 1); 
				else 
					g[i] = f[i - 1] + arith(j - obs[i] + 1, j - 1) + 2 * (obs[i] - 1) + arith(1, j - obs[i] - 1); 
				top = obs[i];
			}
			if ( j != obs[i] ) {
				ans += g[i];
//				fprintf(stderr, "%lld\n", g[i]);
			}
		}
		top = 0;
		for ( int i = n; i >= 1; i -- ) {
			if ( obs[i] == 0 || obs[i] > j ) {
				g[i] = f[i] = f[i + 1] + arith(1, j - 1);
				top = 0;
			} else {
				f[i] = f[i + 1] + arith(j - obs[i] + 1, j - 1) + arith(1, j - obs[i] - 1);
				if ( obs[i] > top ) 
					g[i] = g[i + 1] + arith(j - obs[i] + 1, j - 1) + 2 * (obs[i] - 1) + arith(1, j - obs[i] - 1); 
				else 
					g[i] = f[i + 1] + arith(j - obs[i] + 1, j - 1) + 2 * (obs[i] - 1) + arith(1, j - obs[i] - 1); 
				top = obs[i];
			}
			if ( j != obs[i] )
				ans += g[i];
		}

		for ( int i = 1; i <= n; i ++ ) 
			if ( obs[i] != j ) {
				if ( obs[i] == 0 || obs[i] > j ) 
					ans -= arith(1, j - 1);
				else 
					ans -= arith(j - obs[i] + 1, j - 1) + 2 * (obs[i] - 1) + arith(1, j - obs[i] - 1); 
			}
	}
}

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int obs_cnt = 0;
	for ( int i = 1; i <= n; i ++ ) {
		static char str[1111];	
		scanf("%s", str + 1);
		for ( int j = 1; j <= m; j ++ ) {
			if ( str[j] == 'X' ) {
				obs1[i] = j;
				obs2[j] = i;
				obs_cnt ++;
			}
		}
	}
	solve(n, m, obs1);
	solve(m, n, obs2);
	cout << fixed << setprecision(10) << (long double)ans * 2 / ((ll)(n * m - obs_cnt) * (n * m - obs_cnt));
}
