#include <cstdio>
int n;
int main()
{
	freopen("t.in", "r", stdin);
	while(~scanf("%d", &n))
	{
		int sg = 0;
		for(int i = 0, t; i < n; i ++)
		{
			scanf("%d", &t);
			sg ^= t;
		}
		if(sg)
			printf("Yes\n");
		else
			printf("No\n");
	}
}
