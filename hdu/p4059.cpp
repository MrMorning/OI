#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int64;

const int PRIME_MAX = 10000;
const int N_PRIME_MAX = 10000;
const int MOD = 1000000007;

int prime[N_PRIME_MAX];
bool notprime[PRIME_MAX];
int nPrime, nFactor;
int64 factor[30];


int64 MUL(int64 a, int64 b){
	a %= MOD;
	b %= MOD;
	return a * b % MOD;
}

int64 powMod(int64 a, int64 n){
	a %= MOD;
	int64 res = n & 1 ? a : 1;
	for(n >>= 1; n; n >>= 1){
		a = a * a % MOD;
		if(n & 1)
			res = res * a % MOD;
	}
	return res;
}

int64 calcSum(int64 n){
	int64 res = n % MOD;
	res = MUL(res, n + 1);
	res = MUL(res, MUL(2, n) + 1);
	res = MUL(res, (3 * MUL(n, n) % MOD + MUL(3, n) - 1 + MOD) % MOD);
	res = MUL(res, powMod(30, MOD - 2));
	return res;
}

int64 solve(){
	int64 n;
	cin >> n;
	int64 tmp = n;
	nFactor = 0;
	for(int i = 0; i < nPrime; i ++)
		if(tmp % prime[i] == 0){
			factor[nFactor ++] = prime[i];
			while(tmp % prime[i] == 0)
				tmp /= prime[i];
		}
	if(tmp > 1)
		factor[nFactor ++] = tmp;
	int64 ans = 0;
	int upperlim = 1 << nFactor;
	for(int s = 0; s < upperlim; s ++){
		int oneCnt = 0;
		int64 acc = 1;
		for(int d = 0; d < nFactor; d ++)
			if(s & (1 << d)){
				oneCnt ++;
				acc *= factor[d];
			}
		int64 neg;
		if(oneCnt & 1)
			neg = -1;
		else
			neg = 1;
		ans = (ans + neg * MUL(powMod(acc, 4), calcSum(n / acc)));
		ans %= MOD;
		if(ans < 0)
			ans += MOD;
	}
	cout << ans << '\n';
}

int main(){
	freopen("t.in", "r", stdin);
	for(int x = 2; x < PRIME_MAX; x ++)
		if(!notprime[x]){
			prime[nPrime ++] = x;
			for(int y = x + x; y < PRIME_MAX; y += x)
				notprime[y] = true;
		}
	int T;
	scanf("%d", &T);
	while(T --)
		solve();
}
