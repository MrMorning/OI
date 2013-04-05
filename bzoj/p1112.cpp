#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N_MAX = 100010;
const int inf = 1111111;
struct Node {
	Node *ch[2], *pre;
	int sz, key;
	ll sum;
}  node[N_MAX], *root, *null;
int n, h[N_MAX];

Node *alloc(int key) {
	static int free_pos = 0;
	Node *x = node + free_pos ++;
	x->key = x->sum = key;
	x->sz = 1;
	x->ch[0] = x->ch[1] = x->pre = null;
	return x;
}

void update(Node *x) {
	x->sz = x->ch[0]->sz + x->ch[1]->sz + 1;
	x->sum = x->ch[0]->sum + x->ch[1]->sum + x->key;
}

void rotate(Node *x, int dir) {
	Node *y = x->pre;
	x->pre = y->pre;
	if (y->pre != null)
		y->pre->ch[y == y->pre->ch[1]] = x;
	y->ch[!dir] = x->ch[dir];
	if (x->ch[dir] != null)
		x->ch[dir]->pre = y;
	y->pre = x, x->ch[dir] = y;
	if (y == root)
		root = x;
	update(y);
}

void splay(Node *x, Node *p) {
	while (x->pre != p) {
		if (x->pre->pre == p)
			rotate(x, x == x->pre->ch[0]);
		else {
			Node *y = x->pre, *z = y->pre;
			if (y == z->ch[0]) {
				if (x == y->ch[0])
					rotate(y, 1), rotate(x, 1);
				else
					rotate(x, 0), rotate(x, 1);
			}
			else {
				if (x == y->ch[1])
					rotate(y, 0), rotate(x, 0);
				else
					rotate(x, 1), rotate(x, 0);
			}
		}
	}
	update(x); 
}

void insert(int key) {
	Node *cur = root;
	Node *p;
	while (cur != null) {
		p = cur;
		cur = cur->ch[key > cur->key];
	}
	Node *x = alloc(key);
	p->ch[key > p->key] = x;
	x->pre = p;
	splay(x, null);
}

Node *search(int key) {
	Node *cur = root;
	while (cur->key != key)
		cur = cur->ch[key > cur->key];
	splay(cur, null);
	return cur;
}

Node *get_neighbor(Node *x, int c) {
	splay(x, null);
	Node *t = x->ch[c];
	while (t->ch[!c] != null)
		t = t->ch[!c];
	return t;
}

void remove(int key) {
	Node *x = search(key);
	Node *prec = get_neighbor(x, 0),
		 *succ = get_neighbor(x, 1);
	splay(prec, null);
	splay(succ, prec);
	succ->ch[0] = null;
	splay(succ, null);
}

Node *get_rank(int k) {
	k ++;
	Node *cur = root;
	while (1) {
		int tmp = cur->ch[0]->sz + 1;
		if (tmp == k)
			return cur;
		if (k < tmp)
			cur = cur->ch[0];
		else
			cur = cur->ch[1], k -= tmp;
	}
}

int main() {
	freopen("t.in", "r", stdin);

	null = alloc(0);
	null->sz = 0;
	root = alloc(-inf);
	root->ch[1] = alloc(inf), root->ch[1]->pre = root;
	splay(root->ch[1], null);

	int k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &h[i]);
	ll ans = 0x3f3f3f3f3f3f3f3fLL;
	for (int i = 1; i < k; i ++) {
		insert(h[i]);
	}
	for (int i = k; i <= n; i ++) {
		insert(h[i]);
		Node *x = get_rank(k / 2 + 1);
		splay(x, null);
		ll lsum = (ll)(x->ch[0]->sz - 1) * x->key - (x->ch[0]->sum + inf),
		   rsum = -(ll)(x->ch[1]->sz - 1) * x->key + (x->ch[1]->sum - inf);
		ans = min(ans, lsum + rsum);
		remove(h[i - k + 1]);
	}
	printf("%lld\n", ans);
}
