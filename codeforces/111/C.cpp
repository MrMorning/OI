#include <cstdio>
#include <algorithm>
#include <iostream>
typedef long long ll;
using namespace std;
int a[100010];
int n;
ll k;

int main() {
	//freopen("t.in", "r", stdin);
	cin >> n >> k;
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &a[i]);
	sort(a, a + n);
	int f;
	for ( int i = 0; i < n; i ++ ) {
		int st = i;
		while ( i + 1 < n && a[i + 1] == a[i] ) 
			i ++;
		if ( (ll)st * n + 1 <= k && k <= (ll)(i + 1) * n ) {
			k -= (ll)st * n;
			f = a[i];
			break;
		}
	}
	int cnt = 0;
	for ( int i = 0; i < n; i ++ )
		if ( a[i] == f ) 
			cnt ++;
	for ( int i = 0; i < n; i ++ ) {
		ll l = (ll)i * cnt + 1, 
		   r = (ll)(i + 1) * cnt;
		if ( l <= k && k <= r ) {
			printf("%d %d\n", f, a[i]);
			return 0;
		}
	}
}
