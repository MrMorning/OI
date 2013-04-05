#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

struct A
{
	int res, idx;
	double key;
	inline bool operator< (const A &t) const
	{
		return key > t.key;
	}
} a[1000];
int ans[1000];
int n, m;
double y, x[1000];
int cnt;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%lf", &n, &m, &y);
	for(int i = 0; i < n; i ++)
		scanf("%lf", &x[i]);
	for(int i = 0; i < n; i ++)
	{
		a[i].idx = i;
		double tmp = (double)x[i] / y * m;
		a[i].res = (int)floor(tmp);
		a[i].key = tmp - a[i].res;
		cnt += a[i].res;
	}
	sort(a, a + n);
	for(int i = 0; i < m - cnt; i ++)
		a[i].res ++;
	for(int i = 0; i < n; i ++)
		ans[a[i].idx] = a[i].res;
	for(int i = 0; i < n; i ++)
		printf("%d ", ans[i]);
}
