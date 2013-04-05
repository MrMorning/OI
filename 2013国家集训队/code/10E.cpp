#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const ll kInf = 0x3f3f3f3f3f3f3f3fLL;
ll tmp[444], c[444];
int n;

ll construct(ll val) {
	ll res = 0;
	for ( int i = 1; i <= n; i ++ )
		tmp[i] = val / c[i], res += tmp[i] * c[i], val -= tmp[i] * c[i];
	return res;
}

ll eval() {
	ll res = 0;
	for ( int i = 1; i <= n; i ++ )
		res += c[i] * tmp[i];
	return res;
}

int main() {
	//freopen("t.in", "r", stdin);
	cin >> n;
	ll ans = kInf;
	for ( int i = 1; i <= n; i ++ ) cin >> c[i];
	for ( int i = 2; i <= n; i ++ )
		for ( int j = i; j <= n; j ++ ) {
			construct(c[i-1]-1);
			tmp[j]++;
			for ( int k = j+1; k <= n; k ++ ) tmp[k] = 0;
			bool fail = false;
			for ( int k = 1; k < i; k ++ ) 
				if ( tmp[k] != 0 ) fail = true;
			for ( int k = j+1; k <= n; k ++ ) 
				if ( tmp[k] != 0 ) fail = true;
			if ( fail ) continue;
			ll w = eval();
			ll sz = 0;
			for ( int i = 1; i <= n; i ++ ) sz += tmp[i];
			construct(w);
			ll sz2 = 0;
			for ( int i = 1; i <= n; i ++ ) sz2 += tmp[i];
			if ( sz<sz2 ) ans = min(ans, w);
		}
	if ( ans == kInf ) cout << -1;
	else
		cout << ans;
}

