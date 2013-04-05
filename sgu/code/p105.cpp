#include <cstdio>
int n, ans;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int a = n / 3, b = n % 3;
	if(b == 0)
		ans = a * 2;
	else if(b == 1)
		ans = a * 2;
	else if(b == 2)
		ans = a * 2 + 1;
	printf("%d\n", ans);
}
