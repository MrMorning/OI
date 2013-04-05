#include <cstdio>

int doit(int a, int b)
{
	if(a == 0 || b == 0)
		return 0;
	if(a > b)
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
	if((a & 1) ^ (b & 1))
		return -1;
	if((a & 1) && (b & 1))
	{
		int res = doit(a << 1, b - a);
		if(res == -1)
			return -1;
		return res + 1;
	}
	else
		return doit(a >> 1, b >> 1);
}
int main()
{
	freopen("t.in", "r", stdin);
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d\n", doit(a, b));
}
