#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int Z_MAX = 30;
const int S_MAX = 1010;
const int N_MAX = 65;

char alpha[Z_MAX];
int alphaNum, stateNum, tvNum;
int tv[S_MAX];
bool vis[S_MAX], terminated[S_MAX];
struct Edge
{
	int to, type;
} e[S_MAX][Z_MAX];
int g[S_MAX][Z_MAX];
ll f[N_MAX][S_MAX];
int sv, len;

int dfs(int u, int a)
{
	if(vis[u])
		return -1;
	vis[u] = true;
	if(e[u][a].type == 0)
		return e[u][a].to;
	return dfs(e[u][a].to, a);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s", alpha);
	alphaNum = strlen(alpha);
	scanf("%d", &stateNum);
	scanf("%d%d", &sv, &tvNum);
	sv --;
	while(tvNum --)
	{
		int u;
		scanf("%d", &u);
		u --;
		terminated[u] = true;
	}
	for(int i = 0; i < stateNum; i ++)
		for(int j = 0; j < alphaNum; j ++)
		{
			scanf("%d", &e[i][j].to);
			e[i][j].to --;
		}
	for(int i = 0; i < stateNum; i ++)
		for(int j = 0; j < alphaNum; j ++)
			scanf("%d", &e[i][j].type);
	for(int i = 0; i < stateNum; i ++)
		for(int j = 0; j < alphaNum; j ++)
		{
			memset(vis, 0, sizeof(vis));
			g[i][j] = dfs(i, j);
		}
	f[0][sv] = 1;
	scanf("%d", &len);
	for(int i = 0; i <= len - 1; i ++)
		for(int j = 0; j < stateNum; j ++)
			if(f[i][j])
				for(int k = 0; k < alphaNum; k ++)
					if(g[j][k] != -1)
						f[i + 1][g[j][k]] += f[i][j];
	ll ans = 0;
	for(int i = 0; i < stateNum; i ++)
		if(terminated[i])
			ans += f[len][i];
	cout << ans;
}
