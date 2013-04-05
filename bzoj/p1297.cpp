#include <cstdio>
#include <cstring>

const int N_MAX = 90;
const int MATRIX_SIZE = N_MAX * N_MAX * 4;
const int MOD_NUM = 2009;

int n;
int idMtx[N_MAX][N_MAX], ansMtx[N_MAX][N_MAX], baseMtx[N_MAX][N_MAX];

void mul(int f[N_MAX][N_MAX], const int _a[N_MAX][N_MAX], const int _b[N_MAX][N_MAX])
{
	static int a[N_MAX][N_MAX], b[N_MAX][N_MAX];
	memcpy(a, _a, MATRIX_SIZE);
	memcpy(b, _b, MATRIX_SIZE);
	for(int i = 0; i < 9 * n; i ++)
		for(int j = 0; j < 9 * n; j ++)
		{
			f[i][j] = 0;
			for(int k = 0; k < 9 * n; k ++)
				f[i][j] = (f[i][j] + a[i][k] * b[k][j]) % MOD_NUM;
		}
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int t;
	scanf("%d%d", &n, &t);
	for(int i = 0; i < 9 * n; i ++)
		idMtx[i][i] = 1;
	for(int i = 0; i < n; i ++)
	{
		for(int j = 1; j < 9; j ++)
			baseMtx[9 * i + j][9 * i + j - 1] = 1;
		static char str[15];
		scanf("%s", str);
		for(int j = 0; j < n; j ++)
			if(str[j] - '0')
				baseMtx[9 * i][9 * j + str[j] - '1'] = 1;
	}
	if(t & 1)
		memcpy(ansMtx, baseMtx, MATRIX_SIZE);
	else
		memcpy(ansMtx, idMtx, MATRIX_SIZE);
	t >>= 1;
	while(t)
	{
		mul(baseMtx, baseMtx, baseMtx);
		if(t & 1)
			mul(ansMtx, ansMtx, baseMtx);
		t >>= 1;
	}
	printf("%d\n", ansMtx[0][9 * (n - 1)]);
}
