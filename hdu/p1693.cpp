#include <cstdio>
#include <cstring>
typedef long long ll;
#define LL_FMT "%lld"
const int N_MAX = 12, N_STATE_MAX = 1 << 12;
ll f[N_MAX][N_MAX][N_STATE_MAX];
int ok[N_MAX][N_MAX];
int main()
{
	freopen("t.in", "r", stdin);
	int n_test, n_row, n_col;
	scanf("%d", &n_test);
	for(int ctest = 0; ctest < n_test; ctest ++)
	{
		memset(f, 0, sizeof(f));
		scanf("%d%d", &n_row, &n_col);
		int upper_lim = 1 << (n_col + 1);
		memset(ok, 0, sizeof(ok));
		for(int i = 0; i < n_row; i ++)
			for(int j = 0; j < n_col; j ++)
				scanf("%d", &ok[i][j]);
		f[0][0][0] = 1;
		for(int i = 0; i < n_row; i ++)
			for(int j = 0; j < n_col; j ++)
				for(int k = 0; k < upper_lim; k ++)
					if(f[i][j][k])
					{
						int s_l = (1 << (n_col - j)) & k;
						int s_u = (1 << (n_col - j - 1)) & k;
						if(j == n_col - 1)
						{
							if(! ok[i][j])
							{
								if(! (s_l || s_u))
									f[i + 1][0][k >> 1] += f[i][j][k];
								continue;
							}
							if(s_l && s_u)
								f[i + 1][0][(k >> 1) & (~ 1)] += f[i][j][k];
							else if((s_l || s_u) && ok[i + 1][j])
								f[i + 1][0][(k >> 1) | 1] += f[i][j][k];
						}
						else
						{
							int pos_u = 1 << (n_col - j - 1), pos_l = 1 << (n_col - j);
							if(! ok[i][j])
							{
								if(! (s_l || s_u))
									f[i][j + 1][k] += f[i][j][k];
								continue;
							}
							if(s_l && s_u)
								f[i][j + 1][k & (~ pos_u) & (~ pos_l)] += f[i][j][k];
							else if(s_l || s_u)
							{
								if(ok[i + 1][j])
									f[i][j + 1][(k & (~ pos_u)) | pos_l] += f[i][j][k];
								if(ok[i][j + 1])
									f[i][j + 1][(k & (~ pos_l)) | pos_u] += f[i][j][k];
							}
							else 
								if(ok[i + 1][j] && ok[i][j + 1])
									f[i][j + 1][k | pos_u | pos_l] += f[i][j][k];
						}
					}
		printf("Case %d: There are " LL_FMT " ways to eat the trees.\n", ctest + 1, f[n_row][0][0]);
	}
}
