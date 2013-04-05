#include <cstdio>
#include <algorithm>
#define MAXN 101100
#define INF 10100
#define FOR(i,s,t) for(int i = s; i <= t; i ++)

using namespace std;

struct node
{
	int value, size, sum, maxl, maxr, maxs;
	node *ch[2], *pre;
} tree[MAXN], *queue[MAXN], *stack[MAXN], *Null, *root;
int A[MAXN], top1 = 0, top2 = 0;
int n, m;

node *New_Node(int x)
{
	node *p;
	if(top2) p = stack[top2 --]; else p = &tree[top1 ++];
	p->value = p->sum = p->maxl = p->maxr = p->maxs = x;
	p->ch[1] = p->ch[0] = p->pre = Null;
	return p;
}

void Clear(node *x)
{
	int head, tail;
	for(head = tail = 1, queue[1] = x; head <= tail; head ++)
	{
		if(queue[head] != Null)
		{
			stack[++ top2] = queue[head];
			queue[++ tail] = queue[head]->ch[0], queue[++ tail] = queue[head]->ch[1];
		}
	}
}

void Update(node *x)
{
	if(x == Null) return;
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
	x->sum = x->ch[0]->sum + x->ch[1]->sum + x->value;
	x->maxl = max(x->ch[0]->maxl, x->ch[0]->sum + x->value + max(0, x->ch[1]->maxl));
	x->maxr = max(x->ch[1]->maxr, max(0, x->ch[0]->maxr) + x->value + x->ch[1]->sum);
	x->maxs = max(x->ch[0]->maxs, x->ch[1]->maxs);
	x->maxs = max(x->maxs, max(0, x->ch[0]->maxr) + max(0, x->ch[1]->maxl) + x->value);
}

void Rotate(node *x, int c)
{
	node *y = x->pre;
	y->ch[! c] = x->ch[c], x->pre = y->pre;
	if(x->ch[c] != Null) x->ch[c]->pre = y;
	if(y->pre != Null) y->pre->ch[y->pre->ch[1] == y] = x;
	y->pre = x, x->ch[c] = y;
	if(y == root) root = x;
	Update(y);
}

void Splay(node *x, node *f)
{
	while(x->pre != f)
		if(x->pre->pre == f)
			Rotate(x, x->pre->ch[0] == x);
		else
		{
			node *y = x->pre, *z = y->pre;
			if(z->ch[0] == y)
			{
				if(y->ch[0] == x)
					Rotate(y, 1), Rotate(x, 1);
				else
					Rotate(x, 0), Rotate(x, 1);
			}
			else
			{
				if(y->ch[1] == x)
					Rotate(y, 0), Rotate(x, 0);
				else
					Rotate(x, 1), Rotate(x, 0);
			}
		}
	Update(x);
}

void Select(int k, node *f)
{
	node *now;
	for(now = root; ; )
	{
		int tmp = now->ch[0]->size;
		if(tmp + 1 == k) break;
		if(k <= tmp) now = now->ch[0];
		else now = now->ch[1], k -= tmp + 1;
	}
	Splay(now, f);
}

node *Make_Tree(int l,int r, node *f)
{
	if(l > r) return Null;
	int mid = (l + r) >> 1;
	node *p = New_Node(A[mid]);
	p->ch[0] = Make_Tree(l, mid-1, p);
	p->ch[1] = Make_Tree(mid+1, r, p);
	p->pre = f, Update(p);
	return p;
}

void Ins_Num(int pos, int tot)
{
	Select(pos, Null);
	Select(pos+1, root);
	root->ch[1]->ch[0] = Make_Tree(1, tot, root->ch[1]);
	Splay(root->ch[1]->ch[0], Null);
}

int main()
{
	freopen("t.in", "r", stdin);

	Null = New_Node(-INF), Null->size = Null->sum = 0, root = New_Node(-INF);
	root->ch[1] = New_Node(-INF), root->ch[1]->pre = root;
	Update(root);
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d",&A[i]);
	Ins_Num(1,n);
	scanf("%d",&m);
	FOR(i,1,m)
	{
		char opt;
		int x,y;
		scanf("\n%c %d",&opt,&x);	
		if(opt != 'D') scanf("%d",&y);
		switch(opt)
		{
			case 'I':
				A[1] = y;
				Ins_Num(x,1);
				break;
			case 'D':
				Select(x,Null); Select(x+2,root);
				Clear(root->ch[1]->ch[0]);
				root->ch[1]->ch[0] = Null; Splay(root->ch[1], Null);
				break;
			case 'R':
				Select(x+1,Null);
				root->value = y;
				Update(root);
				break;
			case 'Q':
				Select(x,Null);
			   	Select(y+2,root);
				printf("%d\n",root->ch[1]->ch[0]->maxs);
				break;
			default:
				printf("ERROR!");
		}
	}
}
