#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 15000;

struct City
{
	int pos, val;
} city[N_MAX];
int n;

bool cmp(const City &a, const City &b)
{
	return a.pos < b.pos;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d%d", &city[i].pos, &city[i].val);
	sort(city, city + n, cmp);
	ll acc = 0, lsum = 0, rsum = 0;
	for(int i = n - 1; i > 0; i --)
	{
		rsum += city[i].val;
		acc += rsum * (city[i].pos - city[i - 1].pos);
	}
	ll best = acc;
	int ans = 0;
	rsum += city[0].val;
	for(int i = 1; i < n; i ++)
	{
		lsum += city[i - 1].val;
		rsum -= city[i - 1].val;
		acc = acc + (lsum - rsum) * (city[i].pos - city[i - 1].pos);
		if(acc < best)
			best = acc, ans = i;
	}
	printf("%d.00000", city[ans].pos);
}
