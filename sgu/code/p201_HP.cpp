#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int Z_MAX = 30;
const int S_MAX = 1010;
const int N_MAX = 65;
const int D_MAX = 200;
 
struct BigInt
{
        int num[D_MAX];
        int len;
        void operator+= (const BigInt &x)
        {
                len = max(len, x.len);
                for(int i = 0; i < len; i ++)
                        num[i] += x.num[i];
                for(int i = 0; i < len; i ++)
                        num[i + 1] += num[i] / 10, num[i] %= 10;
                if(num[len])
                        len ++;
        }
        void operator-= (const BigInt &x) //assume *this > x
        {
                for(int i = 0; i < len; i ++)
                {
                        num[i] -= x.num[i];
                        if(num[i] < 0)
                                num[i] += 10, num[i + 1] --;
                }
                for(int i = len - 1; i >= 0; i --)
                        if(num[i])
                        {
                                len = i + 1;
                                break;
                        }
        }
        void operator*= (const BigInt &x)
        {
                static int tmp[D_MAX];
                memset(tmp, 0, sizeof(tmp));
                for(int i = 0; i < len; i ++)
                        for(int j = 0; j < x.len; j ++)
                                tmp[i + j] += num[i] * x.num[j];
                int upperlim = len + x.len;
                for(int i = 0; i < upperlim; i ++)
                        tmp[i + 1] += tmp[i] / 10, tmp[i] %= 10;
                len = 0;
                for(int i = 0; i < upperlim; i ++)
                        if(tmp[i])
                                len = i + 1;
                memcpy(num, tmp, sizeof(int) * len);
        }
        void output()
        {
                for(int i = len - 1; i >= 0; i --)
                        printf("%d", num[i]);
        }
};


char alpha[Z_MAX];
int alphaNum, stateNum, tvNum;
int tv[S_MAX];
bool vis[S_MAX], terminated[S_MAX];
struct Edge
{
	int to, type;
} e[S_MAX][Z_MAX];
int g[S_MAX][Z_MAX];
BigInt f[N_MAX][S_MAX], ans;
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
	f[0][sv].len = f[0][sv].num[0] = 1;
	scanf("%d", &len);
	for(int i = 0; i <= len - 1; i ++)
		for(int j = 0; j < stateNum; j ++)
			if(f[i][j].len)
				for(int k = 0; k < alphaNum; k ++)
					if(g[j][k] != -1)
						f[i + 1][g[j][k]] += f[i][j];
	ans.len = 1;
	for(int i = 0; i < stateNum; i ++)
		if(terminated[i])
			ans += f[len][i];
	ans.output();
}
