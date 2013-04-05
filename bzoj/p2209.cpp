#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

const int BUFFER_LEN = 1024 * 1024 * 5;
static char buffer[BUFFER_LEN];
char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
{ \
	ptr ++; \
	if (ptr == buf_end) \
	{ \
		ptr = buffer; \
		buf_end = buffer + fread(buffer, 1, BUFFER_LEN, stdin); \
	} \
}
#define READ_INT(_x_) \
{ \
	while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
	PTR_NEXT(); \
	bool _nega_ = false; \
	if (*ptr == '-') \
	{ \
		_nega_ = true; \
		PTR_NEXT(); \
	} \
	int register _n_ = 0; \
	while (*ptr >= '0' && *ptr <= '9') \
	{ \
		_n_ = _n_ * 10 + *ptr - '0'; \
		PTR_NEXT(); \
	} \
	if (_nega_) \
	_n_ = - _n_; \
	(_x_) = (_n_); \
}

const int N_MAX = 100010;
const int INFINITY = 0x3f3f3f3f;

struct Node
{
	Node *pre, *ch[2];
	int lmax, lmin, sum, rmin, rmax, size, val;
	bool is_inverse, is_turned;
};

Node node_pool[N_MAX], *root, *null;
int free_pos;

int val[N_MAX];

Node *alloc_node(int val)
{
	Node *x = &node_pool[free_pos ++];
	x->pre = x->ch[0] = x->ch[1] = null;
	x->is_inverse = x->is_turned = false;
	x->size = 1, x->sum = x->val = val;
	if(val > 0)
		x->lmax = x->rmax = val, x->lmin = x->rmin = 0;
	else
		x->lmax = x->rmax = 0, x->lmin = x->rmin = val;
	return x;
}

void update(Node *x)
{
	Node *lch = x->ch[0],
		 *rch = x->ch[1];
	x->lmax = max(0, max(lch->sum + x->val + max(0, rch->lmax), lch->lmax));
	x->lmin = min(0, min(lch->sum + x->val + min(0, rch->lmin), lch->lmin));
	x->sum = lch->sum + x->val + rch->sum;
	x->size = lch->size + rch->size + 1;
	x->rmax = max(0, max(rch->sum + x->val + max(0, lch->rmax), rch->rmax));
	x->rmin = min(0, min(rch->sum + x->val + min(0, lch->rmin), rch->rmin));
}

void make_inverse(Node *x)
{
	swap(x->lmax, x->lmin);
	swap(x->rmax, x->rmin);
	x->lmax *= -1, x->rmax *= -1, x->lmin *= -1, x->rmin *= -1;
	x->sum *= -1, x->val *= -1;
	x->is_inverse ^= 1;
}

void make_turned(Node *x)
{
	swap(x->lmax, x->rmax);
	swap(x->lmin, x->rmin);
	swap(x->ch[0], x->ch[1]);
	x->is_turned ^= 1;
}

void push_down(Node *x)
{
	if(x->is_inverse)
	{
		make_inverse(x->ch[0]);
		make_inverse(x->ch[1]);
		x->is_inverse = 0;
	}
	if(x->is_turned)
	{
		make_turned(x->ch[0]);
		make_turned(x->ch[1]);
		x->is_turned = 0;
	}
}

void rotate(Node *x, int c)
{
	Node *y = x->pre;
	x->pre = y->pre;
	if(y->pre != null)
		y->pre->ch[y == y->pre->ch[1]] = x;
	y->ch[! c] = x->ch[c];
	if(x->ch[c] != null)
		x->ch[c]->pre = y;
	y->pre = x, x->ch[c] = y;
	update(y);
	if(y == root)
		root = x;
}

void splay(Node *x, Node *fa)
{
	for(; x->pre != fa; )
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
	update(x);
}

Node *make_tree(int l, int r, Node *fa)
{
	if(l > r)
		return null;
	int mid = (l + r) / 2;
	Node *x = alloc_node(val[mid]);
	if(l != r)
	{
		x->ch[0] = make_tree(l, mid - 1, x);
		x->ch[1] = make_tree(mid + 1, r, x);
		update(x);
	}
	x->pre = fa;
	return x;
}

void select(int k, Node *fa)
{
	Node *now = root;
	while(1)
	{
		push_down(now);
		int tmp = now->ch[0]->size + 1;
		if(tmp == k)
			break;
		else if(k < tmp)
			now = now->ch[0];
		else
			k -= tmp, now = now->ch[1];
	}
	splay(now, fa);
}

int ask(int l, int r)
{
	l ++, r ++;
	select(l - 1, null);
	select(r + 1, root);
	int a = root->ch[1]->ch[0]->lmin,
		b = root->ch[1]->ch[0]->rmax;
	a = -a;
	a = a == 0 ? 0 : (a - 1) / 2 + 1;
	b = b == 0 ? 0 : (b - 1) / 2 + 1;
	return a + b;
}

void reverse(int l, int r)
{
	l ++, r ++;
	select(l - 1, null);
	select(r + 1, root);
	make_inverse(root->ch[1]->ch[0]);
	splay(root->ch[1], null);
}

void turn(int l, int r)
{
	l ++, r ++;
	select(l - 1, null);
	select(r + 1, root);
	make_turned(root->ch[1]->ch[0]);	
	splay(root->ch[1], null);
}

void init(int n)
{
	null = alloc_node(0);
	null->size = 0;
	null->lmax = null->rmax = -INFINITY;
	null->lmin = null->rmin = INFINITY;

	root = alloc_node(0);
	root->ch[1] = alloc_node(0);
	root->ch[1]->pre = root;
	root->ch[1]->ch[0] = make_tree(1, n, root->ch[1]);
	splay(root->ch[1], null);
}

int main()
{
	freopen("t.in", "r", stdin);
	//	freopen("t.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	static char str[N_MAX];
	scanf("%s", str);
	for(int i = 1; i <= n; i ++)
		val[i] = str[i - 1] == '(' ? 1 : -1;
	init(n);
	while(m --)
	{
		int cmd, l, r;
		READ_INT(cmd); READ_INT(l); READ_INT(r);
		//scanf("%d %d %d\n", &cmd, &l, &r);
		if(cmd == 0)
			printf("%d\n", ask(l, r));
		else if(cmd == 1)
			reverse(l, r);
		else
			turn(l, r);
	}
}
