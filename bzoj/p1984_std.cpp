#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cassert>

#define MAXN 100010
#define MAXM MAXN * 2
#define MAXLOG 19

#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

int Count = 0;
int begin[MAXN + 1], end[MAXM + 1], next[MAXM + 1], cost[MAXM + 1], start[MAXM + 1];
void AddEdge(int a, int b, int v)
{
	Count ++;
	next[Count] = begin[a];
	begin[a] = Count;
	start[Count] = a;
	end[Count] = b;
	cost[Count] = v;
}
int n;
#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0) 

#define scan(t) \
{ \
	t = 0; \
	read(); \
	while (!((*pt) >= '0' && (*pt) <= '9')) {pt ++; read();} \
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
}
#define scan_str(s) \
{ \
	int p = 0; \
	read(); \
	while ((*pt) == ' ' || (*pt) == '\n' || (*pt) == '\r') {pt ++; read();}\
	while (!((*pt) == ' ' || (*pt) == '\n' || (*pt) == '\n')) {s[p ++] = (*(pt ++)); read();} \
	s[p] = 0; \
}
void Init()
{
	scan(n);
	int a, b, c;
	for (int i = 1; i <= n - 1; i ++)
	{
		scan(a); scan(b); scan(c);
		AddEdge(a, b, c);
		AddEdge(b, a, c);
	}
}

class Stack
{
	public:
		int x, cur, fa;
};
int top = 0;
Stack stack[MAXN + 1];
#define top(_x, _cur, _fa) \
{ \
	_x = stack[top].x; \
	_cur = stack[top].cur; \
	_fa = stack[top].fa; \
}
#define pop() (top --)
#define push(_x, _cur, _fa) \
{ \
	top ++; \
	stack[top].x = _x; \
	stack[top].cur = _cur; \
	stack[top].fa = _fa; \
}

int f[MAXN * 2 + 1][MAXLOG + 1];
int P[MAXN + 1];
int N;
int dep[MAXN + 1];
int father[MAXN + 1];
bool hash[MAXN + 1];
void Dfs()
{
	top = 0;
	push(1, begin[1], 0);
	int x, cur, fa, ch;
	while (top)
	{
		top(x, cur, fa);
		hash[x] = true;
		pop();
		if (N >= 2 * n)
			break;
		f[++ N][0] = x;
		P[x] = N;
		for (; cur; cur = next[cur])
		{
			ch = end[cur];
			if (ch == fa)
				continue;
			father[ch] = x;
			dep[ch] = dep[x] + 1;
			push(x, next[cur], fa);
			push(ch, begin[ch], x);
			break;
		}
	}
}

int Log[MAXN * 2 + 1];
int LCA(int a, int b)
{
	a = P[a], b = P[b];
	int k;
	if (a > b)
		k = a, a = b, b = k;
	k = Log[b - a + 1];
	int id1 = f[a][k], id2 = f[b - (1 << k) + 1][k];
	if (dep[id1] < dep[id2])
		return id1;
	return id2;
}

void InitLCA()
{
	for (int j = 0; (1 << j) <= N; j ++)
		for (int i = (1 << j); i < (1 << (j + 1)) && i <= N; i ++)
			Log[i] = j;
	int t;
	for (int j = 1; (1 << j) <= N; j ++)
		for (int register i = 1; i <= N; i ++)
		{
			f[i][j] = f[i][j - 1];
			t = i + (1 << (j - 1));
			if (t <= N)
				if (dep[f[t][j - 1]] < dep[f[i][j]])
					f[i][j] = f[t][j - 1];
		}
}

