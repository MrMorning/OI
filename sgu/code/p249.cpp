#include <cstdio>

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int x = 0; x < 1 << n; x ++)
	{
		int u = x ^ (x >> 1);
		for(int y = 0; y < 1 << m; y ++)
		{
			int t = (y ^ (y >> 1)) << n;
			printf("%d ", u | t);
		}
		printf("\n");
	}
}
