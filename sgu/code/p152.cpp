#include <cstdio>
int a[10000], b[10000], sum, sum2, n;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
	{
		scanf("%d", &a[i]);
		sum += a[i];
	}

	for(int i = 0; i < n; i ++)
		b[i] = a[i] * 100 / sum;

	for(int i = 0; i < n; i ++)
		sum2 += b[i];
	int t = 100 - sum2;
	for(int i = 0, j = 0; i < n && j < t; i ++)
		if(a[i] % sum)
			b[i] ++, j ++;
	for(int i = 0; i < n; i ++)
		printf("%d ", b[i]);
}
