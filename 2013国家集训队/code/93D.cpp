#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <cassert>
using namespace std;
typedef long long ll;
const int kMod = 1000000007;

map<string, int> mp;
string str[64];
const char CONV[4] = {'B', 'W', 'R', 'Y'};

bool valid(string s) {
	return s[0] != s[1] && s[1] != s[2] 
		&& s.substr(0, 2) != "WY" && s.substr(0, 2) != "RB"
		&& s.substr(1, 2) != "WY" && s.substr(1, 2) != "RB"
		&& s.substr(0, 2) != "YW" && s.substr(0, 2) != "BR"
		&& s.substr(1, 2) != "YW" && s.substr(1, 2) != "BR"
		&& s != "BWR" && s != "RWB";
}

void add(int &a, int b) {
	a += b;
	if ( a > kMod ) a %= kMod;
}

void substract(int &a, int b) {
	a -= b;
	a %= kMod;
	if ( a < 0 ) a += kMod;
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

struct Matrix {
	int ele[65][65];
	int n, m;
} IdMat, F, T;

Matrix operator* (const Matrix &A, const Matrix &B) {
	static Matrix C;
	assert(A.m == B.n);
	C.n = A.n, C.m = B.m;
	for ( int i = 0; i < C.n; i ++ )
		for ( int j = 0; j < C.m; j ++ ) {
			C.ele[i][j] = 0;
			for ( int k = 0; k < A.m; k ++ )
				add(C.ele[i][j], mul(A.ele[i][k], B.ele[k][j]));
		}
	return C;
}

Matrix powMat(Matrix A, int n) {
	Matrix res = n & 1 ? A : IdMat;
	for ( n >>= 1; n; n >>= 1 ) {
		A = A * A;
		if ( n & 1 )
			res = res * A;
	}
	return res;
}

int eval(int n) {
	if ( n == 1 ) return 0;
	else if ( n == 2 ) return 8;
	Matrix R = powMat(T, n-3);
	R = R * F;
	add(R.ele[64][0], 8);
	return R.ele[64][0];
}


int tot = 0;
void test(string cur, int tar) {
	if ( tar == 0 ) {
		tot ++;
		return;
	}
	for ( int t = 0; t < 4; t ++ ) {
		string ns = cur.substr(1, 2);
		ns += CONV[t];
		if ( valid(ns) )
			test(ns, tar-1);
	}
}

/*int bruteEval(int n) {
	if ( n == 1 ) return 0;
	if ( n == 2 ) return 8;
	tot = 8;
	for ( int s = 0; s < 64; s ++ )
		if ( valid(str[s]) ) {
			for ( int t = 3; t <= n; t ++ )
				test(str[s], t-3);
		}
	return tot;
}*/

int solve(int n) {
	if ( n == 0 ) return 0;
	else if ( n == 1 ) return 4;
	else if ( n == 2 ) return 8;
	int res = 0;
	add(res, eval(n)); // start from 3
	substract(res, 8);
	add(res, eval((n+1)/2)); // start from 2
	res = mul(res, powMod(2, kMod-2));
	add(res, 8);
	return res;
}
void init() {
	IdMat.n = IdMat.m = 65;
	for ( int i = 0; i < 65; i ++ ) IdMat.ele[i][i] = 1;
	for ( int s = 0; s < 64; s ++ ) {
		string ts;
		ts += CONV[(s>>4)&3];
		ts += CONV[(s>>2)&3];
		ts += CONV[(s>>0)&3];
		mp[ts] = s;
		str[s] = ts;
	}

	T.n = T.m = 65;
	memset(T.ele, 0, sizeof(T.ele));
	for ( int s = 0; s < 64; s ++ ) {
		if ( valid(str[s]) ) {
			for ( int t = 0; t < 4; t ++ ) {
				string ns = str[s].substr(1, 2) + CONV[t];
				if ( valid(ns) )
					T.ele[mp[ns]][s]++;
			}
		}
	}
	for ( int i = 0; i < 64; i ++ )
		for ( int j = 0; j < 64; j ++ )
			T.ele[64][j] += T.ele[i][j];
	T.ele[64][64] = 1;

	F.n = 65, F.m = 1;
	memset(F.ele, 0, sizeof(F.ele));
	for ( int s = 0; s < 64; s ++ )
		if ( valid(str[s]) ) {
			F.ele[s][0] = 1;
			F.ele[64][0] ++;
		}
}
int main() {
	freopen("t.in", "r", stdin);
	init();
	int L, R;
	scanf("%d%d", &L, &R);
	int ans = solve(R)-solve(L-1);
	if ( ans < 0 ) ans += kMod;
	printf("%d\n", ans);
}
