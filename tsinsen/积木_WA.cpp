#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, c, h[1000010];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &c);
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &h[i]);
	ll res = 0;
	for ( int i = 1; i < n - 1; i ++ )
		if ( h[i - 1] > h[i] && h[i] < h[i + 1] ) {
			int lim = min(h[i - 1] - h[i], h[i + 1] - h[i]);
			if ( lim < c ) {
				res += (ll)lim * lim;
				h[i] += lim;
			} else {
				res += (ll)c * c;
				h[i] += c;
			}
		}
	if ( h[0] < h[1] ) {
		int delta = h[1] - h[0];
		if ( delta < c / 2 ) {
			res += (ll)delta * delta;
			h[0] += delta;
		} else {
			res += (ll)(c / 2) * (c / 2);
			h[0] += (c / 2) * (c / 2);
		}
	}
	if ( h[n - 1] < h[n - 2] ) {
		int delta = h[n - 2] - h[n - 1];
		if ( delta < c / 2 ) {
			res += (ll)delta * delta;
			h[n - 1] += delta;
		} else {
			res += (ll)(c / 2) * (c / 2);
			h[n - 1] += (c / 2) * (c / 2);
		}
	}
	for ( int i = 1; i < n; i ++ )
		res += (ll)c * abs(h[i] - h[i - 1]); 
	cout << res;
}
