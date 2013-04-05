#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const ll oo = 100000000000000000LL;

ll calc(ll x)
{
	ll t1 = 0, t2 = 0;
	for(ll y = 2; y <= x; y *= 2)
		t1 += x / y;
	for(ll y = 5; y <= x; y *= 5)
		t2 += x / y;
	return min(t1, t2);
}

int main()
{
	freopen("t.in", "r", stdin);
	int Q;
	scanf("%d", &Q);
	ll lb = 0, rb = oo;
	for(ll mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
		if(calc(mid) < Q)
			lb = mid;
		else
			rb = mid;
	if(calc(rb) == Q)
		printf(LL_FMT "\n", rb);
	else
		printf("No solution\n");
}
