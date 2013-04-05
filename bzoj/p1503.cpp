#include <cstdio>
#define MAXN 101000 * 2
#define INF 1000000000
struct Node
{
	int size, value, count;
	Node *pre, *ch[2];
} tree[MAXN], *queue[MAXN], *stack[MAXN], *Null, *root;
int top1, top2;
int n,min;
Node *New_Node(int value)
{
	Node *x;
	if(top2) x = stack[top2 --]; else x = &tree[top1 ++];
	x->value = value, x->size = x->count = 1;
	x->pre = x->ch[0] = x->ch[1] = Null;
	return x;
}

void Clear(Node *x)
{
	int head, tail;
	for(head = tail = 1, queue[1] = x; head <= tail; head ++)
		if(queue[head] != Null)
		{
			stack[++ top2] = queue[head];
			queue[++ tail] = queue[head]->ch[0], queue[++ tail] = queue[head]->ch[1];
		}
}

void Update(Node *x)
{
	x->size = x->ch[0]->size + x->ch[1]->size + x->count;
}


void Rotate(Node *x, int c)
{
	Node *y = x->pre;
	y->ch[! c] = x->ch[c];
	if(x->ch[c] != Null) x->ch[c]->pre = y;
	x->pre = y->pre;
	if(y->pre != Null) y->pre->ch[y == y->pre->ch[1]] = x;
	y->pre = x, x->ch[c] = y;
	if(y == root) root = x;
	Update(y);
}

void Splay(Node *x, Node *f)
{
	while(x->pre != f)
	{
		if(x->pre->pre == f)
			Rotate(x, x->pre->ch[0] == x);
		else
		{
			Node *y = x->pre, *z = y->pre;
			if(y == z->ch[0])
			{
				if(x == y->ch[0]) Rotate(y, 1), Rotate(x, 1);
				else Rotate(x, 0), Rotate(x, 1);
			}
			else
				if(x == y->ch[1]) Rotate(y, 0), Rotate(x, 0);
				else Rotate(x, 1), Rotate(x, 0);
		}
	}
	Update(x);
}

Node *Insert(int value)
{
	Node *now = root;
	while(1)
	{
		if(value < now->value)
		{
			if(now->ch[0] != Null) now = now->ch[0];
			else break;
		}
		else if(value > now->value)
		{
			if(now->ch[1] != Null) now = now->ch[1];
			else break;
		}
		else
		{
			now->count ++;
			Splay(now, Null);
			return now;
		}
	}
	Node *p;
	if(value < now->value)
	{
		now->ch[0] = New_Node(value);
		now->ch[0]->pre = now;
		p = now->ch[0];
	}
	else
	{
		now->ch[1] = New_Node(value);
		now->ch[1]->pre = now;
		p = now->ch[1];
	}
	Splay(p, Null);
	return p;
}

void Delete(int lowline)
{
	Node *p = Insert(lowline - 1);
	Node *now = p->ch[1];
	while(now->ch[0] != Null) now = now->ch[0];
	Splay(now, Null);
	Clear(now->ch[0]), now->ch[0] = Null;
	Update(now);
}

Node *Find_Rank(int k)
{
	Node *now;
	for(now = root; ; )
	{
		int upper = now->ch[0]->size + now->count;
		int down = now->ch[0]->size + 1;
		if(down <= k && k <= upper) break;
		else
		{
			if(k < down) now = now->ch[0];
			else now = now->ch[1], k -= upper;
		}
	}
	return now;
}

int main()
{
	freopen("t.in","r",stdin);
	scanf("%d %d\n",&n,&min);
	Null = New_Node(INF), Null->size = Null->count = 0;
	root = New_Node(INF), root->ch[1] = New_Node(INF), root->ch[1]->pre = root;
	Update(root);
	int delta = 0, cnt = 0;
	for(int i = 1, k; i <= n; i ++)
	{
		char ctrl;
		scanf("%c %d\n", &ctrl, &k);
		if(ctrl == 'I')
			if(k >= min)
				Insert(k + delta), cnt ++;
		if(ctrl == 'A')
		   	delta -= k, Delete(min + delta);
		if(ctrl == 'S') 
			delta += k, Delete(min + delta);
		if(ctrl == 'F') 
		{
			if(k > root->size - 2) printf("-1\n");
			else
				printf("%d\n", Find_Rank(root->size - 2 - k + 1)->value - delta);
		}
	}
	printf("%d\n",cnt - (root->size - 2));
}
