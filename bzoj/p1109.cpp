#include <cstdio>
#include <algorithm>
using namespace std;
const int N_MAX = 100010;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> pair_t;
int _a[N_MAX], g[N_MAX], f[N_MAX];
pair_t a[N_MAX];
int n;
bool cmp(const pair_t &a, const pair_t &b) {
	return a.first > b.first || (a.first == b.first && a.second < b.second);
}
int main() {
	freopen("t.in", "r", stdin);
	int _n;
	scanf("%d", &_n);
	for (int i = 1; i <= _n; i ++) {
		scanf("%d", &_a[i]);
		if (_a[i] - i <= 0)
			a[++ n] = make_pair(_a[i] - i, _a[i]);
	}
	sort(a + 1, a + 1 + n, cmp);
	int m = 0;
	for (int i = 1; i <= n; i ++) {
		int lb = 0, rb = m + 1;
		for (int mid = (lb + rb) >> 1; lb < rb - 1;
				mid = (lb + rb) >> 1) {
			if (a[i].second > g[mid])
				lb = mid;
			else
				rb = mid;
		}
		f[i] = lb + 1;
		if (lb == m)
			g[++ m] = a[i].second;
		else
			g[lb + 1] = a[i].second;
	}
	int res = 0;
	for (int i = 1; i <= n; i ++)
		res = max(res, f[i]);
	printf("%d\n", res);
}
