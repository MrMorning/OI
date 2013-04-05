#include <cstdio>
#include <algorithm>
#include <iostream>
typedef long long ll;
using namespace std;

const int E_MAX = 100000,
	  N_MAX = E_MAX;

struct Edge
{
	int u, v, w;
	Edge(int _u = 0, int _v = 0, int _w = 0):
		u(_u), v(_v), w(_w){}
	bool operator< (const Edge &t) const
	{
		return w < t.w;
	}
} edge[E_MAX];
int edgeCnt = 0;

int parent[N_MAX], cnt[N_MAX];
int n;

int find(int x)
{
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void merge(int u, int v)
{
	int p = find(u),
		q = find(v);
	parent[p] = q;
	cnt[q] += cnt[p];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0, u, v, w; i < n - 1; i ++)
	{
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		edge[edgeCnt ++] = Edge(u, v, w);
	}
	for(int i = 0; i < n; i ++)
		parent[i] = i, cnt[i] = 1;
	sort(edge, edge + edgeCnt);
	ll res = 0;
	for(int i = 0; i < edgeCnt; i ++)
	{
		int u = edge[i].u, v = edge[i].v;
		res += (ll)(edge[i].w + 1) * cnt[find(u)] * cnt[find(v)];
		merge(u, v);
	}
	cout << res - (n - 1);
}
