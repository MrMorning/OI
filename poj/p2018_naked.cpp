#include <cstdio>
#include <cstdlib>
#define MAX(a,b) ((a)>(b)?(a):(b))
int n, k, a[100001];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	double ans = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i; j ++)
			if(i - j + 1 >= k)
			{
				int cnt = 0;
				for(int l = j; l <= i; l ++)
					cnt += a[l];
				ans = MAX(ans, (double)cnt / (i - j + 1));
			}
	printf("%.0lf", ans * 1000);
}
