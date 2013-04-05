#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

const int V_MAX = 100;

bool linked[V_MAX][V_MAX];
bool color[V_MAX][V_MAX];
bool vis[V_MAX];
int dgr[V_MAX], pre[V_MAX];
int seq[V_MAX], seqCnt;
int nv;
vector<int> son[V_MAX];

void dfs(int u)
{
	seq[seqCnt ++] = u;
	vis[u] = true;
	for(int v = 0; v < nv; v ++)
		if(linked[u][v])
		{
			if(!vis[v])
			{
				son[u].push_back(v);
				pre[v] = u;
				dfs(v);
			}
		}
}

void paint(int u, bool c)
{
	assert(pre[u] != -1);
	color[pre[u]][u] = color[u][pre[u]] = c;
	for(int i = 0; i < nv; i ++)
		if(linked[u][i] && i != pre[u])
			color[u][i] = color[i][u] = !c;
	for(int i = 0; i < (int)son[u].size(); i ++)
		paint(son[u][i], !c);
} 

bool backtrace(int u)
{
	if(u == -1)
		return false;
	if(dgr[u] > 2)
		return true;
	if(backtrace(pre[u]))
	{
		color[pre[u]][u] ^= 1, color[u][pre[u]] ^= 1;
		return true;
	}
	else
		return false;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	for(int i = 0, u; i < nv; i ++)
	{
		scanf("%d", &u);
		while(u)
		{
			u --;
			linked[i][u] = true;
			dgr[u] ++;
			scanf("%d", &u);
		}
	}
	memset(pre, -1, sizeof(pre));
	for(int i = 0; i < nv; i ++)
		if(!vis[i])
		{
			seqCnt = 0;
			dfs(i);
			if(son[i].size() == 0)
				continue;
			if(son[i].size() > 1)
			{
				paint(son[i][0], 0);
				for(int j = 1; j < (int)son[i].size(); j ++)
					paint(son[i][j], 1);
			}
			else
			{
				paint(son[i][0], 0);
				if(dgr[i] <= 1)
					continue;
				bool suc = false;
				for(int j = 0; j < nv; j ++)
					if(linked[i][j] && pre[j] != i && color[i][j] == 1)
					{
						suc = true;
						break;
					}
				if(!suc)
				{
					for(int j = 0; j < seqCnt; j ++)
					{
						int u = seq[j];
						if(son[u].size() != 0 && pre[u] != i && linked[i][u])
						{
							color[i][u] = color[u][i] = 1;
							suc = true;
							break;
						}
					}
					if(!suc)
					{
						for(int j = 0; j < seqCnt; j ++)
						{
							int u = seq[j];
							if(son[u].size() == 0 && pre[u] != i && linked[i][u])
							{
								if(backtrace(u))
								{
									color[i][u] = color[u][i] = 1;
									suc = true;
									break;
								}
							}
						}
					}
				}
				if(!suc)
				{
					printf("No solution\n");
					return 0;
				}
			}
		}
//	printf("1");
	
	for(int i = 0; i < nv; i ++)
	{
		for(int j = 0; j < nv; j ++)
			if(linked[i][j])
				printf("%d ", color[i][j] + 1);
		printf("0\n");
	}
}
