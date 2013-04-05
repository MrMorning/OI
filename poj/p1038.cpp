#include <cstdio>
#include <cstring>
#define MAXN 160
#define INF 0x3f3f3f3f

bool bad[MAXN][11];
int fac[11], n, m, f[2][59049];
int p[59049][11], q[59049][11];
int r[59049];
int badNum, now;

inline int max(int a, int b)
{return a > b ? a : b;}

void Update(int &a, int b)
{a = max(a, b);}

void dfs(int i, int j, int k, int cnt)
{
	Update(f[(i-1)%2][k], cnt);
	if(j > m) return;
	dfs(i, j+1, k, cnt);//do nothing
	//if(bad[i][j])
	//	return;
	//	always trying put something whose top-right corner is (i,j)
	if(i > 2 && j + 1 <= m)
	{
		if(p[now][j] + p[now][j+1] == 0)
			if((bad[i][j] | bad[i-1][j] | bad[i-2][j]) == 0)
				if((bad[i][j+1] | bad[i-1][j+1] | bad[i-2][j+1]) == 0)
					dfs(i, j+2, k+fac[j]*2+fac[j-1]*2, cnt+1);
	}
	if(i > 1 && j + 2 <= m)
		if(max(p[now][j+2],max(p[now][j+1],p[now][j])) <= 1)
			if((bad[i][j] | bad[i][j+1] | bad[i][j+2]) == 0)
				if((bad[i-1][j] | bad[i-1][j+1] | bad[i-1][j+2]) == 0)
					dfs(i, j+3, k+fac[j+1]*2+fac[j]*2+fac[j-1]*2, cnt+1);

}

void init()
{
	fac[0] = 1;
	for(int i = 1; i <= 10; i ++)
		fac[i] = fac[i - 1] * 3;
	memset(p, 0, sizeof(p));
	memset(q, 0, sizeof(q));
	for(int j = 0; j <= fac[10] - 1; j ++)
	{
		int tmp = j;
		int t = 10;
		while(j < fac[t] && t > 0)
			t --;
		t ++;
		for(int l

= 1; l <= t; l ++)
		{
			p[j][l] = tmp % 3;
			q[j][l] = max(0, p[j][l] - 1);
			tmp /= 3;
		}
		for(int l = t; l >= 1; l --)
			r[j] = r[j] * 3 + q[j][l];
	}
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
	memset(f, 0xff, sizeof(f));
	f[1][fac[m] - 1] = 0;
	for(int i = 1; i <= n; i ++)
		for(now = 0; now <= fac[m] - 1; now ++)
			if(f[i%2][now] != -1)//!pay attention to this one!!
				dfs(i, 1, r[now], f[i%2][now]);
	int ans = 0;
	for(int j = 0; j <= fac[m] - 1; j ++)
		ans = max(ans, f[(n-1)%2][j]);
	printf("%d\n", ans);
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d\n", &testNum);
	init();
	while(testNum --)
		solve();
}
