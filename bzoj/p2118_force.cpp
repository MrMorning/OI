#include <cstdio>
int weight[12];
bool f[400000];
int main()
{
//	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	int n, BMax, BMin;
	scanf("%d%d%d", &n, &BMin, &BMax);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &weight[i]);
	f[0] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = weight[i]; j <= BMax; j ++)
			f[j] |= f[j - weight[i]];
	int ans = 0;
	for(int i = BMin; i <= BMax; i ++)
		ans += f[i];
	printf("%d\n", ans);
}
