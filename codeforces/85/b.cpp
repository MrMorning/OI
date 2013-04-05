#include <cstdio>
int n, x, y;
int main()
{
	scanf("%d%d%d", &n, &x, &y);
	if(n / 2 <= x && x <= n / 2 + 1 && n / 2 <= y && y <= n / 2 + 1)
		printf("NO\n");
	else
		printf("YES\n");
}
