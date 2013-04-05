#include <cstdio>
#include <cstring>
typedef unsigned long long bignum_t;

#define INLINE __attribute__((always_inline))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

const int N_MAX = 100010;
bignum_t FACTORIAL_OF_ALPHA[N_MAX];

struct Info
{
	bignum_t hash;
	int len;
	Info(bignum_t _hash = 0, int _len = 0): hash(_hash), len(_len){};
};
inline Info operator+ (const Info &Ia, const Info &Ib)
{
	Info ret_I;
	ret_I.hash  = (Ia.hash * FACTORIAL_OF_ALPHA[Ib.len] + Ib.hash);
	ret_I.len = Ia.len + Ib.len;
	return ret_I;
}
class Splay
{
	public:
		struct Node
		{
			Node *ch[2], *pre;
			Info acc_info, org_info;
			int size;
		};

		static Node node_pool[N_MAX], *null;
		static bool has_init_null;
		static int node_idx;
		Node *root;

		Splay();
		static Node *node_alloc(Info info) INLINE;
		static void update(Node *x) INLINE;
		void rotate(Node *x, int c) INLINE;
		void splay(Node *x, Node *f) INLINE;
		void select(int k, Node *f) INLINE;
		void insert(int k, Node *x) INLINE;
		Node *mktree(int l, int r, Node *f, int *a);

		void change(int k, const Info &info) INLINE;
		Info ask(int l, int r);
		void build(int *a, int n);
		static void print(Node *x, int d);
};

Splay::Node Splay::node_pool[N_MAX], *Splay::null;
bool Splay::has_init_null;
int Splay::node_idx;

Splay::Splay()
{
	if(! has_init_null)
	{
		null = node_alloc(Info(0, 0));
		null->size = 0;
	}
}

Splay::Node *Splay::node_alloc(Info info)
{
	Node *x = &node_pool[node_idx ++];
	x->acc_info = x->org_info = info;
	x->ch[0] = x->ch[1] = x->pre = null;
	x->size = 1;
	return x;
}

void Splay::update(Node *x)
{
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
	x->acc_info = x->ch[0]->acc_info + x->org_info + x->ch[1]->acc_info;
}

void Splay::rotate(Node *x, int c)
{
	Node *p = x->pre;
	x->pre = p->pre;
	if(p->pre != null)
		p->pre->ch[p == p->pre->ch[1]] = x;
	p->ch[! c] = x->ch[c];
	if(x->ch[c] != null)
		x->ch[c]->pre = p;
	x->ch[c] = p, p->pre = x;
	if(p == root)
		root = x;
	update(p);
}

void Splay::splay(Node *x, Node *f)
{
	while(x->pre != f)
	{
		if(x->pre->pre == f)
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

void Splay::select(int k, Node *f)
{
	Node *u = root;
	while(1)
	{
		int tmp = u->ch[0]->size + 1;
		if(tmp == k)
			break;
		else if(k < tmp)
			u = u->ch[0];
		else
			u = u->ch[1], k -= tmp;
	}
	splay(u, f);
}

void Splay::insert(int k, Node *x)
{
	Node *u = root;
	while(1)
	{
		int tmp = u->ch[0]->size + 1;
		if(k == tmp)
			break;
		if(k < tmp)
			u = u->ch[0];
		else
			u = u->ch[1], k -= tmp;
	}
	x->ch[1] = u->ch[1];
	if(u->ch[1] != null)
		u->ch[1]->pre = x;
	u->ch[1] = x, x->pre = u;
	splay(x, null);
}

Splay::Node *Splay::mktree(int l, int r, Node *f, int *a)
{
	if(l > r)
		return null;
	int mid = (l + r) / 2;
	Node *x = node_alloc(Info(a[mid], 1));
	x->pre = f;
	if(l < r)
	{
		x->ch[0] = mktree(l, mid - 1, x, a);
		x->ch[1] = mktree(mid + 1, r, x, a);
		update(x);
	}
	return x;
}

void Splay::change(int k, const Info &info)
{
	k ++;
	select(k - 1, null);
	select(k + 1, root);
	Node *x = root->ch[1]->ch[0];
	x->acc_info = x->org_info = info; 
	splay(x, null);
}

Info Splay::ask(int l, int r)
{
	l ++, r ++;
	select(l - 1, null);
	select(r + 1, root);
	Node *x = root->ch[1]->ch[0];
	return x->acc_info;
}

void Splay::build(int *a, int n)
{
	root = node_alloc(Info(0, 0));
	root->ch[1] = node_alloc(Info(0, 0));
	root->ch[1]->pre = root;
	root->ch[1]->ch[0] = mktree(1, n, null, a);
	root->ch[1]->ch[0]->pre = root->ch[1];
	splay(root->ch[1]->ch[0], null);
}

Splay T;

int bin_search(int a, int b)
{
	int n = T.root->size - 2;
	int l = 0, r = n - MAX(a, b) + 2, mid = (l + r) / 2;
	while(l + 1 < r)
	{
		if(T.ask(a, a + mid - 1).hash == T.ask(b, b + mid - 1).hash)
			l = mid;
		else
			r = mid;
		mid = (l + r) / 2;
	}
	return l;
}

int main()
{
	freopen("t.in", "r", stdin);

	FACTORIAL_OF_ALPHA[0] = 1;
	for(int i = 1; i < N_MAX; i ++)
		FACTORIAL_OF_ALPHA[i] = 26 * FACTORIAL_OF_ALPHA[i - 1];

	static char init_str[N_MAX];
	static int a[N_MAX];
	scanf("%s", init_str);
	for(int i = 1; i <= (int)strlen(init_str); i ++)
		a[i] = init_str[i - 1] - 'a';
	T.build(a, strlen(init_str));

	int n_cmd;
	char cmd[5];
	scanf("%d", &n_cmd);
	while(n_cmd --)
	{
		scanf("%s", cmd);
		if(cmd[0] == 'Q')
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if(T.ask(a, a).hash != T.ask(b, b).hash)
				printf("0\n");
			else
			{
				int n = T.root->size - 2;
				int len = n - MAX(a, b) + 1;
				if(a == b)
					printf("%d\n", len);
				else
					if(T.ask(a, a + len - 1).hash == T.ask(b, b + len - 1).hash)
						printf("%d\n", len);
					else
						printf("%d\n", bin_search(a, b));
			}
		}
		else if(cmd[0] == 'R')
		{
			int x;
			char a;
			scanf("%d %c", &x, &a);
			T.change(x, Info(a - 'a', 1));
		}
		else
		{
			int x;
			char a;
			scanf("%d %c", &x, &a);
			T.insert(x + 1, Splay::node_alloc(Info(a - 'a', 1)));
		}
	}	
}
