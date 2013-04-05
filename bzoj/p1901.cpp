#include <cstdio>
#include <cstdlib>
#define MAXN 20010
#define ASSERT(b) if(!b) exit(1)
const int INFINITY = 0x3f3f3f3f;
struct intrv_t
{
	int l, r;
	intrv_t(){};
	intrv_t(int _l, int _r): l(_l), r(_r){};
	int size(){return r - l + 1;}
	bool contain(int x){return x >= l && x <= r;}
};
class splay_t
{
	private:
		struct node_t
		{
			int size, val, cnt;
			node_t *ch[2], *pre;
		} *root, *null;
		static node_t node[MAXN * 14], *stack[MAXN * 14];
		static int top, nodeIdx;
		node_t *nodeAlloc(int val);
		void rotate(node_t *u, int c);
		void splay(node_t *u, node_t *p);
		void update(node_t *u);
		void clear(node_t *u);
		node_t *getNeighbor(node_t *u, int c);
		node_t *find(int val);
	public:
		splay_t();
		void remove(int val);
		void insert(int val);
		int select(int k);
		intrv_t getRank(int val);
};
splay_t::node_t splay_t::node[MAXN * 14], *splay_t::stack[MAXN * 14];/*{{{*/
int splay_t::top, splay_t::nodeIdx;
int a[MAXN];
splay_t::splay_t()
{
	null = nodeAlloc(INFINITY), null->size = null->cnt = 0;
	root = null;
}
splay_t::node_t *splay_t::nodeAlloc(int val)
{
	node_t *u;
	if(top) u = stack[-- top];
	else u = &splay_t::node[splay_t::nodeIdx ++];
	u->pre = u->ch[0] = u->ch[1] = null;
	u->size = u->cnt = 1, u->val = val;
	return u;
}
void splay_t::rotate(node_t *u, int c)
{
	node_t *p = u->pre;
	u->pre = p->pre;
	if(p->pre != null)
		p->pre->ch[p == p->pre->ch[1]] = u;
	p->ch[! c] = u->ch[c];
	if(u->ch[c] != null)
		u->ch[c]->pre = p;
	p->pre = u, u->ch[c] = p;
	if(p == root)
		root = u;
	update(p);
}

void splay_t::splay(node_t *u, node_t *p)
{
	while(u->pre != p)
	{
		if(u->pre->pre == p)
			rotate(u, u == u->pre->ch[0]);
		else
		{
			node_t *v = u->pre, *w = v->pre;
			if(v == w->ch[0])
			{
				if(u == v->ch[0])
					rotate(v, 1), rotate(u, 1);
				else
					rotate(u, 0), rotate(u, 1);
			}
			else
			{
				if(u == v->ch[1])
					rotate(v, 0), rotate(u, 0);
				else
					rotate(u, 1), rotate(u, 0);
			}
		}
	}
	update(u);
}
void splay_t::update(node_t *u)
{
	u->size = u->ch[0]->size + u->ch[1]->size + u->cnt;
}
splay_t::node_t *splay_t::getNeighbor(node_t *u, int c)
{
	if(u->ch[c] == null) return null;
	for(u = u->ch[c]; u->ch[! c] != null; u = u->ch[! c]);
	return u;
}
splay_t::node_t *splay_t::find(int val)
{
	node_t *u = root, *p = null;
	for(; u != null && p->val != val; p = u, u = u->ch[val > u->val]);
	return p;
}
void splay_t::clear(node_t *u)
{
	splay_t::stack[splay_t::top ++] = u;
}
void splay_t::remove(int val)
{
	node_t *u = find(val); 
	ASSERT(u->val == val);
	splay(u, null);
	if(u->cnt > 1)
	{
		u->cnt --, u->size --;
		return;
	}
	node_t *pred = getNeighbor(u, 0), *succ = getNeighbor(u, 1);
	if(pred == null && succ == null)
		root = null;
	else if(pred == null)
		splay(succ, null), succ->ch[0] = null, update(succ);
	else if(succ == null)
		splay(pred, null), pred->ch[1] = null, update(pred);
	else
		splay(pred, null), splay(succ, root), succ->ch[0] = null, splay(succ, null);
	clear(u);
}
void splay_t::insert(int val)
{
	if(root == null)
	{
		root = nodeAlloc(val);
		return;
	}
	node_t *u = find(val);
	if(u->val == val)
		u->cnt ++, splay(u, null);
	else
		u->ch[val > u->val] = nodeAlloc(val), u->ch[val > u->val]->pre = u, splay(u->ch[val > u->val], null);
}
int splay_t::select(int k)
{
	node_t *u = root;
	while(1)
	{
		intrv_t tmpPir = intrv_t(u->ch[0]->size + 1, u->ch[0]->size + u->cnt);
		if(tmpPir.contain(k))
			return u->val;
		else if(k < tmpPir.l)
			u = u->ch[0];
		else
			u = u->ch[1], k -= tmpPir.r;
	}
}
intrv_t splay_t::getRank(int val)
{
	insert(val);
	intrv_t res = intrv_t(root->ch[0]->size + 1, root->ch[0]->size + root->cnt - 1);
	remove(val);
	return res;
}/*}}}*/
struct segNode_t
{
	splay_t T;
	int l, r;
} node[MAXN << 2];
void build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	for(int j = l; j <= r; j ++)
		node[i].T.insert(a[j]);
	if(l < r)
	{
		build(i * 2, l, (l + r) / 2);
	   	build(i * 2 + 1, (l + r) / 2 + 1, r);
	}
}
void change(int i, int pos, int val)
{
	if(node[i].l > pos || node[i].r < pos)
		return;
	node[i].T.remove(a[pos]), node[i].T.insert(val);
	if(node[i].l == pos && node[i].r == pos)
		return;
	change(i * 2, pos, val), change(i * 2 + 1, pos, val);
}
intrv_t ask(int i, int l, int r, int val)
{
	if(node[i].l > r || node[i].r < l)
		return intrv_t(1, 0);
	if(l <= node[i].l && node[i].r <= r)
		return node[i].T.getRank(val);
	intrv_t p1 = ask(i * 2, l, r, val);
   	intrv_t	p2 = ask(i * 2 + 1, l, r, val);
	return intrv_t(p1.l + p2.l - 1, p1.r + p2.r);
}
int main()
{
	freopen("t.in", "r", stdin);
	int n, m;
	char ctrl[2];
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	build(1, 1, n);
	while(m --)
	{
		scanf("%s", ctrl);
		if(ctrl[0] == 'C')
		{
			int i, t;
			scanf("%d%d", &i, &t);
			change(1, i, t), a[i] = t;
		}
		else
		{
			int i, j, k;
			scanf("%d%d%d", &i, &j, &k);
			int l = 1, r = n, mid = (l + r) / 2;
			while(l <= r)
			{
				int tmp = node[1].T.select(mid);
				intrv_t res = ask(1, i, j, tmp);
				if(res.size() && res.contain(k))
				{
					printf("%d\n", tmp);
					break;
				}
				if(k < res.l)
					r = mid - 1;
				else
					l = mid + 1;
				mid = (l + r) / 2;
			}
		}
	}
}