int q[MAXN + 1];
int size[MAXN + 1];
int ptype[MAXN + 1];
int leaf[MAXN + 1];
int Fa[MAXN + 1];
int cntLeaf;
class LSTNode
{
	public:
		int lt, rt, l, r, max, t_modify, t_add;
};
LSTNode node[MAXN * 2 + 1];
int cntLSTNode = 0;
int nseq;
int seq[MAXN + 1];
int fcost[MAXN + 1];
class LST
{
	private:
		int root;
		void Down(int x)
		{
			int t, lc = node[x].lt, rc = node[x].rt;
			if ((t = node[x].t_modify))
			{
				node[lc].max = node[lc].t_modify = t;
				node[lc].t_add = 0;
				node[rc].max = node[rc].t_modify = t;
				node[rc].t_add = 0;
				node[x].t_modify = 0;
			}
			else if ((t = node[x].t_add))
			{
				node[lc].max += t;
				if (node[lc].t_modify)
					node[lc].t_modify += t;
				else
					node[lc].t_add += t;

				node[rc].max += t;
				if (node[rc].t_modify)
					node[rc].t_modify += t;
				else
					node[rc].t_add += t;
				node[x].t_add = 0;
			}
		}
		void Renew(int x)
		{
			int v1 = node[node[x].lt].max, v2 = node[node[x].rt].max;
			node[x].max = MAX(v1, v2);
		}
		void Modify(int x, int l, int r, int v)
		{
			if (node[x].l >= l && node[x].r <= r)
			{
				node[x].max = node[x].t_modify = v;
				node[x].t_add = 0;
			}
			else
			{
				Down(x);
				int mid = (node[x].l + node[x].r) >> 1;
				if (r <= mid)
					Modify(node[x].lt, l, r, v);
				else if (l > mid)
					Modify(node[x].rt, l, r, v);
				else
				{
					Modify(node[x].lt, l, r, v);
					Modify(node[x].rt, l, r, v);
				}
				Renew(x);
			}
		}
		void Add(int x, int l, int r, int v)
		{
			if (node[x].l >= l && node[x].r <= r)
			{
				node[x].max += v;
				if ((node[x].t_modify))
					node[x].t_modify += v;
				else
					node[x].t_add += v;
			}
			else
			{
				Down(x);
				int mid = (node[x].l + node[x].r) >> 1;
				if (r <= mid)
					Add(node[x].lt, l, r, v);
				else if (l > mid)
					Add(node[x].rt, l, r, v);
				else
				{
					Add(node[x].lt, l, r, v);
					Add(node[x].rt, l, r, v);
				}
				Renew(x);
			}
		}
		int Ask(int x, int l, int r)
		{
			if (node[x].l >= l && node[x].r <= r)
				return node[x].max;
			Down(x);
			int mid = (node[x].l + node[x].r) >> 1;
			if (r <= mid)
				return Ask(node[x].lt, l, r);
			else if (l > mid)
				return Ask(node[x].rt, l, r);
			else
			{
				int v1 = Ask(node[x].lt, l, r), v2 =Ask(node[x].rt, l, r);
				if (v1 > v2)
					return v1;
				return v2;
			}
		}
	public:
		void Modify(int l, int r, int v)
		{
			Modify(root, l, r, v);
		}
		void Add(int l, int r, int v)
		{
			Add(root, l, r, v);
		}
		int maxdep;
		int BuildTree(int l, int r, int dep = 0)
		{
			if (dep > maxdep)
				maxdep = dep;
			int x = ++cntLSTNode;
			node[x].l = l, node[x].r = r;
			node[x].lt = node[x].rt = node[x].t_add = node[x].t_modify = node[x].max = 0;
			if (l == r)
				node[x].max = seq[l];
			else
			{
				int mid = (l + r) >> 1;
				node[x].lt = BuildTree(l, mid, dep + 1);
				node[x].rt = BuildTree(mid + 1, r, dep + 1);
				Renew(x);
			}
			return x;
		}
		void SetRoot(int _root)
		{
			root = _root;
		}
		int Ask(int l, int r)
		{
			return Ask(root, l, r);
		}
};
LST Tree[MAXN + 1];
int cntTree;
int tree_belong[MAXN + 1];
int tree_id[MAXN + 1];
void Cut()
{
	int head = 0, tail = 1;
	q[1] = 1;
	while (head != tail)
	{
		int x = q[++ head], fa = father[x];
		for (int register now = begin[x], tmp; now; now = next[now])
		{
			tmp = end[now];
			if (tmp != fa)
			{
				fcost[tmp] = cost[now];
				q[++ tail] = tmp;
			}
		}
	}
	for (int register i = n; i >= 1; i --)
		size[father[q[i]]] += ++ size[q[i]];
	for (int i = 1, x; i <= n; i ++)
	{
		x = i;
		int maxsize = 0, maxid = -1, fa = father[x];
		for (int register now = begin[x], ch; now; now = next[now])
		{
			ch = end[now];
			if (ch == fa)
				continue;
			if (size[ch] > maxsize)
				maxsize = size[ch], maxid = ch;
		}
		if (maxid != -1)
			ptype[maxid] = 1;
		else
			leaf[++ cntLeaf] = x;
	}
	for (int i = 1; i <= cntLeaf; i ++)
	{
		int x = leaf[i], fa = x, y = x;
		if (ptype[x])
		{
			while (ptype[fa])
				fa = father[fa];
			nseq = 0;
			while (ptype[y])
			{
				Fa[y] = fa;
				seq[++nseq] = fcost[y];
				tree_belong[y] = i;
				tree_id[y] = nseq;
				y = father[y];
			}
			//printf("%d\n", nseq);
			Tree[i].SetRoot(Tree[i].BuildTree(1, nseq));
		}
	}
}

