#include <cstdio>
#define MAXN 200010

struct Node
{
	int val, size;
	Node *pre, *ch[2];
} tree[MAXN], *queue[MAXN*2], *stack[MAXN], *root, *Null;
int top1 = 0, top2 = 0;
int seq[MAXN], seqNum;

Node *New_Node(int val)
{
	Node *x;
	if(top2) 
		x = stack[top2 --];
	else
		x = &tree[top1 ++];
	x->pre = x->ch[0] = x->ch[1] = Null;
	x->val = val;
	x->size = 1;
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

/*void Update(Node *x)
{
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
}*/

void Rotate(Node *x, int c)
{
	Node *y = x->pre;
	x->pre = y->pre;
	if(y->pre != Null)
		y->pre->ch[y == y->pre->ch[1]] = x;
	y->ch[! c] = x->ch[c];
	if(x->ch[c] != Null)
		x->ch[c]->pre = y;
	x->ch[c] = y;
	y->pre = x;
	y->size = y->ch[0]->size + y->ch[1]->size + 1;
}

void Splay(Node *x, Node *f)
{
	while(x->pre != f)
	{
		if(x->pre->pre == f)
			Rotate(x, x == x->pre->ch[0]);
		else
		{
			Node *y = x->pre, *z = y->pre;
			if(y == z->ch[0])
			{
				if(x == y->ch[0])
					Rotate(y, 1), Rotate(x, 1);
				else
					Rotate(x, 0), Rotate(x, 1);
			}
			else
			{
				if(x == y->ch[1])
					Rotate(y, 0), Rotate(x, 0);
				else
					Rotate(x, 1), Rotate(x, 0);
			}

		}
	}
	if(f == Null)
		root = x;
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
}

Node *Select(int k)
{
	Node *now = root;
	while(now->ch[0]->size + 1 != k)
	{
		int tmp = now->ch[0]->size + 1;
		if(k < tmp)
			now = now->ch[0];
		else
			now = now->ch[1], k -= tmp;
	}
	return now;
}

/*void Insert(int val, int pos)//insert a person behind pos
{
	Splay(Select(pos), Null), Splay(Select(pos+1), root);
	Node *x = New_Node(val);
	root->ch[1]->ch[0] = x, x->pre = root->ch[1];
	Splay(x, Null);
}
So slowly!!
*/

void Insert(int val, int pos)
{
	Node *x = Select(pos), *y = x->ch[1];
	Node *p = New_Node(val);
	if(y == Null)
		p->pre = x, x->ch[1] = p;
	else
	{
		while(y->ch[0] != Null)
			y = y->ch[0];
		y->ch[0] = p;
		p->pre = y;
	}
	Splay(p, Null);
}

void Get_Seq(Node *x)
{
	if(x->ch[0] != Null)
		Get_Seq(x->ch[0]);
	seq[++ seqNum] = x->val;
	if(x->ch[1] != Null)
		Get_Seq(x->ch[1]);
}

int main()
{
	freopen("t.in", "r", stdin);
	Null = New_Node(-1), Null->size = 0;
	while(! feof(stdin))
	{
		root = New_Node(-1), root->ch[1] = New_Node(-1), root->ch[1]->pre = root;
		Splay(root->ch[1], Null);
		int n;
		scanf("%d\n", &n);
		for(int i = 1, a, b; i <= n; i ++)
		{
			scanf("%d %d\n", &a, &b);
			Insert(b, a + 1);
		}
		seqNum = 0;
		Get_Seq(root);
		for(int i = 2; i <= seqNum - 2; i ++)
			printf("%d ", seq[i]);
		printf("%d\n", seq[seqNum - 1]);
		Clear(root);
	}
}
