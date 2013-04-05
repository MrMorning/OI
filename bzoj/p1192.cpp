#include <cstdio>
int n, d = 0;
int main()
{
	scanf("%d", &n);
	while((1 << d) <= n)
		d ++;
	printf("%d\n", d);
}
