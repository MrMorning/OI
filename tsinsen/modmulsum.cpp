#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll kMod = 19940417;

int plus(int a, int b) {
	return (a + b)%kMod;
}

int minus(int a, int b) {
	return (a - b + kMod) % kMod;
}

int mul(int a, int b) {
	return (ll)a * b % kMod;
}

int arith(int i, int j) {
	int a = i+j,
		b = j-i+1;
	if ( a % 2 == 0 ) return mul(a/2, b);
	else return mul(a, b/2);
}

int calc(int n) {
	if ( n == 0 ) return 0;
	int a = n, b = n+1, c = 2*n+1;
	if ( a % 2 == 0 ) a /= 2;
	else b /= 2;
	if ( a % 3 == 0 ) a /= 3;
	else if ( b % 3 == 0 ) b /= 3;
	else {
		assert(c % 3 == 0);
		c /= 3;
	}
	return mul(a, mul(b, c));
}

int arith2(int i, int j) {
	return minus(calc(j), calc(i-1));
}

int bruteF(int n, int m) {
	int res = 0;
	for ( int i = 1; i <= n; i ++ )
		res = plus(res, mul(i,m/i));
	return res;
}

int bruteF2(int n, int m) {
	if ( n > m ) swap(n, m);
	int res = 0;
	for ( int i = 1; i <= n; i ++ )
		res = plus(res, mul(n/i,mul(m/i,mul(i,i))));
	return res;
}

int f(int n, int m) {
	n = min(n, m);
	int res = 0;
	for ( int i = 1; ; ) {
		int j = min(n, m / (m / i));
		res = plus(res, mul(arith(i, j), m/i));
		if ( j == n ) break;
		i = j+1;
	}
	return res;
}

int f2(int n, int m) {
	if ( n > m ) swap(n, m);
	int res = 0;
	for ( int i = 1; ; ) {
		int j = min(n/(n/i), m/(m/i));
		assert(j <= n);
		res = plus(res, mul(arith2(i, j), mul(n/i,m/i)));
		if ( j == n ) break;
		i = j + 1;
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	if ( n > m ) swap(n, m);
	int res = mul(minus(mul(n,n),f(n,n)), minus(mul(m,m), f(m,m)));
	res = minus(res, mul(n,mul(n,m)));
	res = plus(res, mul(n,f(n,m)));
	res = plus(res, mul(m,f(n,n)));
	res = minus(res, f2(n,m));
	printf("%d\n", res);
}
