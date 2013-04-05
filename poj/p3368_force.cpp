#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int n, m, a[100000], hash[200001];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
	while(m --)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l --, r --;
		memset(hash, 0, sizeof(hash));
		for(int i = l; i <= r; i ++)
			hash[a[i] + 100000] ++;
		int ret = 0;
		for(int j = - 100000; j <= 100000; j ++)
			ret = MAX(ret, hash[j + 100000]);
		printf("%d\n", ret);
	}
}
