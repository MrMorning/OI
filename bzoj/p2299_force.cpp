#include <cstdio>
const int TRY_MAX = 5;
int t[4], vec[4][2], a, b, x, y;
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int _;
	scanf("%d", &_);
	while(_ --)
	{
		scanf("%d%d%d%d", &a, &b, &x, &y);
		vec[0][0] = a, vec[0][1] = b;
		vec[1][0] = a, vec[1][1] = -b;
		vec[2][0] = b, vec[2][1] = a;
		vec[3][0] = b, vec[3][1] = -a;

		for(t[0] = -TRY_MAX; t[0] <= TRY_MAX; t[0] ++)
			for(t[1] = -TRY_MAX; t[1] <= TRY_MAX; t[1] ++)
				for(t[2] = -TRY_MAX; t[2] <= TRY_MAX; t[2] ++)
					for(t[3] = -TRY_MAX; t[3] <= TRY_MAX; t[3] ++)
					{
						int res[2];
						res[0] = res[1] = 0;
						for(int i = 0; i < 4; i ++)
							for(int j = 0; j <= 1; j ++)
								res[j] += t[i] * vec[i][j];
						if(res[0] == x && res[1] == y)
						{
							for(int i = 0; i < 4; i ++)
								printf("%d ", t[i]);
							printf("\n");
							return 0;
						}
					}

	}
}
