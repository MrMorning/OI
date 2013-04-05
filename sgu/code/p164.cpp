#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
int f[200][200];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	memset(f, 0x3f, sizeof(f));
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
		{
			int t;
			scanf("%d", &t);
			if(t == 0)
				f[i][j] = 0;
			else
				if(t <= (m + 1) / 2)
					f[i][j] = 1;
		}
	for(int k = 0; k < n; k ++)
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(f[i][j] > 3)
			{
				printf("%d\n", m - (m + 1) / 2);
				for(int i = (m + 1) / 2 + 1; i <= m; i ++)
					printf("%d ", i);
				return 0;
			}
	printf("%d\n", (m + 1) / 2);
	for(int i = 1; i <= (m + 1) / 2; i ++)
		printf("%d ", i);
}
