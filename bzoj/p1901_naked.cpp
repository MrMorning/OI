#include <cstdio>
#include <algorithm>
#define MAXN 10010
int n, m, a[MAXN], b[MAXN];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	while(m --)
	{
		char ctrl[2];
		scanf("%s", ctrl);
		if(ctrl[0] == 'C')
		{
			int i, t;
			scanf("%d%d", &i, &t);
			a[i] = t;
		}
		else 
		{
			int i, j, k;
			scanf("%d%d%d", &i, &j, &k);
			for(int t = i; t <= j; t ++)
				b[t - i + 1] = a[t];
			std::sort(b + 1, b + j - i + 2);
			printf("%d\n", b[k]);
		}
	}
}
