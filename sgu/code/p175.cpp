#include <cstdio>

int f(int n, int q)
{
	if(n == 1)
		return 1;
	else 
	{
		int k = n / 2;
		if(q <= k)
			return n - k + f(k, k - q + 1);
		else
			return f(n - k, n - q + 1);
	}
}

int main()
{
	//freopen("t.in", "r", stdin);
	int n, q;
	scanf("%d%d", &n, &q);
	printf("%d\n", f(n, q));
}
