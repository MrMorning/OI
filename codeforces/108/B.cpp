#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f;

int n, m;
int xc, yc, k;
ll ans = 0;

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	scanf("%d%d", &xc, &yc);
	scanf("%d", &k);
	while ( k -- ) {
		int dx, dy;
		scanf("%d%d", &dx, &dy);
		int low = inf;
		if ( dx != 0 ) {
			if ( dx > 0 )
				low = min(low, (n - xc) / dx);
			else
				low = min(low, (1 - xc) / dx);
		} 
		if ( dy != 0 ) {
			if ( dy > 0 )
				low = min(low, (m - yc) / dy);
			else
				low = min(low, (1 - yc) / dy);
		}
		ans += low;
		xc += dx * low, yc += dy * low;
	}
	cout << ans;
}
