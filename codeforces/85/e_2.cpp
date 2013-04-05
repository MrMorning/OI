#include <cstdio>
int ans[41][41];
int main()
{
	freopen("t1.in", "r", stdin);
	//freopen("e_3.cpp", "w", stdout);
	for(int i = 1; i <= 40; i ++)
		for(int j = i; i * j <= 40; j ++)
		{
			int x, y;
			scanf("%d%d%d", &x, &y, &ans[i][j]);
			ans[j][i] = ans[i][j];
		}
	for(int i = 0; i <= 40; i ++)
	{
		printf("{");
		for(int j = 0; j < 40; j ++)
			printf("%d, ", ans[i][j]);
		printf("%d},", ans[i][40]);
	}
}
