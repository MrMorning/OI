#include <cstdio>
#include <algorithm>

using std::sort;

typedef long long bignum_t;
const int MOD_NUM = 9699691;
const int N_MAX = 100010;

inline int calc_hash(int a, int b)
{
	return ((bignum_t)a * 100010 + b) % MOD_NUM;
}

struct Intrv
{
	int l, r, v;
	bool operator< (const Intrv &t) const
	{
		return r < t.r;
	}
};

inline bool cross(const Intrv &a, const Intrv &b)
{
	return ! (a.l > b.r || a.r < b.l);
}

Intrv table[MOD_NUM];
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
	//freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 0, a, b; i < n; i ++)
	{
		scanf("%d%d", &a, &b);
		if(a + b < n)
		{
			int l = a, r = n - b - 1;
			int pos = calc_hash(l, r);
			table[pos].v = std::min(table[pos].v + 1, r - l + 1);
			table[pos].l = l, table[pos].r = r;
		}
	}
	for(int i = 0; i < MOD_NUM; i ++)
		if(table[i].v)
			stuff[++ n_stuff] = table[i];
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
