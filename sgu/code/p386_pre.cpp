
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long double val_t;
const val_t kEps = 1e-8;
int n, mod;
int a[55][55], coef[55][55];
val_t b[55][55];

int sgn(val_t x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

int powMod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = a*a % mod;
		if ( n & 1 )
			res = res*a%mod;
	}
	return res;
}

int calcInv(int x) {
	return powMod(x, mod-2);
}

int calcDet1() {
	int ret = 1;
	for ( int i = 1, j = 1; i <= n; i ++ ) {
		int p;
		for ( p = j; p <= n; p ++ )
			if ( a[p][i] != 0 ) break;
		if ( p == n+1 ) return 0;
		if ( p != j ) {
			ret = ret*(mod-1)%mod;
			for ( int k = 1; k <= n; k ++ ) 
				swap(a[p][k], a[j][k]);
		}
		int tmp = calcInv(a[j][i]);
		ret = ret*a[j][i]%mod;
		for ( int k = 1; k <= n; k ++ ) 
			a[j][k] = a[j][k]*tmp%mod;
		for ( p = 1; p <= n; p ++ )
			if ( p != j && a[p][i] != 0 ) {
				tmp = a[p][i];
				for ( int k = 1; k <= n; k ++ )
					a[p][k] = ((a[p][k]-tmp*a[j][k])%mod+mod)%mod;
			}
		j ++;
	}
	return ret;
}
val_t calcDet2() {
	val_t ret = 1;
	for ( int i = 1, j = 1; i <= n; i ++ ) {
		int p;
		for ( p = j; p <= n; p ++ )
			if ( sgn(b[p][i]) ) break;
		if ( p == n+1 ) return 0;
		if ( p != j ) {
			ret = ret*-1;
			for ( int k = 1; k <= n; k ++ ) 
				swap(b[p][k], b[j][k]);
		}
		val_t tmp = 1/b[j][i];
		ret = ret*b[j][i];
		for ( int k = 1; k <= n; k ++ ) 
			b[j][k] = b[j][k]*tmp;
		for ( p = 1; p <= n; p ++ )
			if ( p != j && b[p][i] != 0 ) {
				tmp = b[p][i];
				for ( int k = 1; k <= n; k ++ )
					b[p][k] = b[p][k]-tmp*b[j][k];
			}
		j ++;
	}
	return ret;
}

int spare[10007];
int nSpare;
val_t test;

bool cmp(int x, int y) {
	return fabs(x-test) < fabs(y-test);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &mod);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ )
			scanf("%d", &coef[i][j]);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) {
			a[i][j] = coef[i][j];
			a[i][j] %= mod;
			b[i][j] = coef[i][j];
		}

	int vol = calcDet1();
	test = calcDet2();

	if ( sgn(test) < 0 ) vol = (mod-vol)%mod; 

	int res = (int)((1LL<<n)%mod)*vol%mod;
	printf("%d\n", res);
}
