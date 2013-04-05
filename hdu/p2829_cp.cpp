#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
typedef long long Val_t;
#define VAL_T_FMT "%lld"
const int MAXN = 1010;
Val_t f[MAXN][MAXN], sum[MAXN], preCnt[MAXN];

void solve(int n, int m)
{
	for(int i = 1, t; i <= n; i ++)
	{
		scanf("%d", &t);
		sum[i] = sum[i - 1] + t;
		preCnt[i] = preCnt[i - 1] + t * sum[i - 1];
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int j = 1; j <= m; j ++)
		for(int i = 1; i <= n; i ++)
			for(int k = 0; k < i; k ++)
				f[i][j] = MIN(f[i][j], f[k][j - 1] + preCnt[i] - preCnt[k] - (sum[i] - sum[k]) * sum[k]);
	printf(VAL_T_FMT "\n", f[n][m]);
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if(n == 0)
			break;
		solve(n, m + 1);
	}
}
