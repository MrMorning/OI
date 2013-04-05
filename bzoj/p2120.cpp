#include <cstdio>
#include <cstdlib>

#define INLINE __attribute__((always_inline))
const int N_MAX = 10010, LOG_N_MAX = 30;
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
#define READ_STR(_s_) \
{ \
	while ((*ptr < 'A' || *ptr > 'Z') && (*ptr < 'a' || *ptr > 'z')) \
	PTR_NEXT(); \
	char *_p_ = (_s_); \
	while ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')) \
	{ \
		*(_p_ ++) = *ptr; \
		PTR_NEXT(); \
	} \
	*_p_ = 0; \
}
class Treap
{
	public:
		struct Node
		{
			int key, fix;
			int size, cnt;
			Node *ch[2];
		};
		static Node node_pool[N_MAX * LOG_N_MAX], *recycle[N_MAX * LOG_N_MAX], *null;
		static int node_idx, recycle_idx;
		static bool has_init_null;
		Node *root;

		Treap();
		static Node *node_alloc(int key) INLINE;
		static void node_delete(Node *&x) INLINE;
		static void update(Node *x) INLINE;
		static void rotate(Node *&x, int c) INLINE;
		static Node *&find(Node *&now, int key);
		static void insert(Node *&now, Node *x);
		static void remove(Node *&now);
		static void remove(Node *&now, int key);
		static int ask_below(Node *now, int upperlim);

		void insert(int key) INLINE;
		void remove(int key) INLINE;
		int ask_below(int upperlim) INLINE;
};

namespace sgt
{
	struct Node
	{
		int l, r;
		Treap T;
	};
	Node node[N_MAX * 8];

	void build(int i, int l, int r);
	void change(int i, int pos, int pre_val, int new_val);
	int ask(int i, int l, int r, int upperlim);
}

Treap::Node Treap::node_pool[N_MAX * LOG_N_MAX], *Treap::recycle[N_MAX * LOG_N_MAX], *Treap::null;
int Treap::node_idx, Treap::recycle_idx;
bool Treap::has_init_null;

int pre_same[N_MAX], clr[N_MAX], hash[1000001];

Treap::Treap()
{
	if(! has_init_null)
	{
		null = node_alloc(0);
		null->size = null->cnt = 0;
		has_init_null = true;
	}
	root = null;
}

Treap::Node *Treap::node_alloc(int key)
{
	Node *x;
	if(recycle_idx)
		x = recycle[-- recycle_idx];
	else
		x = &node_pool[node_idx ++];
	x->key = key, x->fix = rand() * rand(), x->cnt = x->size = 1;
	x->ch[0] = null, x->ch[1] = null;
	return x;
}

void Treap::node_delete(Node *&x)
{
	recycle[recycle_idx ++] = x;
	x = null;
}

void Treap::update(Node *x)
{
	x->size = x->ch[0]->size + x->ch[1]->size + x->cnt;
}

void Treap::rotate(Node *&x, int c)
{
	Node *y = x->ch[c];
	x->ch[c] = y->ch[! c];
	y->ch[! c] = x;
	update(x);
	update(y);
	x = y;
}

Treap::Node *&Treap::find(Node *&now, int key)
{
	if(now->key == key)
		return now;
	return find(now->ch[now->key < key], key);
}

void Treap::insert(Node *&now, Node *x)
{
	if(now == null)
	{
		now = x;
		return;
	}
	if(now->key == x->key)
	{
		now->cnt ++;
		update(now);
		return;
	}
	int t = x->key > now->key;
	insert(now->ch[t], x);
	if(now->ch[t]->fix < now->fix)
		rotate(now, t);
	else
		update(now);
}

void Treap::remove(Node *&now)
{
	if(now->ch[0] == null && now->ch[1] == null)
	{
		node_delete(now);
		return;
	}
	int t;
	if(now->ch[0] != null)
	{
		t = 0;
		if(now->ch[1] != null)
			t = now->ch[1]->fix < now->ch[0]->fix;
	}
	else
		t = 1;
	rotate(now, t);
	remove(now->ch[! t]);
	if(now->ch[! t] != null && now->ch[! t]->fix < now->fix)
		rotate(now, ! t);
	else
		update(now);
}

void Treap::remove(Node *&now, int key)
{
	if(now->key == key)
	{
		if(now->cnt > 1)
			now->cnt --;
		else
			remove(now);
		if(now != null)
			update(now);
		return;
	}
	int t = now->key < key;
	remove(now->ch[t], key);
	if(now->ch[t] != null && now->ch[t]->fix < now->fix)
		rotate(now, t);
	else
		update(now);
}

int Treap::ask_below(Node *now, int upperlim)
{
	if(now == null)
		return 0;
	if(now->key >= upperlim)
		return ask_below(now->ch[0], upperlim);
	else
		return now->ch[0]->size + now->cnt + ask_below(now->ch[1], upperlim);
}

void Treap::insert(int key)
{
	insert(root, node_alloc(key));
}

void Treap::remove(int key)
{
	remove(root, key);
}

int Treap::ask_below(int upperlim)
{
	return ask_below(root, upperlim);
}

void sgt::build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	for(int j = l; j <= r; j ++)
		node[i].T.insert(pre_same[j]);
	if(l == r)
		return;
	build(i * 2, l, (l + r) / 2);
	build(i * 2 + 1, (l + r) / 2 + 1, r);
}

void sgt::change(int i, int pos, int pre_val, int new_val)
{
	if(node[i].l > pos || node[i].r < pos)
		return;
	node[i].T.remove(pre_val);
	node[i].T.insert(new_val);
	change(i * 2, pos, pre_val, new_val);
	change(i * 2 + 1, pos, pre_val, new_val);
}

int sgt::ask(int i, int l, int r, int upperlim)
{
	if(node[i].l > r || node[i].r < l)
		return 0;
	if(l <= node[i].l && node[i].r <= r)
		return node[i].T.ask_below(upperlim);
	return ask(i * 2, l, r, upperlim) + ask(i * 2 + 1, l, r, upperlim);
}

int main()
{
	int n, m;
	READ_INT(n);
	READ_INT(m);
	for(int i = 1; i <= n; i ++)
	{
		READ_INT(clr[i]);
		pre_same[i] = hash[clr[i]];
		hash[clr[i]] = i;
	}
	sgt::build(1, 1, n);
	while(m --)
	{
		char cmd[10];
		int a, b;
		READ_STR(cmd);
		READ_INT(a);
		READ_INT(b);
		if(cmd[0] == 'Q')
			printf("%d\n", sgt::ask(1, a, b, a));
		else
		{
			int i;
			for(int i = a + 1; i <= n; i ++)
				if(clr[i] == clr[a])
				{
					sgt::change(1, i, pre_same[i], pre_same[a]);
					pre_same[i] = pre_same[a];
					break;
				}

			clr[a] = b;
			int tmp = pre_same[a];
			for(i = a - 1; i >= 1; i --)
				if(clr[i] == clr[a])
				{
					pre_same[a] = i;
					break;
				}
			if(i == 0)
				pre_same[a] = 0;
			sgt::change(1, a, tmp, pre_same[a]);

			for(i = a + 1; i <= n; i ++)
				if(clr[i] == clr[a])
				{
					sgt::change(1, i, pre_same[i], a);
					pre_same[i] = a;
					break;
				}
		}
	}
}
