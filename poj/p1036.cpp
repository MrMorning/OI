#include <cstdio>
#include <cstring>
#define MAXN 101

int n, m, T;
int time[MAXN], p[MAXN], s[MAXN];
int f1[MAXN], f2[MAXN], w[MAXN];

inline int max(int a, int b)
{return a > b ? a: b; }

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d\n", &n, &m, &T);
	for(int i = 1; i <= n; i ++)
		scanf("%d\n", &time[i]);
	for(int i = 1; i <= n; i ++)
		scanf("%d\n", &p[i]);
	for(int i = 1; i <= n; i ++)
		scanf("%d\n", &s[i]);
	for(int i = 1; i <= n; i ++)
	{
		if(time[i] == 0)
			w[s[i]] += p[i];
	}
	for(int j = 1; j <= m; j ++)
		f1[j] = -0x3f3f3f3f;
	f1[0] = w[0];
	for(int i = 1; i <= T; i ++)
	{
		memset(w, 0, sizeof(w));
		for(int k = 1; k <= n; k ++)
			if(time[k] == i)
				w[s[k]] += p[k];
		for(int j = 0; j <= m; j ++)
		{
			f2[j] = f1[j] + w[j];
			if(j > 0)
				f2[j] = max(f2[j], f1[j - 1] + w[j]);
			if(j < m)
				f2[j] = max(f2[j], f1[j + 1] + w[j]);
		}
		memcpy(f1, f2, sizeof(f2));
	}
	int ans = 0;
	for(int j = 0; j <= m; j ++)
		ans = max(ans, f2[j]);
	printf("%d\n", ans);
}
