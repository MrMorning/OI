#include <cstdio>
#ifdef unix
	#define VAL_T_FMT "%lld"
#else
	#define VAL_T_FMT "%I64d"
#endif
typedef long long val_t;

const int D_MAX = 16;

val_t f[D_MAX][10][13][2], g[D_MAX][13][2];
int tmp[D_MAX], dig[D_MAX];

void pre_work()
{
	for(int i = 0; i <= 9; i ++)
		f[1][i][i][0] = 1;
	for(int i = 1; i < D_MAX - 1; i ++)
		for(int j = 0; j <= 9; j ++)
			for(int k = 0; k < 13; k ++)
				for(int l = 0; l <= 9; l ++)
				{
					f[i + 1][l][(10 * k + l) % 13][1] += f[i][j][k][1];
					if(j == 1 && l == 3)
						f[i + 1][l][(10 * k + l) % 13][1] += f[i][j][k][0];
					else
						f[i + 1][l][(10 * k + l) % 13][0] += f[i][j][k][0];
				}
	for(int i = 1; i < D_MAX; i ++)
		for(int k = 0; k < 13; k ++)
			for(int t = 0; t <= 1; t ++)
				for(int j = 0; j <= 9; j ++)
					g[i][k][t] += f[i][j][k][t];
	g[0][0][0] = 1;
}

val_t solve(val_t n)
{
	val_t x = n;
	int n_dig = 0;
	while(x)
	{
		tmp[++ n_dig] = x % 10;
		x /= 10;
	}
	for(int i = 1; i <= n_dig; i ++)
		dig[i] = tmp[n_dig - i + 1];

	val_t res = 0;
	for(int i = 0; i < n_dig - 1; i ++)
	{
		for(int j = 0; j < dig[i + 1]; j ++)
		{
			bool flag = false;
			int mod = 0;
			for(int k = 0; k <= i; k ++)
				mod = (10 * mod + dig[k]) % 13;
			mod = (10 * mod + j) % 13;
			for(int k = i + 2; k <= n_dig; k ++)
				mod = (10 * mod) % 13;

			for(int k = 1; k <= i; k ++)
				if(dig[k - 1] == 1 && dig[k] == 3)
					flag = true;
			flag |= (dig[i] == 1 && j == 3);

			res += g[n_dig - i - 1][(13 - mod) % 13][1];
			if(flag)
				res += g[n_dig - i - 1][(13 - mod) % 13][0];
			
			//one missed situation: dig[j] == 1 && dig[j + 1] == 3, not counted
			if(!flag && j == 1 && n_dig - i - 1 > 0)
			{
				int z = 3;
				for(int k = i + 3; k <= n_dig; k ++)
					z = (z * 10) % 13;
				res += g[n_dig - i - 2][(13 - (mod + z) % 13) % 13][0];
			}
		}
	}

	//get the last several numbers brutely
	for(x = n / 10 * 10; x <= n; x ++)
		if(x % 13 == 0)
		{
			val_t y = x;
			while(y)
			{
				if(y % 10 == 3 && y / 10 % 10 == 1)
				{
					res ++;
					break;
				}
				y /= 10;
			}
		}
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	pre_work();
	val_t n;
	scanf(VAL_T_FMT, &n);
	printf(VAL_T_FMT "\n", solve(n));
}
