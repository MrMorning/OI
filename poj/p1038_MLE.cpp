#include <cstdio>
#include <cstring>
#define MAXN 160
#define INF 0x3f3f3f3f

bool bad[MAXN][11];
int fac[11], n, m, f[MAXN][59049];
int p[11], q[11];
int badNum;

inline int max(int a, int b)
{return a > b ? a : b;}

void Update(int &a, int b)
{a = max(a, b);}

void dfs(int i, int j, int k, int cnt)
{
	Update(f[i+1][k], cnt);
	if(j > m) return;
	dfs(i, j+1, k, cnt);//do nothing
	//if(bad[i][j])
	//	return;
	//	always trying put something whose top-right corner is (i,j)
	if(i > 2 && j + 1 <= m)
	{
		if(p[j] + p[j+1] == 0)
			if((bad[i][j] | bad[i-1][j] | bad[i-2][j]) == 0)
				if((bad[i][j+1] | bad[i-1][j+1] | bad[i-2][j+1]) == 0)
					dfs(i, j+2, k+fac[j]*2+fac[j-1]*2, cnt+1);
	}
	if(i > 1 && j + 2 <= m)
		if(max(p[j+2],max(p[j+1],p[j])) <= 1)
			if((bad[i][j] | bad[i][j+1] | bad[i][j+2]) == 0)
				if((bad[i-1][j] | bad[i-1][j+1] | bad[i-1][j+2]) == 0)
					dfs(i, j+3, k+fac[j+1]*2+fac[j]*2+fac[j-1]*2, cnt+1);

}

void solve()
{
	scanf("%d %d %d\n", &n, &m, &badNum);
	memset(bad, 0, sizeof(bad));
	while(badNum --)
	{
		int a, b;
		scanf("%d %d\n", &a, &b);
		bad[a][b] = true;
	}
	fac[0] = 1;
	for(int i = 1; i <= m; i ++)
		fac[i] = fac[i - 1] * 3;
	memset(f, -0x3f, sizeof(f));
	//for(int j = 0; j < fac[m] - 1; j ++)
	//	f[1][j] = -INF;
	f[1][fac[m] - 1] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= fac[m] - 1; j ++)
		{
			int tmp = j, k = 0;
			int t = m;
			while(j < fac[t] && t > 0)
				t --;
			t ++;
			memset(p, 0, sizeof(p));
			memset(q, 0, sizeof(q));
			for(int l = 1; l <= t; l ++)
			{
				p[l] = tmp % 3;
				q[l] = max(0, p[l] - 1);
				tmp /= 3;
			}
			for(int l = t; l >= 1; l --)
				k = k * 3 + q[l];
			dfs(i, 1, k, f[i][j]);
		}
	int ans = 0;
	for(int i = n; i <= n;  i ++)
		for(int j = 0; j <= fac[m] - 1; j ++)
			if(f[i][j] == 7)
				printf("f[%d][%d] = %d\n", i, j, f[i][j]);
	for(int j = 0; j <= fac[m] - 1; j ++)
		ans = max(ans, f[n+1][j]);
	printf("%d\n", ans);
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
		solve();
}
