#include <cstdio>
typedef long long bignum_t;
#define BIGNUM_T_FMT "%lld"
bignum_t res[2];
int n, m;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int t = 0; t < 2; t ++)
		for(int i = 0; i < n; i ++)
			for(int j = 0, v; j < m; j ++)
			{
				scanf("%d", &v);
				res[t] += (i * i + j * j) * v;
			}
	printf(BIGNUM_T_FMT "\n", -1 * (res[1] - res[0]) / 2);
}
