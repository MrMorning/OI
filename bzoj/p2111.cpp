#include <cstdio>
typedef long long ll;
int N, P;
int log2[1000011];
ll powMod(ll a, ll n, ll m){
	ll res = n & 1 ? a : 1;
	for(n >>= 1; n; n >>= 1){
		a = a * a % m;
		if(n & 1)
			res = res * a % m;
	}
	return res % m;
}

ll bino(ll n, ll k){
	ll res = 1;
	for(ll x = 1; x <= n; x ++)
		res = res * x % P;
	ll inv = 1;
	for(ll x = 1; x <= n - k; x ++)
		inv = inv * x % P;
	for(ll x = 1; x <= k; x ++)
		inv = inv * x % P;
	return res * powMod(inv, P - 2, P) % P;
}

ll dp(ll n){
	static bool done[1000011];
	static ll memo[1000011];
	if(n == 0) return 1;
	if(done[n])
		return memo[n];
	done[n] = true;
	int k = log2[n];
	ll p = n - ((1 << k) - 1);
	ll l, r;
	if(p <= (1 << (k - 1)))
		l = p + (1 << (k - 1)) - 1, r = (1 << (k - 1)) - 1;
	else
		l = (1 << k) - 1, r = n - l - 1;
	return memo[n] = dp(l) * dp(r) % P * bino(l + r, l) % P;
}

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &P);
	for(int i = 0; 1 << i <= N; i ++)
		log2[1 << i] = i;
	for(int i = 2; i <= N; i ++)
		if(log2[i] == 0)
			log2[i] = log2[i - 1];
	printf("%lld\n", dp(N));
}