void InitTree()
{
	Dfs();
	InitLCA();
	Cut();
}

int GetMax(int u, int fa)
{
	int ret = 0;
	while (dep[u] > dep[fa])
	{
		if (ptype[u] == 0)
		{
			if (fcost[u] > ret)
				ret = fcost[u];
			u = father[u];
		}
		else
		{
			int d = dep[Fa[u]];
			if (d <= dep[fa])
				d = dep[fa] + 1;
			ret = max(ret, Tree[tree_belong[u]].Ask(tree_id[u], tree_id[u] + dep[u] - d));
			u = Fa[u];
		}
	}
	return ret;
}

int Max(int u, int v)
{
	int fa = LCA(u, v);
	return max(GetMax(u, fa), GetMax(v, fa));
}

void AddRoute(int u, int fa, int w)
{
	while (dep[u] > dep[fa])
	{
		if (ptype[u] == 0)
		{
			fcost[u] += w;
			u = father[u];
		}
		else
		{
			int d = dep[Fa[u]];
			if (d <= dep[fa])
				d = dep[fa] + 1;
			Tree[tree_belong[u]].Add(tree_id[u], tree_id[u] + dep[u] - d, w);
			u = Fa[u];
		}
	}
}

void Add(int u, int v, int w)
{
	int fa = LCA(u, v);
	AddRoute(u, fa, w);
	AddRoute(v, fa, w);
}

void Change(int k, int w)
{
	int u = start[k * 2 - 1], v = start[k * 2];
	if (u == father[v])
		u = v;
	if (ptype[u] == 0)
		fcost[u] = w;
	else
		Tree[tree_belong[u]].Modify(tree_id[u], tree_id[u], w);
}

void CoverRoute(int u, int fa, int w)
{
	while (dep[u] > dep[fa])
	{
		if (ptype[u] == 0)
		{
			fcost[u] = w;
			u = father[u];
		}
		else
		{
			int d = dep[Fa[u]];
			if (d <= dep[fa])
				d = dep[fa] + 1;
			Tree[tree_belong[u]].Modify(tree_id[u], tree_id[u] + dep[u] - d, w);
			u = Fa[u];
		}
	}
}

void Cover(int u, int v, int w)
{
	int fa = LCA(u, v);
	CoverRoute(u, fa, w);
	CoverRoute(v, fa, w);
}

void DealOperations()
{
	char s[100] = {0};
	int k, u, v, w;
	while (true)
	{
		scan_str(s);
		if (s[0] == 'S')
			break;
		if (s[0] == 'M') // Max
		{
			scan(u); scan(v);
			printf("%d\n", Max(u, v));
		}
		else if (s[0] == 'A') // Add
		{
			scan(u); scan(v); scan(w);
			Add(u, v, w);
		}
		else // 'C'
		{
			if (s[1] == 'h') // Change
			{
				scan(k); scan(w);
				Change(k, w);
			}
			else // Cover
			{
				scan(u); scan(v); scan(w);
				Cover(u, v, w);
			}
		}
	}
}

void Solve()
{
	InitTree();
	DealOperations();
}

int main()
{
	freopen("t.in", "r", stdin);
	Init();
	Solve();
	return 0;
}
