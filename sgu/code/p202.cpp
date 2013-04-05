#include <cstdio>
#include <cstring>
typedef long long ll;
#ifdef unix	
#define LL_FMT_T "%lld"
#else
#define LL_FMT_T "%I64d"
#endif
ll f[70][70];
int g[70][70];
int peg[70][70], top[70];
int pegNum;

inline void move(int st, int en)
{
	int u = peg[st][-- top[st]];
	printf("move %d from %d to %d", u, st, en);
	if(top[en] == 0)
		printf("\n");
	else
		printf(" atop %d\n", peg[en][top[en] - 1]);
	peg[en][top[en] ++] = u; 
}

void output(int st, int en, int n, int m)
{
	if(n == 1)
	{
		move(st, en);
		return;
	}
	int k;
	for(k = 1; k <= pegNum; k ++)
		if(k != st && k != en)
			if(top[k] == 0 || 
					peg[k][top[k] - 1] > peg[st][top[st] - g[n][m]])
				break;
	output(st, k, g[n][m], m);
	output(st, en, n - g[n][m], m - 1);
	output(k, en, g[n][m], m);
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	pegNum = m;
	memset(f, 0x3f, sizeof(f));
	f[1][1] = 0;
	for(int i = 2; i <= m; i ++)
		f[1][i] = 1;
	for(int i = 2; i <= n; i ++)
		for(int j = 3; j <= m; j ++)
		{
			for(int k = 1; k < i; k ++)
				if(2 * f[k][j] + f[i - k][j - 1] < f[i][j])
				{
					f[i][j] = 2 * f[k][j] + f[i - k][j - 1];
					g[i][j] = k;
				}
		}
	for(int i = n; i >= 1; i --)
		peg[1][top[1] ++] = i;
	printf(LL_FMT_T "\n", f[n][m]);
	output(1, m, n, m);
}
