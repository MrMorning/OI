#include <cstdio>
#define MOD 1000000007
typedef long long ll;
int n, m, k;
int powMod(int a, int n){
	int res = n & 1 ? a : 1;
	for(n >>= 1; n; n >>= 1){
		a = (ll)a * a % MOD;
		if(n & 1)
			res = (ll)res * a % MOD;
	}
	return res;
}
int factorial(int n){
	int res = 1;
	for(int x = 2; x <= n; x ++)
		res = (ll)res * x % MOD;
}
int f(int i, int j){
	static int memo[1010][1010];
	static bool done[1010][1010];
	if(done[i][j])
		return memo[i][j];
	done[i][j] = true;
	int &res = memo[i][j] = 0;
	if(j > i)
		return res = 0;
	if(i == 0)
		return res = 1;
	if(j == 0)
		return res = 0;
	return (res = (ll)(f(i - 1, j) + f(i - 1, j - 1)) * j % MOD);
}

void solve(){
	scanf("%d%d%d", &n, &m, &k);
	int ans = 0, acc = 1;
	for(int i = 1; i <= k; i ++){
		acc = (ll)acc * (m - i + 1) % MOD;
		acc = (ll)acc * powMod(i, MOD - 2) % MOD;
		ans += (ll)acc * f(n, i) % MOD;
		ans %= MOD;
	}
	printf("%d\n", ans);
}

int main(){
	freopen("t.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while(T --)
		solve();
}
