#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

bool same_digit(ll x) {
	int t = x % 10;
	while ( x ) {
		if ( x % 10 != t )
			return false;
		x /= 10;
	}
	return true;
}	

ll extend(ll x, int M, int N) {
	while ( 1 ) {
		int bonus = 0;
		if ( x % 5 == 0 )
			bonus += M;
		if ( same_digit(x) )
			bonus += N;
		if ( bonus == 0 )
			break;
		x += bonus;
	}
	return x;
}

ll solve(int M, int N) {
	ll res = 0;
	for ( ll x = 1; x <= 10000; x ++ ) 
		res = max(res, extend(x, M, N));
	return res;
}
int main() {
//	freopen("t.in", "r", stdin);
	for ( int M = 1; M <= 50; M ++ )
			for ( int N = 1; N <= 50; N ++ )
				cout << M << ' ' << N << ' ' << solve(M, N) << '\n';
}
