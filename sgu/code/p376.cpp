#include <cstdio>
#include <algorithm>
#include <functional>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
using namespace std;

const int kNMax = 1010;

ll val[kNMax], W[kNMax], R[kNMax], P[kNMax];
ll A[kNMax], B[kNMax], arr[kNMax], S[kNMax];
int n, m;

bool cmpCan(ll i, ll j) {
	return val[i] < val[j] || (val[i] == val[j] && P[i] > P[j]);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		scanf(LL_FMT LL_FMT LL_FMT, &W[i], &R[i], &P[i]);
	for ( int i = 1; i <= m; i ++ )
		scanf(LL_FMT, &A[i]);
	for ( int i = 1; i <= n; i ++ )
		scanf(LL_FMT, &B[i]);

	for ( int i = 1; i <= n; i ++ )
		val[i] = 20000000-W[i];
	for ( int i = 1; i <= n; i ++ )
		arr[i] = i;
	sort(arr+1, arr+1+n, cmpCan);
	for ( int i = 1; i <= m; i ++ ) {
		for ( int j = 1; j <= n; j ++ )
			S[j] = 3*A[i]*A[i] + 5*A[i]*B[j] + 2*B[j]*B[j];
		sort(S+1, S+1+n, greater<ll>());
		for ( int j = 1; j <= n; j ++ )
			val[arr[j]] += 20000000-R[arr[j]]-S[j];
		sort(arr+1, arr+1+n, cmpCan);
	}
	for ( int i = 1; i <= n; i ++ )
		printf(LL_FMT " ", arr[i]);
}
