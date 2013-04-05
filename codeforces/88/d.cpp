#include <cstdio>
#include <cmath>
#include <algorithm>
#ifdef unix
	#define LL_FMT "%lld"
#else
	#define LL_FMT "%I64d"
#endif
#define M(x) (((x) + modVal) % modVal)
typedef long long ll;
using namespace std;
ll u, v;
int modVal, m;
ll n;
inline ll ceilDiv(ll a, ll b)
{
	if(a % b == 0)
		return a / b;
	else if ((a >= 0 && b >= 0) || (a <= 0 && b <= 0))
		return a / b + 1;
	else
		return a / b;
}
inline ll floorDiv(ll a, ll b)
{
	if(a % b == 0 || (a >= 0 && b >= 0) || (a <= 0 && b <= 0))
		return a / b;
	else
		return a / b - 1;
}
ll ask(ll a1, ll d, ll n, ll l, ll r)
{
	if(l == 1 && r == n)
	{
		ll p = 1 + ceilDiv(u - a1, d),
		   q = 1 + floorDiv(v - a1, d);
		p = max(1LL, p);
		q = min(n, q);
		if(p > q)
			return 0LL;
		ll ap = a1 + (p - 1) * d, cnt = q - p + 1, val;
		if(cnt & 1)
			val = M(M(ap) + M(M((q - p) / 2) * M(d)));
		else
			cnt >>= 1, val = M(M(ap) * 2 + M(q - p) * M(d));
		return M(M(cnt) * M(val));
	}
	ll mid = ceilDiv(n, 2);
	ll res = 0;
	if(l <= mid)
		res += ask(a1, d << 1, mid, l, min(r, mid));
	if(r > mid)
		res += ask(a1 + d, d << 1, n - mid, max(l - mid, 1LL), r - mid);
	return M(res);
}

int main()
{
	scanf(LL_FMT "%d%d", &n, &m, &modVal);
	while(m --)
	{
		ll l, r;
		scanf(LL_FMT LL_FMT LL_FMT LL_FMT, &l, &r, &u, &v);
		printf(LL_FMT "\n", ask(1, 1, n, l, r));
	}
}
