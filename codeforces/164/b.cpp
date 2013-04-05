#include <cstdio>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
int n;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	ll sum = 0;
	for ( int i = 1; i < n; i ++ )
		sum += i*(n-i);
	sum += n;
	printf(LL_FMT "\n", sum);
}
