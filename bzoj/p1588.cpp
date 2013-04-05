#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 100000 * 2
#define INF 1 << 30
#define	UNDEF INF
struct node
{
	node *pre, *ch[2];
	int value, size;
} tree[MAXN], *root, *Null;
int top1 = 0;
int n;
long long ans = 0;

node *New_Node(int v)
{
	node *x;
	x = &tree[top1 ++];
	x->value = v, x->size = 1;
	x->pre = x->ch[0] = x->ch[1] = Null;
	return x;
}

void Update(node *x)
{
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
}

void Rotate(node *x, int c)
{
	node *y = x->pre;
	y->ch[! c] = x->ch[c];
	if(x->ch[c] != Null) x->ch[c]->pre = y;
	x->pre = y->pre;
	if(y->pre != Null) y->pre->ch[y == y->pre->ch[1]] = x;
	y->pre = x, x->ch[c] = y;
	if(y == root) root = x;
	Update(y);
}

void Splay(node *x, node *f)
{
	while(x->pre != f)
	{
		if(x->pre->pre == f)
			Rotate(x, x->pre->ch[0] == x);
		else
		{
			node *y = x->pre, *z = y->pre;
			if(y == z->ch[0])
				if(x == y->ch[0]) Rotate(y, 1), Rotate(x, 1);
				else Rotate(x, 0), Rotate(x, 1);
			else
				if(x == y->ch[1]) Rotate(y, 0), Rotate(x, 0);
				else Rotate(x, 1), Rotate(x, 0);
		}
	}
	Update(x);
}

node *Insert(int value)
{
	node *now, *p;
	for(now = root; ; )
	{
		if(now->value > value) 
		{
			if(now->ch[0] != Null) now = now->ch[0];
			else break;
		}
		else 
			if(now->ch[1] != Null) now = now->ch[1];
			else break;
	}
	if(now->value > value)
	{
		now->ch[0] = New_Node(value);
		p = now->ch[0];
	}
	else
	{
		now->ch[1] = New_Node(value);
		p = now->ch[1];
	}
	p->pre = now;
	Splay(p, Null);
	return p;
}

int main()
{
	freopen("t.in","r",stdin);
	Null = New_Node(UNDEF), Null->size = 0;
	root = New_Node(UNDEF), root->ch[1] = New_Node(UNDEF), root->ch[1]->pre = root;
	Update(root);
	scanf("%d",&n);
	int i = 0;
	while(i < n)
	{
		i++;
		int v = 0;
		////if(feof(stdin)) v = 0;
		scanf("%d",&v);
		node *p = Insert(v);
		if(i == 1)
		{
			ans = v;
			continue;
		}
		node *x = p->ch[0];
		if(x != Null)
			while(x->ch[1] != Null) x = x->ch[1];
		node *y = p->ch[1];
		if(y != Null)
			while(y->ch[0] != Null) y = y->ch[0];
		if(x == Null) ans += abs(y->value - v);
		else if(y == Null) ans += abs(x->value - v);
		else ans += min(abs(x->value - v), abs(y->value - v));
	}
	printf("%lld\n",ans);
}

