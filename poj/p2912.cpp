#include <cstdio>
#include <cstring>
#define MAXN 510
#define MAXM 2010
int parent[MAXN], relation[MAXN], err[MAXN];
int query[MAXM][3];
int n, m;

void Make_Set(int x)
{
	parent[x] = x;
	relation[x] = 0;
}

int Find_Set(int x)
{
	if(x == parent[x])
		return x;
	int tmp = parent[x];
	parent[x] = Find_Set(parent[x]);
	relation[x] = (relation[x] + relation[tmp]) % 3;
	return parent[x];
}

void Merge(int x, int y, int d)
{
	int p = Find_Set(x), q = Find_Set(y);
	if(p == q) return;
	parent[p] = q;
	relation[p] = (relation[y] - relation[x] + d + 3) % 3;
}


int main()
{
	freopen("t.in","r",stdin);
	while(!feof(stdin))
	{
		scanf("%d %d\n", &n, &m);
		for(int i = 1; i <= m; i ++)
		{
			char c;
			int a, b;
			scanf("%d%c%d\n", &a, &c, &b);
			a ++, b ++;
			query[i][1] = a, query[i][2] = b;
			if(c == '>') query[i][0] = 1;
			else if(c == '=') query[i][0] = 0;
			else query[i][0] = 2;
		}
		int suc_num = 0;
		int ans_p;
		memset(err, 0, sizeof(err));
		for(int judge = 1; judge <= n; judge ++)
		{
			for(int i = 1; i <= n; i ++) Make_Set(i);
			int i;
			for(i = 1; i <= m; i ++)
			{
				int a = query[i][1], b = query[i][2], d = query[i][0];
				if(a == judge || b == judge) continue;
				int p = Find_Set(a), q = Find_Set(b);
				if(p != q)
					Merge(a, b, d);
				else
					if((d + relation[b]) % 3 != relation[a]) break;
			}
			err[judge] = i;
			if(i == m + 1) 
			{
				ans_p = judge;
				suc_num++;
			}
		}
		if(suc_num == 0) printf("Impossible\n");
		else if(suc_num > 1) printf("Can not determine\n");
		else
		{
			int ans = 0;
			for(int i = 1; i <= n; i ++)
				if(err[i] != m + 1 && err[i] > ans) ans = err[i];
			printf("Player %d can be determined to be the judge after %d lines\n", ans_p - 1, ans);
		}
	}
}
