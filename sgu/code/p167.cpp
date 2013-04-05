#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
int sum[16][16];
int n, m, s;
int f[16][226][16][16][2][2], w[16][16];
bool used[16][16];

struct State
{
	int s;
	State(){}
	State(int a, int b, int c, int d)
	{
		s = a * 16 * 16 * 16 + b * 16 * 16 + c * 16 + d;
	}
	inline int getL()
	{
		return s / (16 * 16 * 16);
	}
	inline int getR()
	{
		return s / (16 * 16) % 16;
	}
	inline int getT1()
	{
		return s / 16 % 16;
	}
	inline int getT2()
	{
		return s % 16;
	}
} g[16][226][16][16][2][2];

void update(int i1, int j1, int k1, int l1, int m1, int n1,
		int i2, int j2, int k2, int l2, int m2, int n2, int val)
{
	int tmp =  val + f[i1][j1][k1][l1][m1][n1], &x = f[i2][j2][k2][l2][m2][n2];
	if(tmp > x)
	 	x = tmp, g[i2][j2][k2][l2][m2][n2] = State(k1, l1, m1, n1);
}
int main()
{
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &w[i][j]);
			sum[i][j] = sum[i][j - 1] + w[i][j];
		}

	memset(f, -0x3f, sizeof(f));
	f[0][s][0][0][1][1] = 0;
	for(int i = 0; i <= n - 1; i ++)
		for(int k = 0; k <= s; k ++)
			for(int l = 0; l <= m; l ++)
				for(int r = l; r <= m; r ++)
					for(int t1 = 0; t1 < 2; t1 ++)
						for(int t2 = 0; t2 < 2; t2 ++)
							if(f[i][k][l][r][t1][t2] >= 0)
							{
								if(l == 0)
								{
									if(t1)
									{
										for(int a = 1; a <= m; a ++)
											for(int b = a; b <= m; b ++)
												if(k >= b - a + 1)
													update(i, k, l, r, t1, t2, i + 1, k - (b - a + 1), a, b, 1, 1, sum[i + 1][b] - sum[i + 1][a - 1]);
										update(i, k, l, r, t1, t2, i + 1, k, 0, 0, 1, 1, 0);
									}
									else
										update(i, k, l, r, t1, t2, i + 1, k, 0, 0, 0, 0, 0);
								}
								else
									for(int a = (t1 ? 1 : l); a <= r; a ++)
										for(int b = max(a, l); b <= (t2 ? m : r); b ++)
											if(k >= b - a + 1)
												update(i, k, l, r, t1, t2, i + 1, k - (b - a + 1), a, b, t1 && a <= l, t2 && b >= r, sum[i + 1][b] - sum[i + 1][a - 1]);
								update(i, k, l, r, t1, t2, i + 1, k, 0, 0, 0, 0, 0);
							}
	int ansVal = -1, ansL, ansR, ansT1, ansT2;
	for(int l = 0; l <= m; l ++)
		for(int r = l; r <= m; r ++)
			for(int t1 = 0; t1 < 2; t1 ++)
				for(int t2 = 0; t2 < 2; t2 ++)
					if(f[n][0][l][r][t1][t2] > ansVal)
					{
						ansVal = f[n][0][l][r][t1][t2];
						ansL = l, ansR = r, ansT1 = t1, ansT2 = t2;
					}
	printf("Oil : %d\n", ansVal);
	for(int i = n, ansK = 0; i >= 1; i --)
	{
		for(int j = ansL; j <= ansR; j ++)
			used[i][j] = true;
		State s = g[i][ansK][ansL][ansR][ansT1][ansT2];
		if(ansL != 0)
			ansK += ansR - ansL + 1;
		ansL = s.getL();
		ansR = s.getR();
		ansT1 = s.getT1();
		ansT2 = s.getT2();
	}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(used[i][j])
				printf("%d %d\n", i, j);
}
