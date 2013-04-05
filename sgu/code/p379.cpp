#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
int A[111], B[111];
int N, C, P, T;

ll ceilDiv(ll a, ll b) {
	if ( a % b == 0 ) return a / b;
	return a / b + 1;
}

bool check(ll tot) {
	memcpy(B, A, sizeof(A));
	ll acc = 0;
	for ( int i = 1; i <= N; i ++ ) {
		if ( acc+1 <= tot && acc + A[i] >= tot ) {
			B[i] = tot-acc;
			for ( int j = i+1; j <= N; j ++ )
				B[j] = 0;
			break;
		}
		acc += A[i];
	}
	ll res = 0, rem = 0;
	for ( int i = N; i >= 1; i -- )
		if ( B[i] ) {
			if ( rem != 0 ) {
				if ( B[i] < rem ) {
					rem -= B[i];
					B[i] = 0;
					continue;
				} else {
					B[i] -= rem;
					rem = 0;
				}
			}
			assert(rem == 0);
			res += 2LL*i*P*ceilDiv(B[i], C);
			if ( B[i] % C == 0 )
				rem = 0;
			else
				rem = ceilDiv(B[i],C)*C-B[i];
			B[i] = 0;
		}
	return res <= T;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &N, &C, &P, &T);
	ll tot = 0;
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%d", &A[i]);
		tot += A[i];
	}

	ll lb = 0, rb = tot+1;
	while ( lb < rb-1 ) {
		ll mid = (lb + rb) / 2;
		if ( check(mid) )
			lb = mid;
		else
			rb = mid;
	}
	printf(LL_FMT "\n", lb);
}
