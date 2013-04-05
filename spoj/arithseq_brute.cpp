#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll POW[16];
struct Stuff {
	int pos;
   	ll sum;
} stuff[1000000];
int A, D, N, X;

int calcDig(ll x) {
	ll tmp = x;
	int res = 0;
	while ( tmp ) {
		if ( tmp % 10 == X )
			res ++;
		tmp /= 10;
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);

	scanf("%d%d%d%d", &A, &D, &N, &X);
	ll ans = 0;
	for ( ll x = A; x <= A + (ll)N * D; x += D )
		ans += calcDig(x);
	cout << ans;
}
