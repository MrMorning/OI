#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 30;

pair<int, int> now[N_MAX][N_MAX], next[N_MAX][N_MAX];
int input[N_MAX][N_MAX];
int ans[N_MAX][N_MAX];
int match[N_MAX * N_MAX];
bool used[N_MAX * N_MAX];
int n;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int tot = 0;
	for(int i = 0; i < n; i ++)
	{
		static char str[100];
		scanf("%s", str);
		for(int j = 0; j < n; j ++)
		{
			input[i][j] = str[j] - '0';
			if(input[i][j] == 1)
				tot ++;
		}
	}
	if(tot & 1)
	{
		printf("NO\n");
		return 0;
	}
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			next[i][j] = make_pair(i * n + j, input[i][j]);
	for(int rotate = 0; rotate < 4; rotate ++)
	{
		memcpy(now, next, sizeof(next));
		
		for(int dx = -(n - 1); dx < n; dx ++)
			for(int dy = -(n - 1); dy < n; dy ++)
			{
				bool fail = false;
				int cnt = 0;
				memset(match, -1, sizeof(match));
				memset(used, 0, sizeof(used));
				for(int i = 0; !fail && i < n; i ++)
					for(int j = 0; !fail && j < n; j ++)
						if(now[i][j].second)
						{
							int u = now[i][j].first;
							if(match[u] != -1)
								continue;
							int ni = dx + i, nj = dy + j;
							if(0 <= ni && ni < n)
								if(0 <= nj && nj < n)
									if(input[ni][nj])
									{
										int v = ni * n + nj;
										if(v == u)
											continue;
										if(match[v] == -1)
											match[u] = v, match[v] = u, used[u] = true, cnt ++;
									}
						}
				if(!fail && (cnt == tot / 2))
				{
					printf("YES\n");
					for(int i = 0; i < n; i ++)
						for(int j = 0; j < n; j ++)
							if(now[i][j].second)
							{
								int u = now[i][j].first;
								if(used[u])
									ans[u / n][u % n] = 1;
							}
					for(int i = 0; i < n; i ++, printf("\n"))
						for(int j = 0; j < n; j ++)
							printf("%d", ans[i][j]);
					return 0;
				}
			}

		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				next[j][n - 1- i] = now[i][j];
	}

	printf("NO\n");
}
