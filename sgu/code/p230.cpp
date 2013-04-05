#include <cstdio>
#include <cstring>
#include <cstdlib>

const int V_MAX = 100;
bool e[V_MAX][V_MAX], done[V_MAX];
int inDgr[V_MAX];
int stk[V_MAX], top;
int ans[V_MAX];
int nv;

int main()
{
	freopen("t.in", "r", stdin);
	int ne;
	scanf("%d%d", &nv, &ne);
	for(int i = 0, a, b; i < ne; i ++)
	{
		scanf("%d%d", &a, &b);
		a --, b --;
		e[a][b] = true;
	}
	for(int u = 0; u < nv; u ++)
		for(int v = 0; v < nv; v ++)
			if(e[u][v])
				inDgr[v] ++;
	for(int u = 0; u < nv; u ++)
		if(inDgr[u] == 0)
			stk[top ++] = u;
	int weightIdx = 0;
	while(top)
	{
		int u = stk[-- top];
		done[u] = true;
		ans[u] = weightIdx ++;
		for(int v = 0; v < nv; v ++)
			if(e[u][v])
			{
				inDgr[v] --;
				if(inDgr[v] == 0)
					stk[top ++] = v;
			}
	}
	for(int i = 0 ; i < nv; i ++)
		if(!done[i])
		{
			printf("No solution\n");
			return 0;
		}
	for(int i = 0 ; i < nv; i ++)
		printf("%d ", ans[i] + 1);
}
