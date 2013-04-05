#include <cstdio>
#include <cstring>
typedef long long ll;
const int kLenMax = 55;

int mod, root;

void add(int &x, int y) {
	x += y;
	x %= mod;
	if ( x < 0 ) x += mod;
}

int mul(int x, int y) {
	return (ll)x * y % mod;
}

int powMod(int a, int n) {
	a %= mod;
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = mul(a, a);
		if ( n & 1 ) res = mul(res, a);
	}
	return res;
}

int getDiscreteRoot(int p) {
	for ( int x = 2; ; x ++ ) {
		bool fail = false;
		for ( int y = 2; !fail && y * y <= p; y ++ )
			if ( p % y == 0 && powMod(x, p / y) == 1 ) 
				fail = true;
		if ( ! fail ) return x;
	}
}

int coef[kLenMax], res[kLenMax], tmp[kLenMax];
int A[kLenMax], B[kLenMax], C[kLenMax], resA[kLenMax], resB[kLenMax], resC[kLenMax], X[30][kLenMax];

void fft(int delta, int step, int size, bool nega) {
	if ( size == 1 ) { res[delta] = coef[delta]; return; }
	int k;
	for ( k = 2; ; k ++ ) if ( size % k == 0 ) break;
	for ( int i = 0; i < k; i ++ ) fft(delta + i * step,  step * k, size / k, nega);
	int acc = 1, pri = powMod(root, (mod - 1) / size);
	if ( nega ) pri = powMod(pri, mod - 2);
	for ( int i = 0; i < size; i ++, acc = mul(acc, pri) ) {
		tmp[delta + i * step] = 0;
		for ( int j = 0, cur = 1; j < k; j ++, cur = mul(cur, acc) )
			add(tmp[delta + i * step], mul(cur, res[delta + j * step + (i % (size / k)) * step * k]));
	}
	for ( int i = 0; i < size; i ++ ) res[delta + i * step] = tmp[delta + i * step];
}

int main() {
	freopen("t.in", "r", stdin);
	int n, Q;

	scanf("%d%d", &n, &Q);
	mod = n + 1;
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d", &A[i]); A[i] %= mod;
	}
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d", &B[i]); B[i] %= mod;
	}
	for ( int i = 0; i < n; i ++ )
		X[0][i] = A[i];
	for ( int i = 0; i < Q; i ++ )
		for ( int j = 0; j < n; j ++ )
			for ( int k = 0; k < n; k ++ )
				add(X[i+1][(j + k) % n], mul(B[k], X[i][j]));
	for ( int i = 0; i < n; i ++ )
		printf("%d\n", X[Q][i]);
}
