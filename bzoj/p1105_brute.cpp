#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int N_MAX = 1000010;
int n, x[N_MAX], y[N_MAX], w[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d%d%d", &x[i], &y[i], &w[i]);
	ll all_res1, all_res2;
	all_res1 = all_res2 = 0x3f3f3f3f3f3f3f3fLL;
	for (int s = 0, lim = 1 << n; s < lim; s ++) {
		int minX = inf, minY = inf,
			maxX = -inf, maxY = -inf;
		ll res2 = 0;
		for (int i = 0; i < n; i ++)
			if (s & (1 << i)) {
				minX = min(minX, y[i + 1]);
				maxX = max(maxX, y[i + 1]);
				minY = min(minY, x[i + 1]);
				maxY = max(maxY, x[i + 1]);
				res2 += w[i + 1];
			}
			else {
				minX = min(minX, x[i + 1]);
				maxX = max(maxX, x[i + 1]);
				minY = min(minY, y[i + 1]);
				maxY = max(maxY, y[i + 1]);
			}
		ll res1 = ((ll)maxX - minX + maxY - minY) * 2;
		if (res1 < all_res1) {
			all_res1 = res1;
			all_res2 = res2;
		}
		else if (res1 == all_res1 && res2 < all_res2) 
			all_res2 = res2;
	}
	printf("%lld %lld\n", all_res1, all_res2);
}
