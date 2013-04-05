#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long double val_t;
val_t kEps = 1e-8;
int n;
int nArr;
pair<val_t, val_t> arr[500010];
int sgn(val_t x) {
    if ( fabs(x) < kEps ) return 0;
    return x > 0 ? 1 : -1;
}
bool contain(int i, val_t x, val_t y) {
    val_t a = arr[i].first, b = arr[i].second;
    return sgn(x*x-2*a*x+y*y-2*b*y) <= 0;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	while ( n -- ) {
		int t;
		double xx, yy;
		scanf("%d", &t);
		scanf("%lf%lf", &xx, &yy);
		val_t x = xx, y = yy;
		if ( t == 0 ) {
			arr[nArr++] = make_pair(x, y);
		} else {
			if ( nArr == 0 ) {
				puts("No");
				continue;
			}
			bool found = true;
			for ( int i = 0; i < nArr; i ++ )
				if ( !contain(i, x, y) ) {
					found = false;
					break;
				}
			if ( found ) puts("Yes");
			else puts("No");
		}
	}
}
