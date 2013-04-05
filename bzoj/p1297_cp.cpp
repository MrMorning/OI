#include <cstdio>
#include <cstring>

const int N_MAX = 100;
const int MATRIX_SIZE = N_MAX * N_MAX * 4;
const int MOD_NUM = 2009;

int n;
int idMtx[N_MAX][N_MAX], ansMtx[N_MAX][N_MAX], baseMtx[N_MAX][N_MAX];

void mul(int f[N_MAX][N_MAX], const int _a[N_MAX][N_MAX], const int _b[N_MAX][N_MAX])
{
	static int a[N_MAX][N_MAX], b[N_MAX][N_MAX];
	memcpy(a, _a, MATRIX_SIZE);
	memcpy(b, _b, MATRIX_SIZE);
	for(int i = 0; i < 10 * n; i ++)
		for(int j = 0; j < 10 * n; j ++)
		{
			f[i][j] = 0;
			for(int k = 0; k < 10 * n; k ++)
				f[i][j] = (f[i][j] + a[i][k] * b[k][j]) % MOD_NUM;
		}
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int t;
	scanf("%d%d", &n, &t);
	for(int i = 0; i < 10 * n; i ++)
		idMtx[i][i] = 1;
	for(int i = 0; i < n; i ++)
	{
		for(int j = 2; j < 10; j ++)
			baseMtx[10 * i + j][10 * i + j - 1] = 1;
		static char str[15];
		scanf("%s", str);
		for(int j = 0; j < n; j ++)
			if(str[j] - '0')
				baseMtx[10 * i + 1][10 * j + str[j] - '0'] = 1;
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
	printf("%d\n", ansMtx[1][10 * (n - 1) + 1]);
}
