#include <cstdio>
int n, f[41];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	f[1] = f[2] = 1;
	for(int i = 3; i <= n; i ++)
		f[i] = f[i - 1] + f[i - 2];
	int sum = 0;
	for(int i = 1; i <= n; i ++)
		sum += f[i];
	printf("%d\n", sum);
}
