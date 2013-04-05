#include <cstdio>
#include <algorithm>
using namespace std;
int n, s;
int c[7];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &s);
	for ( int i = 0; i < n; i ++ ) {
		int x;
		scanf("%d", &x);
		c[x]++;
	}
	int ans = 0x3f3f3f3f, ansK3, ansK4, ansK5;
	for ( int k4 = 0; k4*c[4] <= s; k4 ++ )
		for ( int k3 = 0; k3 <= k4; k3 ++ ) {
			int k5 = s-k3*c[3]-k4*c[4];
			if ( k5 % c[5] != 0 ) continue;
			k5 /= c[5];
			if ( k5 < k4 ) continue;
			int val = abs(c[3]*k3-c[4]*k4)+abs(c[4]*k4-c[5]*k5);
			if ( val < ans ) {
				ans = val;
				ansK3 = k3, ansK4 = k4, ansK5 = k5;
			}
		}
	if ( ans == 0x3f3f3f3f ) puts("-1");
	else printf("%d\n", ans);
	//printf("%d %d %d\n", ansK3, ansK4, ansK5);
}
