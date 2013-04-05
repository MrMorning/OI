#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define MAXN 500100
#define INF 100000

using namespace std;

struct node
{
	node *pre, *ch[2];
	int maxs, maxl, maxr, value, sum, size;
	bool same, rev;
} tree[MAXN], *stack[MAXN], *queue[MAXN], *root, *Null;
int top1 = 0, top2 = 0;
int num[MAXN], n, m;


node *New_Node(int x)
{
	node *p;
	if(top2) p = stack[top2 --];
	else p = &tree[top1 ++];
	p->maxs = p->maxl = p->maxr = p->value = p->sum = x;
	p->size = 1;
	p->pre = p->ch[0] = p->ch[1] = Null;
	p->same = p->rev = 0;
	return p;
}

void Clear(node *p)
{
	int head, tail;
	for(head = tail = 1, queue[1] = p; head <= tail; head ++)
		if(queue[head] != Null)
		{
			stack[++ top2] = queue[head];
			queue[++ tail] = queue[head]->ch[0], queue[++ tail] = queue[head]->ch[1];
		}
}

void Update(node *x)
{
	if(x == Null) return;
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
	x->sum = x->ch[0]->sum + x->ch[1]->sum + x->value;
	x->maxl = max(x->ch[0]->maxl, x->ch[0]->sum + x->value + max(0, x->ch[1]->maxl));
	x->maxr = max(x->ch[1]->maxr, x->ch[1]->sum + x->value + max(0, x->ch[0]->maxr));
	x->maxs = max(x->ch[0]->maxs, x->ch[1]->maxs);
	x->maxs = max(x->maxs, max(0, x->ch[0]->maxr) + x->value + max(0, x->ch[1]->maxl));
}

void Make_Same(node *x, int value)
{
	if(x == Null) return;
	x->value = value, x->same = 1, x->sum = x->size * value;
	x->maxl = x->maxr = x->maxs = max(x->value, x->sum);
}

void Reverse(node *x)
{
	if(x == Null) return;
	swap(x->ch[0], x->ch[1]), swap(x->maxl, x->maxr);
	x->rev = ! x->rev;
}

void Push_Down(node *x)
{
	if(x == Null) return;
	if(x->same) 
		Make_Same(x->ch[0], x->value), Make_Same(x->ch[1], x->value), x->same = 0;
	if(x->rev) 
		Reverse(x->ch[0]), Reverse(x->ch[1]), x->rev = 0;
}

void Rotate(node *x, int c)
{
	node *y = x->pre;
	Push_Down(y), Push_Down(x);
	y->ch[! c] = x->ch[c], x->pre = y->pre;
	if(x->ch[c] != Null) x->ch[c]->pre = y;
	if(y->pre != Null) y->pre->ch[y == y->pre->ch[1]] = x;
	x->ch[c] = y, y->pre = x;
	if(y == root) root = x;
	Update(y);
}

void Splay(node *x, node *f)
{
	for(Push_Down(x); x->pre != f; )
	{
		if(x->pre->pre == f)
			Rotate(x, x->pre->ch[0] == x);
		else
		{
			node *y = x->pre, *z = y->pre;
			if(y == z->ch[0])
			{
				if(x == y->ch[0]) Rotate(y, 1), Rotate(x, 1);
				else Rotate(x, 0), Rotate(x, 1);
			}
			else
			{
				if(x == y->ch[1]) Rotate(y, 0), Rotate(x, 0);
				else Rotate(x, 1), Rotate(x, 0);
			}	
		}
	}
	Update(x);
}

void Select(int k, node *f)
{
	node *now;
	for(now = root; ; )
	{
		Push_Down(now);
		int tmp = now->ch[0]->size + 1;
		if(k == tmp) break;
		else
			if(k < tmp)
				now = now->ch[0];
			else
				now = now->ch[1], k -= tmp;
	}
	Splay(now, f);
}

node *Make_Tree(int l,int r,node *f)
{
	if(l > r) return Null;
	int mid = (l + r) >> 1;
	node *p = New_Node(num[mid]);
	p->ch[0] = Make_Tree(l, mid-1, p);
	p->ch[1] = Make_Tree(mid+1, r, p);
	p->pre = f; Update(p);
	return p;
}

void Ins_Num(int pos, int tot)
{
	for(int i = 1; i <= tot; i ++) scanf("%d",&num[i]);
	Select(pos, Null);
   	Select(pos + 1, root);
	root->ch[1]->ch[0] = Make_Tree(1, tot, root->ch[1]);
	Splay(root->ch[1]->ch[0],Null);
}

int main()
{
	freopen("t.in","r",stdin);
	Null = New_Node(-INF), Null->size = Null->sum = 0;
	root = New_Node(-INF), root->ch[1] = New_Node(-INF), root->ch[1]->pre = root;
	Update(root);
	scanf("%d%d",&n,&m),Ins_Num(1,n);
	while(m --)
	{
		char ctrl[20];
		int posi, tot;
		scanf("\n%s",ctrl);
		if(ctrl[2] != 'X') 
		{
			scanf("%d%d",&posi,&tot);
			if(ctrl[0] != 'I')
			Select(posi,Null), Select(posi+tot+1,root);
		}
		switch(ctrl[0])
		{
			case 'I':
				Ins_Num(posi+1,tot);
				break;
			case 'D':
				Clear(root->ch[1]->ch[0]);
				root->ch[1]->ch[0] = Null;
				Splay(root->ch[1], Null);
				break;
			case 'R':
				Reverse(root->ch[1]->ch[0]);
				Splay(root->ch[1], Null);
				break;
			case 'G':
				printf("%d\n",root->ch[1]->ch[0]->sum);
				break;
			case 'M':
				if(ctrl[2] == 'K')
				{
					int c;
					scanf("%d",&c);
					Make_Same(root->ch[1]->ch[0], c);
					Splay(root->ch[1], Null);
					break;
				}
				else
					printf("%d\n",root->maxs);
		}
	}
}
