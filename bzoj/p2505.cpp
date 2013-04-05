#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int D_MAX = 19;
const int S_MAX = 18 * 9 + 1;
const int K_MAX = 1010;
struct Info {
	ll a;
	int b;
	Info(){}
	Info (ll _a, int _b):
		a(_a), b(_b){}
} memo[D_MAX][S_MAX][K_MAX];
bool done[D_MAX][S_MAX][K_MAX];
int upper;
ll L, R, pow[19];
int a[20], b[20];

inline Info merge(const Info &I1, const Info &I2) {
	return Info(I1.a + I2.a, I2.b);
}
Info dp(int h, int sum, int rem) {
	if ( done[h][sum][rem] )
		return memo[h][sum][rem];
	done[h][sum][rem] = true;
	Info &res = memo[h][sum][rem] = Info(0, rem);
	if ( h == 0 ) {
		if ( rem > 0 )
			res.a = 0, res.b = rem > sum ? rem - sum : 0;
		else
			res.a = 1, res.b = max(0, upper - sum);
	} else {
		for ( int x = 0; x <= 9; x ++ )
			res = merge(res, dp(h - 1, sum + x, res.b));
	}
	return res;
}

int count_dig(ll x) {
	int res = 0;
	while ( x )
		res ++, x /= 10;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	pow[0] = 1;
	for ( int i = 1; i < 19; i ++ )
		pow[i] = pow[i - 1] * 10;
	scanf("%lld%lld%d", &L, &R, &upper);
	L --, R ++;
	
	int n = count_dig(R);
	for ( int i = 1; i <= n; i ++ ) {
		a[i] = L / pow[n - i] % 10;
		b[i] = R / pow[n - i] % 10;
	}
	int lca;
	for ( lca = 0; a[lca + 1] == b[lca + 1]; lca ++ );
	Info res(0, 0);
	for ( int i = n; i >= 2 + lca; i -- ) {
		int sum = 0;
		for ( int j = 1; j < i; j ++ )
			sum += a[j];
		for ( int x = a[i] + 1; x <= 9; x ++ )
			res = merge(res, dp(n - i, sum + x, res.b));
	}
	{
		int sum = 0;
		for ( int i = 1; i <= lca; i ++ )
			sum += a[i];
		for ( int x = a[lca + 1] + 1; x <= b[lca + 1] - 1; x ++ )
			res = merge(res, dp(n - 1 - lca, x + sum, res.b));
	}
	for ( int i = 2 + lca; i <= n; i ++ ) {
		int sum = 0;
		for ( int j = 1; j < i; j ++ )
			sum += b[j];
		for ( int x = 0; x <= b[i] - 1; x ++ )
			res = merge(res, dp(n - i, sum + x, res.b));
	}
	printf("%lld\n", res.b == 0 ? res.a : res.a - 1);
}
