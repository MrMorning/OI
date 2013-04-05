#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
vector<int> buff;
vector<vector<int> > way;
int N, M, P;
ll fact[55], inv[55], facInv[55];
void dfs(int left, int pre) {
	if ( left == 0 ) {
		way.push_back(buff);
		return;
	} else if ( left < pre )
		return;
	for ( int x = pre; x <= left; x ++ ) {
		buff.push_back(x);
		dfs(left - x, x);
		buff.pop_back();
	}
}
ll powMod(ll a, ll n) {
	ll res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = a * a % P;
		if ( n & 1 )
			res = res * a % P;
	}
	return res;
}
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	scanf("%d%d%d", &N, &M, &P);
	fact[0] = facInv[0] = 1;
	for ( int i = 1; i <= N; i ++ ) {
		fact[i] = fact[i - 1] * i % P;
		inv[i] = powMod(i, P - 2);
		facInv[i] = facInv[i - 1] * inv[i] % P;
	}
	dfs(N, 1);
	ll ans = 0;
	for ( int i = 0; i < (int)way.size(); i ++ ) {
		ll tot = fact[N];
		int cnt = 1;
		for ( int j = 0; j < (int)way[i].size(); j ++ ) {
			tot = tot * inv[way[i][j]] % P;
			if ( j > 0 && way[i][j] == way[i][j - 1] )
				cnt ++;
			else {
				tot = tot * facInv[cnt] % P;
				cnt = 1;
			}
		}
		tot = tot * facInv[cnt] % P;
		cnt = 0;

		ll tmp = 0;
		for ( int j = 0; j < (int)way[i].size(); j ++ ) {
			tmp += way[i][j] / 2;
			for ( int k = j + 1; k < (int)way[i].size(); k ++ ) 
				tmp += gcd(way[i][j], way[i][k]);
		}
		ans += tot * powMod(M, tmp) % P;
		ans %= P;
	}
	for ( int i = 1; i <= N; i ++ )
		ans = ans * inv[i] % P;
	printf("%d\n", (int)ans);
}
