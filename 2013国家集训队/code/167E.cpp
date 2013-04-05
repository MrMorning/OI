#include <cstdio>
#include <cassert>
#include <vector>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
typedef long long ll;

int mod;
bool done[666][666];
int memo[666][666];
vector<int> adj[666];
int mat[666][666];
int inDgr[666], outDgr[666];
int sink[666], src[666];
int nSrc, nSink;

void add(int &a, int b) {
	a += b;
	a %= mod;
}

int minus(int a, int b) {
	return ((a-b)%mod+mod)%mod;
}

inline int mul(int a, int b) {
	return (ll)a * b % mod;
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
	return powMod(x, mod-2);
}

int dp(int des, int cur) {
	if ( done[des][cur] ) return memo[des][cur];
	done[des][cur] = true;
	int &res = memo[des][cur] = 0;
	if ( des == cur ) return res = 1;
	foreach(it, adj[cur])
		add(res, dp(des, *it));
	return res;
}

int gauss(int n) {
	int det = 1;
	for ( int i = 1, j = 1; i <= n; i ++ ) {
		int p;
		for ( p = j; p <= n; p ++ )
			if ( mat[p][i] ) break;
		if ( p == n+1 ) continue;
		if ( p != j ) {
			for ( int k = 1; k <= n; k ++ ) swap(mat[j][k], mat[p][k]);
			det = mul(det, mod-1);
		}
		int tmp = calcInv(mat[j][i]);
		for ( int k = 1; k <= n; k ++ ) 
			mat[j][k] = mul(mat[j][k], tmp);
		det = mul(det, tmp);
		for ( p = 1; p <= n; p ++ )
			if ( p != j && mat[p][i] ) {
				int tmp = mat[p][i];
				for ( int k = 1; k <= n; k ++ )
					mat[p][k] = minus(mat[p][k], mul(tmp, mat[j][k]));
			}
		j++;
	}
	det = calcInv(det);
	for ( int i = 1; i <= n; i ++ )
		det = mul(det, mat[i][i]);
	return det;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d%d", &n, &m, &mod);
	while ( m -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b); 
		inDgr[b]++;
		outDgr[a]++;
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( inDgr[i] == 0 ) 
			src[++nSrc] = i;
		if ( outDgr[i] == 0 )
			sink[++nSink] = i;
	} 
	assert(nSrc == nSink);
	for ( int i = 1; i <= nSrc; i ++ )
		for ( int j = 1; j <= nSink; j ++ )
			mat[i][j] = dp(sink[j], src[i]);

	printf("%d\n", gauss(nSrc));
}

