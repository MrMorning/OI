#include <cstdio>
typedef long long bignum_t;
const int MOD_NUM = 1000000007;
int s[6];
int f[16][16][16][16][16][6];
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int m, n = 0;
	scanf("%d", &m);
	for(int i = 1, c; i <= m; i ++)
	{
		scanf("%d", &c);
		s[c] ++;
	}
	n = m;
	f[s[5]][s[4]][s[3]][s[2]][s[1]][0] = 1;
	for(int a = s[5]; a >= 0; a --)
		for(int b = m; b >= 0; b --)
			for(int c = m; c >= 0; c --)
				for(int d = m; d >= 0; d --)
					for(int e = m; e >= 0; e --)
						for(int l = 0; l <= 5; l ++)
							if(int tmp = f[a][b][c][d][e][l])
							{
#define update(x,y) (x = (bignum_t)(x + y) % MOD_NUM)
								if(e)
									update(f[a][b][c][d][e - 1][0], (bignum_t)(e - (l == 1)) * tmp % MOD_NUM);
								if(d)
									update(f[a][b][c][d - 1][e + 1][1], (bignum_t)(d - (l == 2)) * tmp % MOD_NUM);
								if(c)
									update(f[a][b][c - 1][d + 1][e][2], (bignum_t)(c - (l == 3)) * tmp % MOD_NUM);
								if(b)
									update(f[a][b - 1][c + 1][d][e][3], (bignum_t)(b - (l == 4)) * tmp % MOD_NUM);
								if(a)
									update(f[a - 1][b + 1][c][d][e][4], (bignum_t)(a - (l == 5)) * tmp % MOD_NUM);
							}
	printf("%d\n", f[0][0][0][0][0][0]);
}
