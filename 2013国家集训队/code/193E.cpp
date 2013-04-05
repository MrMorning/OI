#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
using namespace std;
typedef long long ll;

ll curMod;
ll mulMod(ll a, ll b) {
	ll res = b&1?a:0, acc = a;
	for ( b >>= 1; b; b >>= 1 ) {
		acc = (acc + acc) % curMod;
		if ( b & 1 ) 
			res = (res + acc) % curMod;
	}
	return res;
}

struct Matrix {
	ll ele[2][2];
} IdMat;

Matrix operator* (const Matrix &A, const Matrix &B) {
	static Matrix ret;
	for ( int i = 0; i < 2; i ++ )
		for ( int j = 0; j < 2; j ++ ) {
			ret.ele[i][j] = 0;
			for ( int k = 0; k < 2; k ++ )
				ret.ele[i][j] = (ret.ele[i][j] + mulMod(A.ele[i][k], B.ele[k][j])) % curMod;
		}
	return ret;
}

Matrix powMat(Matrix A, ll n) {
	Matrix res = n & 1 ? A : IdMat;
	for ( n >>= 1; n; n >>= 1 ) {
		A = A * A;
		if ( n & 1 )
			res = res * A;
	}
	return res;
}

ll eval(ll n) {
	if ( n == 0 ) return 0;
	IdMat.ele[0][0] = IdMat.ele[1][1] = 1;
	Matrix R, T;
	R.ele[0][0] = 1, R.ele[1][0] = 0;
	R.ele[0][1] = R.ele[1][1] = 0;
	T.ele[0][0] = T.ele[0][1] = T.ele[1][0] = 1;
	T.ele[1][1] = 0;

	T = powMat(T, n-1);
	R = T * R;
	return R.ele[0][0];
}

ll brutePow(int x, int m) {
	ll res = 1;
	for ( int i = 0; i < m; i ++ )
		res *= x;
	return res;
}

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}

int findPeriod(int M) {
	static int f[11111];
	f[0] = 0, f[1] = 1;
	for ( int i = 2; ; i ++ ) {
		f[i] = (f[i-1] + f[i-2]) % M;
		if ( f[i-1] == 0 && f[i] == 1 ) 
			return i-1;
	}
}

ll calcPeriod(int m) {
	//mod 10^m
	return lcm(findPeriod(2)*brutePow(2,m-1), findPeriod(5)*brutePow(5,m-1));
}

int nPos;
ll pos[10000], nxt[10000];
int g[1500];

int main() {
	freopen("t.in", "r", stdin);
//	{
//		curMod = 10;
//		printf(LL_FMT "\n", eval(7));
//		return 0;
//	}
	ll f;
	scanf(LL_FMT, &f);
	g[0] = 0, g[1] = 1;
	ll lim = calcPeriod(3);
	for ( int i = 2; i < lim; i ++ ) 
		g[i] = (g[i-1] + g[i-2]) % 1000;
	for ( int i = 0; i < lim; i ++ )
		if ( f % 1000 == g[i] )
			pos[nPos++] = i;


	for ( int m = 4; m <= 13; m ++ ) {
//		fprintf(stderr, "%d %d\n", nPos, m);
		//transfer from 10^m-1 to 10^m
		ll preP = calcPeriod(m-1);
		curMod = brutePow(10, m);
		int nNxt = 0;
		for ( int i = 0; i < nPos; i ++ )
			for ( int k = 0; k < 10; k ++ ) {
				ll t = pos[i] + k*preP;
				if ( eval(t) == f%curMod )
					nxt[nNxt++] = t;
			}
		nPos = nNxt;
		memcpy(pos, nxt, sizeof(pos[0])*nPos);
	}
	if ( nPos == 0 ) puts("-1");
	else printf(LL_FMT "\n", *min_element(pos, pos+nPos));
}
