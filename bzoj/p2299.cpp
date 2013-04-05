#include <cstdio>
#include <algorithm>
typedef long long bignum_t;
int root[2][2][2];
int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void extend_gcd(int a, int b, int &x, int &y)
{
	if(b == 0)
		x = 1, y = 0;
	else
	{
		int x0, y0;
		extend_gcd(b, a % b, x0, y0);
		x = y0, y = x0 - (a / b) * y0;
	}
}

bignum_t func(int i, int j, int x)
{
	return (bignum_t)root[i][j][1] * x + root[i][j][0];
}

bool judge(int a, int b, int x0, int y0)
{
	if(a == 0 && b == 0)
		return x0 == 0 && y0 == 0;
	int g = gcd(a, b);
	if(a == 0 || b == 0)
		return x0 % g == 0 && y0 % g == 0;
	int ans[2];
	ans[0] = x0, ans[1] = y0;
	for(int t = 0; t <= 1; t ++)
	{
		if(ans[t] % g)
			return false;
		if(t)
			std::swap(a, b);
		extend_gcd(a, b, root[t][0][0], root[t][1][0]);
		root[t][0][1] = - b / g, root[t][1][1] = a / g;
		for(int i = 0; i <= 1; i ++)
			root[t][i][0] *= ans[t] / g;
	}
	for(int t1 = 0; t1 <= 1; t1 ++)
		for(int t2 = 0; t2 <= 1; t2 ++)
			if((func(0, 0, t1) + func(1, 0, t2)) % 2 == 0)
				if((func(0, 1, t1) + func(1, 1, t2)) % 2 == 0)
					return true;
	return false;
}

void test()
{
	int x, y;
	extend_gcd(6, 8, x, y);
	printf("%d %d\n", x, y);
}

int main()
{
	freopen("t.in", "r", stdin);
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
	{
		int a, b, x, y;
		scanf("%d%d%d%d", &a, &b, &x, &y);
		if(judge(a, b, x, y))
			printf("Y\n");
		else
			printf("N\n");
	}
}
