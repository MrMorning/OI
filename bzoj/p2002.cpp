#include <cstdio>
const int N_MAX = 200010;
struct Node {
	Node *pre, *ch[2];
	int sz;
	void update() {
		sz = ch[0]->sz + ch[1]->sz + 1;
	}
} node[N_MAX], *null;
int node_cnt = 0;

Node *alloc() {
	Node *x = node + node_cnt ++;
	x->pre = x->ch[0] = x->ch[1] = null;
	x->sz = 1;
	return x;
}

void rotate(Node *x, int c) {
	Node *y = x->pre;
	x->pre = y->pre;
	if ( y == y->pre->ch[y == y->pre->ch[1]] )
		y->pre->ch[y == y->pre->ch[1]] = x;
	y->ch[!c] = x->ch[c];
	if ( x->ch[c] != null )
		x->ch[c]->pre = y;
	y->pre = x, x->ch[c] = y;
	y->update();
}

void splay(Node *x) {
	while ( x == x->pre->ch[x == x->pre->ch[1]] ) {
		Node *y = x->pre, *z = y->pre;
		if ( y != z->ch[y == z->ch[1]] )
			rotate(x, x == y->ch[0]);
		else {
			if ( y == z->ch[0] ) {
				if ( x == y->ch[0] ) rotate(y, 1);
				else rotate(x, 0);
				rotate(x, 1);
			} else {
				if ( x == y->ch[1] ) rotate(y, 0);
				else rotate(x, 1);
				rotate(x, 0);
			}
		}
	}
	x->update();
}

Node *expose(Node *x) {
	Node *y = null;
	for ( ; x != null; y = x, x = x->pre ) {
		splay(x);
		x->ch[1] = y;
		x->update();
	}
	return y;
}

void cut(Node *x) {
	expose(x);
	splay(x);
	x->ch[0]->pre = x->pre;
	x->pre = null;
	x->ch[0] = null;
	x->update();
}

void join(Node *x, Node *y) {
	expose(y);
	splay(y);
	x->pre = y;
	expose(x);
}
int n, m;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	null = alloc();
	null->sz = 0;
	for ( int i = 1; i <= n; i ++ )
		alloc();
	for ( int i = 1; i <= n; i ++ ) {
		int k;
		scanf("%d", &k);
		if ( k + i <= n )
			join(node + i, node + k + i);
	}
	scanf("%d", &m);
	while ( m -- ) {
		int i, j;
		scanf("%d%d", &i, &j);
		j ++;
		Node *x = node + j;
		if ( i == 1 ) {
			expose(x);
			splay(x);
			printf("%d\n", x->ch[0]->sz + 1);
		} else {
			int k;
			scanf("%d", &k);
			cut(x);
			if ( j + k <= n )
				join(x, node + j + k);
		}
	}
}
