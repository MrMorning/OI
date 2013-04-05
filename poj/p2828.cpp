/*
 * My First Treap
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define MAXN 200010

struct Node
{
	int val, priority, size;
	Node *ch[2];
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
	x->ch[0] = x->ch[1] = Null;
	x->val = val;
	x->size = 1;
	x->priority = rand();
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
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
}

void Rotate(Node *x, int t)
{
	Node *y = x->ch[t];
	x->ch[t] = y->ch[! t];
	y->ch[! t] = x;
	Update(x), Update(y);
	if(x == root)
		root = y;
}

void Insert(Node *now, int k, int val)
{
	int tmp = now->ch[0]->size + 1;
	if(k == tmp)
	{
		Node *x = New_Node(val);
		x->ch[1] = now->ch[1];
		now->ch[1] = x;
		Update(x), Update(now);
		if(x->ch[1] != Null && x->ch[1]->priority < x->priority)
			Rotate(x, 1);
		if(now->ch[1]->priority < now->priority)
			Rotate(now, 1);
	}
	else
	{
		if(k < tmp)
		{
			Insert(now->ch[0], k, val);
			if(now->ch[0]->priority < now->priority)
				Rotate(now, 0);
			else
				Update(now);
		}
		else
		{
			Insert(now->ch[1], k-tmp, val);
			if(now->ch[1]->priority < now->priority)
				Rotate(now, 1);
			else
				Update(now);
		}
	}
}

void Get_Seq(Node *x)
{
	if(x->ch[0] != Null)
		Get_Seq(x->ch[0]);
	seq[++ seqNum] = x->val;
	if(x->ch[1] != Null)
		Get_Seq(x->ch[1]);
}

/*void deb(Node *x, string fillChars)
{
	if(x->ch[0] != Null)
		deb(x->ch[0],)
}*/

int main()
{
	freopen("t.in", "r", stdin);
	srand(1);
	Null = New_Node(-1), Null->size = 0;
	while(! feof(stdin))
	{
		root = New_Node(-1);//, root->ch[1] = New_Node(-1);
		//Update(root);
		int n;
		scanf("%d\n", &n);
		for(int i = 1, a, b; i <= n; i ++)
		{
			scanf("%d %d\n", &a, &b);
			Insert(root, a+1, b);
		}
		seqNum = 0;
		Get_Seq(root);
		for(int i = 2; i <= seqNum - 1; i ++)
			printf("%d ", seq[i]);
		printf("%d\n", seq[seqNum]);
		Clear(root);
	}
}
