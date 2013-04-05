#include <cstdio>
#include <algorithm>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
typedef long long bignum_t;
const int N_MAX = 5001;
struct Staff
{
	bignum_t h, v, f;
	bool operator< (const Staff &x) const
	{
		return f < x.f;
	}
} staff[N_MAX];
int n, A, B, C;
int minH[N_MAX], minV[N_MAX];

inline bool check(int k)
{
	return (staff[k].f <= C + minH[k] * A + minV[k] * B);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &n, &A, &B, &C);
	for(int i = 1; i <= n; i ++)
	{
		scanf("%lld%lld", &staff[i].h, &staff[i].v);
		staff[i].f = (bignum_t)A * staff[i].h + B * staff[i].v;
	}
	std::sort(staff + 1, staff + 1 + n);
	minH[1] = staff[1].h, minV[1] = staff[1].v;
	for(int i = 2; i <= n; i ++)
	{
		minH[i] = MIN(minH[i - 1], staff[i].h);
		minV[i] = MIN(minV[i - 1], staff[i].v);
	}
	int l = 1, r = n + 1, mid = (l + r) / 2;
	while(l < r - 1)
	{
		if(check(mid))
			l = mid;
		else
			r = mid - 1;
		mid = (l + r) / 2;
	}
	printf("%d\n", l);
}
