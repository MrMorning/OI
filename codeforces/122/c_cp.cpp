#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll mat[11][11], des[11];
ll var[11], nVar;
ll id2eq[6][6], nEq;
bool done[1 << 4];
ll head[11];
const ll inf = 0x3f3f3f3f3f3f3f3fLL;
ll ans = inf, note[11], res[11];
bool notfree[11];
char str[4][400010];

inline ll getbit(ll s, ll i) {
	return (s & (1 << i)) > 0;
}

void elim(ll n, ll m) {
	for ( ll i = 0, j = 0; i < m - 1; i ++ ) {
		ll p = 0;
		for ( p = j; p < n; p ++ )
			if ( mat[p][i] != 0 )
				break;
		if ( p == n )
			continue;
		for ( ll k = 0; k < m; k ++ )
			swap(mat[p][k], mat[j][k]);
		for ( p = 0; p < n; p ++ )
			if ( p != j && mat[p][i] != 0 ) {
				ll lcm = mat[p][i] * mat[j][i] / gcd(abs(mat[p][i]), abs(mat[j][i]));
				ll f1 = lcm / mat[j][i], f2 = lcm / mat[p][i];
				for ( ll k = 0; k < m; k ++ ) 
					mat[p][k] = f2 * mat[p][k] - f1 * mat[j][k];
			}
		j ++;
	}
}

bool noSol(ll n, ll m) {
	for ( ll i = 0; i < n; i ++ ) {
		bool allZero = true;
		for ( ll j = 0; j < m - 1; j ++ )
			allZero &= mat[i][j] == 0 ;
		if ( allZero && mat[i][m - 1] != 0 ) 
		   return true;	
	}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	for ( ll a = 0; a < 4; a ++ )
		for ( ll b = a + 1; b < 4; b ++ ) {
			id2eq[a][b] = nEq;
			cin >> des[nEq++];
		}
	for ( ll s = 0, lim = 1 << 4; s < lim; s ++ ) 
		if ( s != 0 && s != lim - 1 )
			if ( !done[~s & (lim - 1)] ) {
				done[s] = true;
				var[nVar++] = s;
				for ( ll a = 0; a < 4; a ++ )
					for ( ll b = a + 1; b < 4; b ++ )
						if ( getbit(s, a) != getbit(s, b) ) 
							mat[id2eq[a][b]][nVar - 1] = 1;
			}
	for ( ll i = 0; i < nEq; i ++ )
		mat[i][nVar] = des[i];
	assert(nVar == 7 && nEq == 6);
	ll nRow = 6, nCol = 8;
	elim(nRow, nCol);
	if ( noSol(nRow, nCol) ) {
		puts("-1");
		return 0;
	}
	for ( ll i = 0; i < nRow; i ++ ) {
		for ( ll j = 0; j < nCol - 1; j ++ )
			if ( mat[i][j] != 0 ) {
				head[i] = j;
				notfree[j] = true;
				break;
			}
	}
	ll free = -1;
	for ( ll i = 0; i < nCol - 1; i ++ )
		if ( !notfree[i] ) {
			free = i;
			break;
		}
	assert(free != -1);
	for ( res[free] = 0; res[free] <= 100000; res[free] ++ ) {
		bool fail = false;
		for ( ll i = 0; i < nRow; i ++ ) {
			ll tmp = mat[i][nCol - 1] - (ll)res[free] * mat[i][free];
			if ( tmp % mat[i][head[i]] != 0 || tmp / mat[i][head[i]] < 0 ) {
				fail = true;
				break;
			}
			res[head[i]] = tmp;
		}
		if ( !fail ) {
			ll sum = 0;
			for ( ll i = 0; i < nVar; i ++ )
				sum += res[i];
			if ( sum < ans ) {
				ans = sum;
				memcpy(note, res, sizeof(res));
			}
		}
	}
	if ( ans == inf ) {
		puts("-1");
		return 0;
	}
	cout << ans << '\n';
	for ( ll i = 0, len = 0; i < nVar; i ++ ) {
		for ( ll j = 0; j < note[i]; j ++ ) {
			for ( ll t = 0; t < 4; t ++ )
				if ( var[i] & (1 << t) ) {
					str[t][len] = 'a';
				} else {
					str[t][len] = 'b';
				}
			len ++;
		}
	}
	for ( ll i = 0; i < 4; i ++ )
		cout << str[i] << '\n';
}
