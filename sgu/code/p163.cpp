#include <cstdio>
int n, k;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &k);
	int sum = 0;
	for(int i = 0, t; i < n; i ++)
	{
		scanf("%d", &t);
		int cnt = 1;
		for(int j = 0; j < k; j ++)
			cnt = cnt * t;
		if(cnt > 0)
			sum += cnt;
	}
	printf("%d\n", sum);
}
