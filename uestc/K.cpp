#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int TST;

ll ceil_div(ll a, ll b) {
	if ( a % b == 0 )
		return a / b;
	return a / b + 1;
}

int main() {
	freopen("t.in", "r", stdin);

	ios::sync_with_stdio(false);
	cin >> TST;
	for ( int tst = 1; tst <= TST; tst ++ ) {
		ll N, M, K;
		cin >> N >> M >> K;
		cout << "Case #" << tst << ": ";
	//	if ( N == 1LL && M == 1LL ) {
	//		cout << "0\n";
	//		continue;
	//	}
		ll lb = -1, rb = max(N, M);
		for ( ll mid = (lb + rb) / 2;
				lb < rb - 1; mid = (lb + rb) / 2 ) {
			if ( ceil_div(N, 2 * mid + 1) * ceil_div(M, 2 * mid + 1) <= K )
				rb = mid;
			else
				lb = mid;
		}
		cout << rb << '\n';
	}
}
