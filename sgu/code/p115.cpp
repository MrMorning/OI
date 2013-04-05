#include <cstdio>
const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int ans[12][31];
int main()
{
	freopen("t.in", "r", stdin);
	int week = 6, n, m;
	for(int i = 0; i < 12; i ++)
		for(int j = 0; j < days[i]; j ++)
		{
			week = (week + 1) % 7;
			ans[i][j] = week;
		}
	scanf("%d%d", &n, &m);
	if(m > 12 || n > days[m - 1])
		printf("Impossible\n");
	else
		printf("%d\n", ans[m - 1][n - 1] + 1);
}
