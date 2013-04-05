#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll f[1000010], g[1000010];
const int kMod = 1000000009;
int main() {
	freopen("t.in", "r", stdin);
	int n;
	cin >> n;
	f[1] = 1;
	for ( int i = 2; i < n/2; i ++ )
		f[i] = (2*f[i-1]+3) % kMod;
	g[n/2] = 2;
	for ( int i = n/2 - 1; i >= 1; i -- )
		g[i] = (2 + 2*f[i] + f[i] * g[i+1]) % kMod;
	ll ans = 2*(g[1]*g[1]+1) % kMod;
	cout << ans;
} 
