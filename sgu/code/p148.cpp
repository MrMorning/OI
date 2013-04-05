#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>

const int N_MAX = 15100;
const int oo = 0x3f3f3f3f;

namespace splay
{
	struct Node
	{
		Node *ch[2], *pre;
		int val, tag, idx,;
	} nodePool[N_MAX], *root, *null;
	int freePos;

	Node *alloc(int _val, int _idx)
	{
		Node *x = &nodePool[freePos ++];
		x->idx = _idx, x->val = _val;
		x->tag = 0;
		x->ch[0] = x->ch[1] = x->pre = null;
		return x;
	}

	void markTag(Node *x, int tag)
	{
		if(x == null)
			return;
		x->val += tag;
		x->tag += tag;
	}

	void pushDown(Node *x)
	{
		if(x->tag)
		{
			markTag(x->ch[0], x->tag);
		   	markTag(x->ch[1], x->tag);
			x->tag = 0;
		}
	}

	void rotate(Node *x, int t)
	{
		Node *y = x->pre;
		pushDown(y); pushDown(x);
		x->pre = y->pre;
		if(y->pre != null)
			y->pre->ch[y == y->pre->ch[1]] = x;
		y->ch[!t] = x->ch[t];
		if(x->ch[t] != null)
			x->ch[t]->pre = y;
		x->ch[t] = y, y->pre = x;
		if(root == y)
			root = x;
	}

	void splay(Node *x, Node *fa)
	{
		for(pushDown(x); x->pre != fa; )
		{
			if(x->pre->pre == fa)
				rotate(x, x == x->pre->ch[0]);
			else
			{
				Node *y = x->pre, *z = y->pre;
				if(y == z->ch[0])
				{
					if(x == y->ch[0])
						rotate(y, 1), rotate(x, 1);
					else
						rotate(x, 0), rotate(x, 1);
				}
				else
				{
					if(x == y->ch[1])
						rotate(y, 0), rotate(x, 0);
					else
						rotate(x, 1), rotate(x, 0);
				}
			}
		}
	}

	void insert(Node *x)
	{
		if(root == null)
		{
			root = x;
			return;
		}
		Node *now = root, *pre;
		while(now != null)
		{
			pre = now;
			pushDown(now);
			if(now->val < x->val)
				now = now->ch[1];
			else
				now = now->ch[0];
		}
		pre->ch[x->val > pre->val] = x;
		x->pre = pre;
		splay(x, null);
	}

	int search()
	{
		if(root == null)
			return -1;
		Node *now = root;
		while(now->ch[0] != null)
			pushDown(now), now = now->ch[0];
		pushDown(now);
		if(now->val >= 0)
			return -1;
		int res = now->idx;
		if(now->ch[1] == null)
		{
			if(now->pre == null)
				root = null;
			else
			{
				now->pre->ch[now == now->pre->ch[1]] = null;
				splay(now->pre, null);
			}
		}
		else
		{
			if(now->pre == null)
				root = now->ch[1], now->ch[1]->pre = null;
			else
				now->pre->ch[now == now->pre->ch[1]] = now->ch[1], now->ch[1]->pre = now->pre;
			splay(now->ch[1], null);
		}
		return res;
	}

	void addAll(int val)
	{
		markTag(root, val);
	}

	void init()
	{
		freePos = 0;
		null = alloc(0, 0);

		root = null;
	}
};

int n, W[N_MAX], L[N_MAX], P[N_MAX];
bool used[N_MAX];

int main()
{
	splay::init();

	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d%d%d", &W[i], &L[i], &P[i]);
	int res = 0;
	int ans = oo;
	int best = -1;
	for(int i = n - 1; i >= 0; i --)
	{
		splay::insert(splay::alloc(L[i], i));
		splay::addAll(-W[i]);
		res += P[i];
		while(1)
		{
			int x = splay::search();
			if(x == -1)
				break;
			res -= P[x];
		}
		if(res < ans)
			best = i, ans = res;
	}

	splay::freePos = 0;
	splay::init();

	res = 0;
	for(int i = n - 1; i >= best; i --)
	{
		splay::insert(splay::alloc(L[i], i));
		splay::addAll(-W[i]);
		res += P[i];
		used[i] = true;
		while(1)
		{
			int x = splay::search();
			if(x == -1)
				break;
			res -= P[x];
			used[x] = false;
		}
	}
	for(int i = 0; i < n; i ++)
		if(used[i])
			printf("%d\n", i + 1);
}
