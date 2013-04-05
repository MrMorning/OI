#include <cstdio>

typedef long long bignum_t;
#ifdef unix
	#define BIGNUM_T_FMT "%lld"
#else
	#define BIGNUM_T_FMT "%I64d"
#endif

const int LIM_MAX = 100010;

int cost[4], d[4], p[4];
int cur_lim;
bignum_t f[LIM_MAX];
bignum_t ans;

void dfs(int i, int flag)
{
	int cnt = 0;
	for(int j = 0; j < i; j ++)
		cnt += cost[p[j]] * (d[p[j]] + 1);
	if(cnt <= cur_lim)
		ans += flag * f[cur_lim - cnt];
	for(int j = i == 0 ? 0 : p[i - 1] + 1; j < 4; j ++)
	{
		p[i] = j;
		dfs(i + 1, flag * -1);
		p[i] = 0;
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	for(int i = 0; i < 4; i ++)
		scanf("%d", &cost[i]);
	f[0] = 1;
	for(int i = 0; i < 4; i ++)
		for(int j = cost[i]; j <= LIM_MAX; j ++)
			f[j] += f[j - cost[i]];
	int T;
	scanf("%d", &T);
	while(T --)
	{
		for(int i = 0; i < 4; i ++)
			scanf("%d", &d[i]);
		scanf("%d", &cur_lim);
		ans = 0;
		dfs(0, 1);
		printf(BIGNUM_T_FMT "\n", ans);
	}
}
