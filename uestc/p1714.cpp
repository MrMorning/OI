#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

ll A[1<<20], B[1<<20], C[1<<20];
int bitsCnt[1<<22], log2[1<<22];
int edCntLeft[1<<22], edCntRight[1<<22], xorAcc[1<<22];
ll adj[44];
int n1, n2, n, sz;

void init() {
#define MS(X) memset(X, 0, sizeof(X));
	MS(A); MS(B); MS(C); MS(bitsCnt);
	MS(log2); MS(edCntLeft); MS(edCntRight); MS(xorAcc);
	MS(adj);
}

void expandLeft(int s) {
	if ( s ) {
		int u = log2[s & -s];
		edCntLeft[s] = edCntLeft[s - (s & -s)] ^ (bitsCnt[(adj[u] & ((1 << n1) - 1)) & (s - (s & -s))] & 1);
		xorAcc[s] = xorAcc[s - (s&-s)] ^ (adj[u] >> n1);
	}
	A[(xorAcc[s] << 2) | (edCntLeft[s] << 1) | 1] ++;
}

void expandRight(int s) {
	if ( s ) {
		int u = log2[s & -s] + n1;
		edCntRight[s] = edCntRight[s - (s & -s)] ^ (bitsCnt[(adj[u] >> n1) & (s - (s & -s))] & 1);
	}
	B[(s << 2) | 1 << 1 | edCntRight[s]] ++;
}

void transform(ll *X, int l, int r) {
	if ( l == r ) return;
	int mid = (l + r) / 2;
	transform(X, l, mid);
	transform(X, mid + 1, r);
	for ( int k = mid + 1; k <= r; k ++ ) 
		X[k - mid - 1 + l] += X[k];
}

void untransform(ll *X, int l, int r) {
	if ( l == r ) return;
	int mid = (l + r) / 2;
	for ( int k = mid + 1; k <= r; k ++ ) 
		X[k - mid - 1 + l] -= X[k];
	untransform(X, l, mid);
	untransform(X, mid + 1, r);
}

void solve() {
	int t;
	scanf("%d%d", &n, &t);
	while ( t -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;
		adj[a] |= 1LL << b;
		adj[b] |= 1LL << a;
	}
	n2 = max(0, n / 2 - 2), n1 = n - n2;
	sz = 1 << (n2 + 2);
	for ( int i = 0; i < max(n2 + 2, n1); i ++ )
		log2[1<<i] = i;
	for ( int i = 1, lim = 1 << max(n2 + 2, n1); i < lim; i ++ ) {
		bitsCnt[i] = bitsCnt[i - (i & -i)] + 1;
		if ( i > 1 && log2[i] == 0 ) log2[i] = log2[i-1];
	}

	for ( int s = 0, lim = 1 << n1; s < lim; s ++ )
		expandLeft(s);
	for ( int s = 0, lim = 1 << n2; s < lim; s ++ )
		expandRight(s);
	transform(A, 0, sz - 1);
	transform(B, 0, sz - 1);
	for ( int i = 0; i < sz; i ++ )
		C[i] = A[i] * B[i];
	untransform(C, 0, sz - 1);
	ll ans = 0;
	for ( int i = 0; i < sz; i ++ )
		if ( bitsCnt[i] & 1 ) 
			ans += C[i];
	printf(LL_FMT "\n", ans);
}

int main() {
	int tst;
	scanf("%d", &tst);
	for ( int t = 0; t < tst; t ++ ) {
		printf("Case #%d: ", t + 1);
		init();
		solve();
	}
}
