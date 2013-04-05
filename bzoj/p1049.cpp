#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#define pb(x) push_back(x)
using namespace std;
const int inf = 0x3f3f3f3f;
const int N_MAX = 35010;
int a[N_MAX], b[N_MAX], f[N_MAX], g[N_MAX], n;
vector<int> ptr[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 2; i <= n + 1; i ++)
		scanf("%d", &a[i]);
	a[1] = -inf, a[n + 2] = inf;
	n += 2;
	f[1] = 1, g[1] = 0;
	for (int i = 1; i <= n; i ++)
		a[i] -= i;
	b[1] = a[1];
	ptr[1].pb(1);
	int m = 1;
	for (int i = 2; i <= n; i ++) {
		int lb = 1, rb = m + 1;
		for (int mid = lb + rb >> 1; lb < rb - 1; mid = lb + rb >> 1) {
			if (b[mid] <= a[i])
				lb = mid;
			else
				rb = mid;
		}
		f[i] = lb + 1;
		g[i] = inf;
		for (int k = 0, sz = ptr[lb].size(); k < sz; k ++) {
			int j = ptr[lb][k];
			if (a[j] > a[i])
				continue;
			long long sum1 = 0, sum2 = 0;
			for (int t = i - 1; t > j; t --)
				sum2 += abs(a[t] - a[i]);
			g[i] = min((long long)g[i], g[j] + sum1 + sum2);
			for (int t = j + 1; t < i; t ++) {
				sum2 -= abs(a[t] - a[i]);
				sum1 += abs(a[t] - a[j]);
				g[i] = min((long long)g[i], g[j] + sum1 + sum2);
			}
		}
		if (lb == m) {
			b[++ m] = a[i];
			ptr[m].pb(i);
		}
		else if (b[lb + 1] == a[i])
			ptr[lb + 1].pb(i);
		else {
			assert(b[lb + 1] > a[i]);
			b[lb + 1] = a[i];
			//ptr[lb + 1].clear();
			ptr[lb + 1].pb(i);
		}
	}
	printf("%d\n%d\n", n - f[n], g[n]);
}
