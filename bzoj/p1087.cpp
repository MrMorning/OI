#include <cstdio>
#define PLACE_KING(s, p) (s | ((7 << p) >> 1))
typedef long long bignum_t;
const int N_MAX = 10;
bignum_t f[N_MAX][1 << N_MAX][N_MAX * N_MAX];
int log2[1 << N_MAX];
int n, m;
void dfs(int i, int j, int k, int w, int obs, int begin)
{
	f[i + 1][j][k] += w;
	for(int pos = begin; pos < n; pos ++)
	{
		if(! (obs & (1 << pos)))
			dfs(i, j | (1 << pos), k + 1, w, PLACE_KING(obs, pos), pos + 1);
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	for(int i = 0; i < N_MAX; i ++)
		log2[1 << i] = i;
	scanf("%d%d", &n, &m);
	f[0][0][0] = 1;
	int upperlim = 1 << n;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < upperlim; j ++)
			for(int k = 0; k <= m; k ++)
				if(f[i][j][k])
				{
					int obs = 0;
					int tmp = j;
					while(tmp)
					{
						int one = tmp & ((~ tmp) + 1);
						int pos = log2[one];
						obs = PLACE_KING(obs, pos);
						tmp -= one;
					}
					dfs(i, 0, k, f[i][j][k], obs, 0);
				}
	bignum_t ans = 0;
	for(int j = 0; j < upperlim; j ++)
		ans += f[n][j][m];
	printf("%I64d\n", ans);
}
