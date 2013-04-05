#include <cstdio>
#include <functional>
#include <algorithm>
#include <vector>
#define foreach(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)
using namespace std;

typedef long long ll;
#ifdef unix
	#define LL_FMT "%lld"
#else
	#define LL_FMT "%I64d"
#endif

const int N_MAX = 2 * 100010;

namespace sgt
{
	struct Node
	{
		int l, r;
		ll maxVal;
		ll tag;
	} node[N_MAX * 4];

	void update(int i)
	{
		node[i].maxVal = max(node[i * 2].maxVal, node[i * 2 + 1].maxVal);
	}

	void build(int i, int l, int r)
	{
		Node &x = node[i];
		x.l = l, x.r = r;
		x.maxVal = 0;
		x.tag = 0;

		if(l == r)
			return;
		build(i * 2, l, (l + r) / 2);
		build(i * 2 + 1, (l + r) / 2 + 1, r);
	}

	void mark(int i, ll val)
	{
		node[i].tag += val;
		node[i].maxVal += val;
	}

	void pushDown(int i)
	{
		if(node[i].tag)
		{
			mark(i * 2, node[i].tag);
			mark(i * 2 + 1, node[i].tag);
			node[i].tag = 0;
		}
	}

	void add(int i, int l, int r, ll val)
	{
		Node &x = node[i];
		if(l > x.r || r < x.l)
			return;
		if(l <= x.l && x.r <= r)
		{
			mark(i, val);
			return;
		}
		pushDown(i);
		add(i * 2, l, r, val);
		add(i * 2 + 1, l, r, val);
		update(i);
	}

	ll ask(int i, int l, int r)
	{
		Node &x = node[i];
		if(l > x.r || r < x.l)
			return 0;
		if(l <= x.l && x.r <= r)
			return x.maxVal;
		pushDown(i);
		ll res = max(ask(i * 2, l, r), ask(i * 2 + 1, l, r));
		update(i);
		return res;
	}
}

vector<pair<int, int> > adj[N_MAX];
ll f[N_MAX], cost[N_MAX];
int n, m;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	sgt::build(1, 0, n);
	for(int i = 1, c; i <= n; i ++)
	{
		scanf("%d", &c);
		cost[i] = cost[i - 1] + c;
	}
	for(int i = 0, l, r, p; i < m; i ++)
	{
		scanf("%d%d%d", &l, &r, &p);
		adj[r].push_back(make_pair(l, p));
	}
	for(int i = 1; i <= n; i ++)
	{
		foreach(it, adj[i])
			sgt::add(1, 0, it->first - 1, it->second);
		f[i] = f[i - 1];
		f[i] = max(f[i], sgt::ask(1, 0, i - 1) - cost[i]);
		sgt::add(1, i, i, f[i] + cost[i]);
	}
	printf(LL_FMT "\n", f[n]);
}
