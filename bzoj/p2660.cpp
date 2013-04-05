#include <cstdio>
#include <iostream>
typedef long long ll;
using namespace std;
const ll inf = 1000000000000000000LL;
ll x, fib[111], f[111][2][2];
int a[111], n_fib;
int main() {
	freopen("t.in", "r", stdin);
	fib[0] = 1, fib[1] = 2;
	n_fib = 2;
	for ( int i = 2; fib[i - 1] + fib[i - 2] <= inf; i ++ ) {
		fib[i] = fib[i - 1] + fib[i - 2];
		n_fib ++;
	}
	cin >> x;
	for ( int i = n_fib - 1; i >= 0; i -- )
		if ( x >= fib[i] ) {
			x -= fib[i];
			a[i] = 1;
		} else {
			a[i] = 0;
		}
	f[n_fib - 1][0][0] = 1;
	for ( int i = n_fib - 1; i > 0; i -- ) 
		for ( int s1 = 0; s1 <= 1; s1 ++ ) 
			for ( int s2 = 0; s2 <= 1; s2 ++ )
				if ( f[i][s1][s2] ) {
					int cur = s1 + a[i], nxt = s2 + a[i - 1];

					if ( cur == 0 ) 
						f[i - 1][s2][0] += f[i][s1][s2];
					else if ( cur == 1 ) {
						f[i - 1][s2][0] += f[i][s1][s2];
						if ( nxt == 0 )
							f[i - 1][s2 + 1][1] += f[i][s1][s2];
					} else {
						if ( nxt == 0 )
							f[i - 1][s2 + 1][1] += f[i][s1][s2];
					}
				}
	cout << f[0][0][0] + (a[0] ? 0 : f[0][1][0]);
}
