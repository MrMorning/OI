#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>

#define MAXN 1010

using std::map;

int parent[MAXN], relation[MAXN];
int n, p1, p2, m;
int w[MAXN][2], f[MAXN][310], choose[MAXN][310];
int son[MAXN][MAXN];

int comp(const void *a, const void *b)
{return *(int*)a - *(int*)b;}

void Make_Set(int x)
{
	parent[x] = x;
	relation[x] = 1;
}

int Find_Set(int x)
{
	if(x != parent[x])
	{
		int tmp = parent[x];
		parent[x] = Find_Set(parent[x]);
		relation[x] = ! (relation[x] ^ relation[tmp]);
	}
	return parent[x];
}

void Union(int x, int y, int d)
{
	int p = Find_Set(x), q = Find_Set(y);
	if(p == q) return;
	parent[p] = q;
	relation[p] = relation[x] ^ d ^ relation[y];
}

void solve()
{
	bool failed = false;
	n =  p1 + p2;
	for(int i = 1; i <= n; i ++) Make_Set(i);
	for(int i = 1; i <= m; i ++)
	{
		char ctrl[20];
		int a, b, d;
		scanf("%d %d %s\n", &a, &b, ctrl);
		if(failed) continue;
		if(ctrl[0] == 'n') d = 0;
		else d = 1;
		int p = Find_Set(a), q = Find_Set(b);
		if(p != q)
			Union(a, b, d);
		else
			if(! (d ^ relation[b]) != relation[a])
				failed = true;
	}
	if(failed)
	{
		printf("no\n");
		return;
	}
	else
	{
		//init array w[]
		map<int, int> index;
		int rootNum = 0;
		for(int i = 1; i <= n; i ++)
		{
			parent[i] = Find_Set(i);
			if(i == parent[i]) 
			{
				if(index.find(i) == index.end())
					index[i] = ++rootNum;
			}
			//????????????????????else
		}
		for(int i = 1;i <= n; i ++)
			son[index[parent[i]]][++ son[index[parent[i]]][0]] = i;
		for(int i = 1; i <= rootNum; i ++)
		{
			int t = 0, cnt = 0;
			for(int j = 1; j <= son[i][0]; j ++)
			{
				int k = son[i][j];
				cnt += ! (relation[k] ^ t);
			}
			w[i][0] = cnt;
			t = 1, cnt = 0;
			for(int j = 1; j <= son[i][0]; j ++)
			{
				int k = son[i][j];
				cnt += ! (relation[k] ^ t);
			}
			w[i][1] = cnt;
		}
		//DP
		f[0][0] = 1; 
		for(int i = 1; i <= rootNum; i ++)
			for(int j = 0; j <= p1; j ++)
			{
				f[i][j] = 0;
				if(j >= w[i][0]) 
				{
					f[i][j] += f[i - 1][j - w[i][0]];
					if(f[i - 1][j - w[i][0]]) choose[i][j] = 0;
				}
				if(j >= w[i][1]) 
				{
					f[i][j] += f[i - 1][j - w[i][1]];
					if(f[i - 1][j - w[i][1]]) choose[i][j] = 1;
				}
				if(f[i][j] > 2) f[i][j] = 2;
			}
		if(f[rootNum][p1] != 1)
			printf("no\n");
		else
		{
			int seq[MAXN], seqNum = 0;
			int t = p1;
			for(int i = rootNum; i >= 1; i --)
			{
				int m = choose[i][t];
				for(int j = 1; j <= son[i][0]; j ++)
				{
					int k = son[i][j];
					if(! (relation[k] ^ m)) seq[++ seqNum] = k;
				}
				t -= w[i][m];
			}
			qsort(seq + 1, seqNum, sizeof(int), comp);
			for(int i = 1; i <= seqNum; i ++)
				printf("%d\n",seq[i]);
			printf("end\n");
		}
	}
}

int main()
{
	freopen("t.in","r",stdin);
	while(1)
	{
		scanf("%d %d %d\n", &m, &p1, &p2);
		if(m == 0 && p1 ==0 && p2 == 0) 
			break;
		memset(w, 0 ,sizeof(w)), memset(f, 0 ,sizeof(f)), memset(choose, 0 ,sizeof(choose));
		memset(son, 0 ,sizeof(son));
		solve();
	}
}
