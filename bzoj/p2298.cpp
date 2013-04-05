#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long bignum_t;
const int N_MAX = 100010;
const int MOD_NUM = 10003; 

struct Intrv
{
	int l, r, v;
	bool operator< (const Intrv &t) const
	{
		return r < t.r;
	}
};

namespace hash
{
	struct Edge
	{
		Intrv vtx;
		Edge *next;
	};
	Edge edge[N_MAX], *begin[MOD_NUM];
	int n_edge = 0;

	inline int calc_hash(int a, int b)
	{
		return ((bignum_t)a * 100001 + b) % MOD_NUM;
	}

	void insert(int l, int r)
	{
		int pos = calc_hash(l, r);
		Edge *e = begin[pos];
		for(; e; e = e->next)
			if(e->vtx.l == l && e->vtx.r == r)
				break;
		if(e)
			e->vtx.v = std::min(r - l + 1, e->vtx.v + 1);
		else
		{
			Edge *e_n = &edge[n_edge ++];
			e_n->vtx.l = l, e_n->vtx.r = r, e_n->vtx.v = 1;
			e_n->next = begin[pos], begin[pos] = e_n;
		}
	}
}

inline bool cross(const Intrv &a, const Intrv &b)
{
	return ! (a.l > b.r || a.r < b.l);
}

Intrv stuff[N_MAX];
int f[N_MAX], n_stuff;

int bsearch(int l, int r, Intrv I)
{
	r ++;
	int mid = (l + r) / 2;
	while(l < r - 1)
	{
		if(cross(stuff[mid], I))
			r = mid;
		else
			l = mid;
		mid = (l + r) / 2;
	}
	return l;
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 0, a, b; i < n; i ++)
	{
		scanf("%d%d", &a, &b);
		if(a + b < n)
		{
			int l = a, r = n - b - 1;
			hash::insert(l, r);
		}
	}
	for(int i = 0; i < MOD_NUM; i ++)
		for(hash::Edge *e = hash::begin[i]; e; e = e->next)
			stuff[++ n_stuff] = e->vtx;
	stuff[0].l = -1, stuff[0].r = -1, stuff[0].v = 0;
	sort(stuff, stuff + n_stuff + 1);
	f[0] = 0;
	for(int i = 1; i <= n_stuff; i ++)
	{
		f[i] = f[i - 1];
		int j = bsearch(0, i - 1, stuff[i]);
		f[i] = std::max(f[i], f[j] + stuff[i].v);
	}
	printf("%d\n", n - f[n_stuff]);
}
