#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 1000010;
const int inf = 0x3f3f3f3f;
const ll inf_ll = 0x3f3f3f3f3f3f3f3fLL;
int n;
int x[N_MAX], y[N_MAX], w[N_MAX];
ll res, best;
char out[N_MAX];
void test(int minX, int minY, int maxX, int maxY) {
	static char tmp[N_MAX];
	ll acc = 0;
	for (int i = 1; i <= n; i ++) {
		if (minX <= x[i] && x[i] <= maxX
				&& minY <= y[i] && y[i] <= maxY)
			tmp[i] = '0';
		else {
			if (minX <= y[i] && y[i] <= maxX
					&& minY <= x[i] && x[i] <= maxY)
				tmp[i] = '1', acc += w[i];
			else
				return;
		}
	}
	if (acc < best) {
		best = acc;
		memcpy(out + 1, tmp + 1, sizeof(char) * n);
	}
}
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d%d%d", &x[i], &y[i], &w[i]);
	int minX = inf, minY = inf,
		maxX = -inf, maxY = -inf;
	for (int i = 1; i <= n; i ++) {
		int p = x[i], q = y[i];
		if (p > q)
			swap(p, q);
		minX = min(p, minX);
		minY = min(q, minY);
		maxX = max(p, maxX);
		maxY = max(q, maxY);
	}
	res = ((ll)maxX - minX + maxY - minY) * 2;
	best = inf_ll;
	test(minX, minY, maxX, maxY);
	test(minY, minX, maxX, maxY);
	test(minX, minY, maxY, maxX);
	test(minY, minX, maxY, maxX);
	printf("%lld %lld\n", res, best);
	printf("%s", out + 1);
}
