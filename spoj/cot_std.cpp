#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 400100;
int i, n, m, num, tot, ol[maxn], bh[maxn], w[30], f[maxn][30], lim, e[maxn], next[maxn], first[maxn], go[maxn], lo[maxn+10];
struct Tpoint
{
	int pos, dep, f, k;
}a[maxn];
struct node
{
	node *l, *r;
	int a, b, num;
}tree[maxn * 20], *root[maxn];
void link(int x, int y)
{
	e[++num] = y, next[num] = first[x], first[x] = num;
}
int com(int p, int q)
{
	return a[p].k < a[q].k;
}
void dfsol(int x)
{
	a[x].dep = a[a[x].f].dep + 1;
	ol[a[x].pos = ++num] = x;
	for (int p = first[x]; p; p = next[p])
		if (e[p] != a[x].f)
		{
			a[e[p]].f = x;
			dfsol(e[p]);
			ol[++num] = x;
		}
}
int minol(int x, int y)
{
	return a[x].dep <= a[y].dep ? x : y;
}
void origanLCA()
{
	int j = 1;
	lo[1] = num = 0;
	num = 0;
	dfsol(1);
	for (i = 1, w[0] = 1; i <= 25; ++i)
		w[i] = w[i - 1] << 1;
	for (i = 2, j = 1; i < maxn; ++i)
	{
		if (w[j + 1] <= i) ++j;
		lo[i] = j;
	}
	lim = lo[num];
	for (i = 1; i <= num; ++i) f[i][0] = ol[i];
	for (i = 1; i <= lim; ++i)
		for (int j = 1; j <= num; ++j)
			if (j + w[i] - 1 <= num)
				f[j][i] = minol(f[j + w[i - 1]][i - 1], f[j][i - 1]);
}
node *build(int l, int r)
{
	node *p = &tree[++num];
	p->a = l, p->b = r;
	p->num = 0;
	if (l == r) return p;
	int mid = l + r >> 1;
	p->l = build(l, mid);
	p->r = build(mid + 1, r);
	return p;
}
node *change(node *p, int x, int s)
{
	node *q = &tree[++num];
	q->num = p->num + s;
	q->l = p->l, q->r = p->r;
	q->a = p->a, q->b = p->b;
	if (p->a == x && p->b == x) return q;
	int mid = p->a + p->b >> 1;
	if (x <= mid) q->l = change(p->l, x, s);
	else q->r = change(p->r, x, s);
	return q;
}
void dfsxds(int x)
{
	root[x] = change(root[a[x].f], a[x].k, 1);
	for (int p = first[x]; p; p = next[p])
		if (e[p] != a[x].f) dfsxds(e[p]);
}
int find(node *u, node *v, node *flca, int k, int h)
{
	if (u->a == u->b) return u->a;
	int mid = u->l->num + v->l->num - 2 * flca->l->num;
	if (h >= u->l->a && h <= u->l->b) ++mid; 
	if (k <= mid) return find(u->l, v->l, flca->l, k, h);
	else return find(u->r, v->r, flca->r, k - mid, h);
}
int ask(int u, int v, int k)
{
	int l = a[u].pos, r = a[v].pos;
	if (l > r) swap(l, r);
	lim = lo[r - l + 1];
	int x = minol(f[l][lim], f[r - w[lim] + 1][lim]);
	return find(root[u], root[v], root[x], k, a[x].k);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i)
		scanf("%d", &a[bh[i] = i].k);
	sort(bh + 1, bh + n + 1, com);
	for (i = 2, go[tot = 1] = a[bh[1]].k, a[bh[1]].k = 1; i <= n; ++i)
		a[bh[i]].k = a[bh[i]].k == go[tot] ? tot : (go[tot + 1] = a[bh[i]].k, ++tot);
	int x, y, u, v, k;
	for (i = 1; i < n; ++i)
	{
		scanf("%d%d", &x, &y);
		link(x, y), link(y, x);
	}
	origanLCA();
	num = 0;
	root[0] = build(1, tot);
	dfsxds(1);
	for (; m; --m)
	{
		scanf("%d%d%d", &u, &v, &k);
		printf("%d\n", go[ask(u, v, k)]);
	}
	return 0;
}

