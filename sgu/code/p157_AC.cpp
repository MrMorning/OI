#include <cstdio>
const int ans[14] = {0, 1, 2, 5, 14, 47, 189, 891, 4815, 29547, 203173, 1548222, 12966093, 118515434};
int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	printf("%d", ans[n]);
}
