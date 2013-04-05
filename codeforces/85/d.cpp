#include <cstdio>
#include <cstring>
#include <cmath>
int n, f[100001];
int main()
{
	scanf("%d", &n);
	memset(f, -1, sizeof(f));
	for(int i = 1, x, y; i <= n; i ++)
	{
		scanf("%d%d", &x, &y);
		int cnt = 0;
		for(int j = 1, lim = (int)sqrt(x); j <= lim; j ++)
			if(x % j == 0)
			{
				int p = j, q = x / j;
				if(f[p] < i - y)
					cnt ++;
				if(p != q)
					if(f[q] < i - y)
						cnt ++;
				f[p] = f[q] = i;
			}
		printf("%d\n", cnt);
	}
}
