#include <cstdio>
#include <cstring>

int color[100001];
int main()
{
	freopen("t.in", "r", stdin);
	int n, colornum, m;
	scanf("%d %d %d\n", &n, &colornum, &m);
	for(int i = 1; i <= n; i ++) color[i] = 1;
	for(int i = 1, a, b, c; i <= m; i ++)
	{
		char ctrl;
		scanf("\n%c %d %d", &ctrl, &a, &b);
		if(ctrl == 'C')
		{
			scanf("%d",&c);
			for(int j = a; j <= b; j ++) color[j] = c;
		}
		else
		{
			bool exist[31];
			int cnt = 0;
			memset(exist, 0 ,sizeof(exist));
			for(int j = a; j <= b; j ++)
				if(!exist[color[j]])
				{
					cnt ++;
					exist[color[j]] = true;
				}
			printf("%d\n", cnt);
		}
	}
}
