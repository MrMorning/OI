#include <cstdio>
#include <algorithm>
#define MAXN 111
class set_t
{
	int p[MAXN], rank[MAXN], n;/*{{{*/
	public:
		set_t(int _n): n(_n)
		{
			for(int i = 1; i <= n; i ++)
				p[i] = i, rank[i] = 0;
		}
		void combine(int u, int v)
		{
			u = find(u), v = find(v);
			if(u == v)
				return;
			if(rank[u] > rank[v])
				p[v] = u;
			else
			{
				p[u] = v;
				if(rank[u] == rank[v])
					rank[v] ++;
			}
		}
		int find(int u)
		{
			if(u != p[u])
				p[u] = find(p[u]);
			return p[u];
		}
/*}}}*/
};

struct edge_t
{
	int v1, v2, w;
	bool operator< (const edge_t &x) const
	{return w < x.w;}
} edge[1012];

int totCnt, f[MAXN], b[MAXN], n, m, nKind;
bool used[MAXN];

void search(int i, int j, int target, set_t &S)
{
	if(i > b[j])
	{
		static set_t S2(n);
		S2 = S;
		int cnt = f[j - 1];
		for(int k = b[j - 1] + 1; k <= b[j]; k ++)
			if(used[k])
			{
				if(S2.find(edge[k].v1) == S2.find(edge[k].v2))
					return;
				S2.combine(edge[k].v1, edge[k].v2), cnt --;
			}
		if(cnt == target)
			totCnt ++;
		return;
	}
	used[i] = true;
	search(i + 1, j, target, S);
	used[i] = false;
	search(i + 1, j, target, S);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d%d%d", &edge[i].v1, &edge[i].v2, &edge[i].w);
	std::sort(edge + 1, edge + 1 + m);
	int cnt = f[0] = n;
	set_t S(n);
	edge[m + 1].w = 0;
	for(int i = 1; i <= m; i ++)
	{
		if(S.find(edge[i].v1) != S.find(edge[i].v2))
			S.combine(edge[i].v1, edge[i].v2), cnt --;
		if(edge[i].w != edge[i + 1].w)
			f[++ nKind] = cnt, b[nKind] = i;
	}
	if(cnt > 1)
		printf("0\n");
	else
	{
		int ans = 1;
		set_t S1(n);
		for(int i = 1; i <= nKind; i ++)
		{
			totCnt = 0;
			search(b[i - 1] + 1, i, f[i], S1);
			ans = (ans * totCnt) % 31011;
			for(int j = b[i - 1] + 1; j <= b[i]; j ++)
				S1.combine(edge[j].v1, edge[j].v2);
		}
		printf("%d\n", ans);
	}
}
