#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool f[10001][1000];
int from[10001][1000];
int N, M, a[10000];
int ans[10000], ansCnt;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for(int i = 0; i < N; i ++)
	{
		scanf("%d", &a[i]);
		a[i] %= M;
	}
	f[0][1] = true;
	memset(from, -1, sizeof(from));
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < M; j ++)
			if(f[i][j])
			{
				int tmp = (j * a[i] % M);
				f[i + 1][j] = 1, f[i + 1][tmp] = 1;
				from[i + 1][j] = j;
				from[i + 1][tmp] = j;
			}
	for(int i = M - 1; i >= 0; i --)
		if(f[N][i])
		{
			printf("%d\n", i);
			int k = N;
			while(k)
			{
				if(from[k][i] == i)
					k --;
				else
				{
					ans[ansCnt ++] = k;
					i = from[k --][i];
				}
			}
			break;
		}
	sort(ans, ans + ansCnt);
//	int res = 1;
	for(int i = 0; i < ansCnt; i ++)
	{
		printf("%d ", ans[i]);
//		res = res * a[ans[i] - 1] % M;
	}
//	printf("\n%d\n", res);
}
