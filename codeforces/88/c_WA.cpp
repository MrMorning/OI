#include <cstdio>
#include <cstring>
#include <cassert>

bool e[5010][5010];
int nv;
int prev[5010];
bool vis[5010], done[5010];
int seq[5010], seqCnt;
int stk[5010];
int inDgr[5010];
bool found;

void dfs(int u, int term)
{
	if(found)
		return;
	vis[u] = true;
	for(int v = 0; v < nv; v ++)
		if(v != u && !done[v] && e[u][v])
		{
			prev[v] = u;
			if(!vis[v])
				dfs(v, term);
			else if(v == term)
			{
				found = true;
				return;
			}
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	for(int i = 0; i < nv; i ++)
	{
		static char str[5010];
		scanf("%s", str);
		for(int j = 0; j < nv; j ++)
		{
			e[i][j] = str[j] == '1';
			if(i != j)
			{
				if(e[i][j])
					inDgr[j] ++;
			}
		}
	}

	int top = 0;
	for(int i = 0; i < nv; i ++)
		if(inDgr[i] == 0)
			stk[top ++] = i;
	while(top)
	{
		int u = stk[-- top];
		done[u] = true;
		for(int v = 0; v < nv; v ++)
			if(u != v && e[u][v])
			{
				inDgr[v] --;
				if(inDgr[v] == 0)
					stk[top ++] = v;
			}
	}
	bool flag = false;
	for(int i = 0; i < nv; i ++)
		if(!done[i])
		{
			flag = true;
			break;
		}
	if(!flag)
	{
		printf("-1\n");
	}
	else
	{
		memset(inDgr, 0, sizeof(inDgr));
		for(int i = 0; i < nv; i ++)
			for(int j = 0; j < nv; j ++)
				if(e[i][j])
					inDgr[i] ++;
		for(int i = 0; i < nv; i ++)
			if(inDgr[i] == 0)
				stk[top ++] = i;
		while(top)
		{
			int u = stk[-- top];
			done[u] = true;
			for(int v = 0; v < nv; v ++)
				if(u != v && e[v][u])
				{
					inDgr[v] --;
					if(inDgr[v] == 0)
						stk[top ++] = v;
				}
		}

		for(int i = 0; i < nv; i ++)
			if(!done[i])
			{
				memset(prev, -1, sizeof(prev));
				dfs(i, i);
				if(!found)
				{
					printf("haha");
					return 0;
				}
				int j = i;
				while(1)
				{
					seq[seqCnt ++] = i;
					i = prev[i];
					if(i == j)
						break;
				}
				if(seqCnt < 3)
				{
					printf("haha");
					return 0;
				}
				for(int k = seqCnt - 1; k >= 2; k --)
				{
					if(e[i][seq[k]] && e[seq[k - 1]][i])
					{
						printf("%d %d %d\n", i + 1, seq[k] + 1, seq[k - 1] + 1);
						assert(e[seq[k]][seq[k - 1]]);
						return 0;
					}
				}
			}
		printf("haha");
		//assert(0);
	}
}
