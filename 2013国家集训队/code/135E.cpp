#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kMod = 1000000007;
int fact[1000005], invfact[1000005];
int plus(int a, int b) {
	return (a + b) % kMod;
}
int minus(int a, int b) {
	return ((a-b)%kMod+kMod)%kMod;
}
int mul(int a, int b) {
	return (ll)a * b % kMod;
}
int powMod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = mul(a, a);
		if ( n & 1 )
			res = mul(res, a);
	}
	return res;
}
int calcInv(int x) {
	return powMod(x, kMod-2);
}
int bino(int n, int k) {
	if ( n < 0 || k < 0 || k > n ) return 0;
	return mul(fact[n], mul(invfact[k], invfact[n-k]));
}

int calc(int k, int n, int a, int b) {
	if ( a < 0 || b < 0 ) return 0;
	if ( max(a, b) > k ) return 0;
	if ( a + b <= n ) 
		return mul(mul(bino(k, a), fact[a]), mul(mul(bino(k, b), fact[b]), powMod(k, n-a-b)));
	else {
		int t = a+b-n;
		int res = mul(bino(k, b), fact[b]);
		res = mul(res, mul(bino(k-t, a-t), fact[a-t]));
		return res;
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int k, w;
	scanf("%d%d", &k, &w);

	fact[0] = invfact[0] = 1;
	for ( int i = 1; i <= k; i ++ ) {
		fact[i] = mul(fact[i-1], i);
		invfact[i] = mul(invfact[i-1], calcInv(i));
	}

	int res = 0;
	for ( int n = w+1; n <= k+w; n ++ ) {
		int tmp = 0;
		tmp = plus(tmp, calc(k, n, n-w, n-w));
		tmp = minus(tmp, calc(k, n, n-(w-1), n-(w-1)));
		res = plus(res, tmp);
	}
	printf("%d\n", res);
}
