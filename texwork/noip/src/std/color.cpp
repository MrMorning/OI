#include <cstdio>
#include <cstring>
typedef long long ll;
const int MOD = 1000000007;
void mulMat(int c[][2], int a[][2], int b[][2]){
	static int z[2][2];
	memset(z, 0, sizeof(z));
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
			for(int k = 0; k < 2; k ++)
				z[i][j] = ((ll)z[i][j] + (ll)a[i][k] * b[k][j]) % MOD;
	memcpy(c, z, sizeof(z));
}
ll gcd(ll a, ll b){
	return b ? gcd(b, a % b) : a;
}
void powMat(int c[][2], int a[][2], int k){
	static int z[2][2];
	memset(z, 0, sizeof(z));
	if(k & 1)
		memcpy(z, a, sizeof(z));
	else
		z[0][0] = z[1][1] = 1;
	for(k >>= 1; k; k >>= 1){
		mulMat(a, a, a);
		if(k & 1)
			mulMat(z, z, a);
	}
	memcpy(c, z, sizeof(z));
}
int powMod(int a, ll n){
	int res = n & 1 ? a : 1;
	for(n >>= 1; n; n >>= 1){
		a = (ll)a * a % MOD;
		if(n & 1)
			res = (ll)res * a % MOD;
	}
	return res;
}
int F[2][2], T[2][2], R[2][2];
ll n, p;
int main(){
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%lld%lld", &n, &p);
	if(p > n / 2){
		printf("%d\n", powMod(2, n));
		return 0;
	}
	ll m = gcd(n, p), l = n / m;
	int way;
	if(l == 1)
		way = 2;
	else{
		F[0][0] = 1, F[1][0] = 2;
		T[0][0] = 0, T[0][1] = T[1][0] = T[1][1] = 1;
		powMat(R, T, l - 3);
		mulMat(F, R, F);
		way = ((ll)F[0][0] + (ll)F[1][0] + (ll)F[0][0]) % MOD;
	}
	printf("%d\n", powMod(way, m));
}
