#include <cstdio>
#include <cstring>
int n, k, m, a[1000], b[1000];
int main()
{
	freopen("t.in", "r", stdin);
	int n, k;
	scanf("%d%d", &n, &k);
	int m = k / n; k %= n;
	for(int d = 1; d < n; d ++)
	{
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		a[n - 1] = b[0] = 1;
		for(int i = d, pre = 0; i != 0; pre = i, i = (i + d) % n)
			a[i] = b[pre], b[i] = (i == n - 1 ? 0 : a[i]);
		int cnt = 0;
		for(int i = 0; i < n; i ++)
			cnt += a[i];
		if(cnt == k)
			break;
	}
	for(int i = 0; i < n; i ++)
		printf("%d ", a[i] + m);
}
