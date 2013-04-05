#include <cstdio>
#include <cstring>

int n, c[4], V, f[1000001];
inline int min(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &c[i]);
	scanf("%d", &V);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = c[i]; j <= V; j ++)
			f[j] = min(f[j], f[j - c[i]] + 1);
	if(f[V] == 0x3f3f3f3f)
		printf("-1\n");
	else
		printf("%d\n", f[V]);
}
