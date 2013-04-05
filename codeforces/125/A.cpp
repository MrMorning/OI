
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}

int main(){
//	freopen("t.in", "r", stdin);
	ll k, b, n, t;
	cin >> k >> b >> n >> t;
	{
		ll tmp = 1;
		for ( int i = 0; i < n; i ++ ) {
			tmp = tmp * k + b;
			if ( tmp > t ) 
				break;
		}
		if ( tmp <= t ) {
			puts("0");
			return 0;
		}
	}
	ll acc = 1;
	int ans = (int)n;
	for ( int i = 0; ; i ++ ) {
		acc = acc * k + b;
		if ( t >= acc ) {
			ans = min(ans, (int)(n - i - 1));
		} else break;
	}
	printf("%d\n", ans);
}
