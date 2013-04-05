#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#define PRE(x) ((x)->dirPre?(node+find((x)->dirPre-node)):NULL)
using namespace std;

const int kNMax = 150010;

int p[kNMax], realVal[kNMax];
int find(int x) { return x==p[x]?x:p[x]=find(p[x]); }
void merge(int x, int y) { 
	p[x] = y; 
}

struct Node {
	Node *ch[2], *dirPre;
	bool isRev;
	int sum, val;
	void update() {
		sum = (ch[0]?ch[0]->sum:0) + (ch[1]?ch[1]->sum:0) + val;
	}
} node[kNMax];

void reverse(Node *x) {
	swap(x->ch[0], x->ch[1]);
	x->isRev ^= 1;
}

void pushDown(Node *x) {
	if ( x->isRev ) {
		if ( x->ch[0] )
			reverse(x->ch[0]);
		if ( x->ch[1] )
			reverse(x->ch[1]);
		x->isRev = false;
	}
}

void rotate(Node *x, int dir) {
	Node *y = PRE(x);
	x->dirPre = PRE(y);
	if ( PRE(y) && y == PRE(y)->ch[y == PRE(y)->ch[1]] )
		PRE(y)->ch[y == PRE(y)->ch[1]] = x;
	y->ch[!dir] = x->ch[dir];
	if ( x->ch[dir] )
		x->ch[dir]->dirPre = y;
	x->ch[dir] = y;
	y->dirPre = x;
	y->update();
}

void splay(Node *x) {
	pushDown(x);

	while ( PRE(x) && (x == PRE(x)->ch[x == PRE(x)->ch[1]]) ) {
		Node *y = PRE(x);
		if ( !(PRE(y) && y == PRE(y)->ch[y == PRE(y)->ch[1]]) ) {
			pushDown(y); pushDown(x);
			rotate(x, x == y->ch[0]);
		}
		else {
			Node *z = PRE(y);
			pushDown(z); pushDown(y); pushDown(x);
			if ( y == z->ch[0] ) {
				if ( x == y->ch[0] )
					rotate(y, 1), rotate(x, 1);
				else
					rotate(x, 0), rotate(x, 1);
			} else {
				if ( x == y->ch[1] ) 
					rotate(y, 0), rotate(x, 0);
				else
					rotate(x, 1), rotate(x, 0);
			}
		}
	}
	x->update();
}

Node *getNeighbor(Node *x, int dir) {
	splay(x);
	if ( x->ch[dir] == NULL ) return NULL;
	pushDown(x->ch[dir]);
	x = x->ch[dir];
	while ( x->ch[!dir] ) {
		pushDown(x->ch[!dir]);
		x = x->ch[!dir];
	}
	return x;
}

Node *expose(Node *x) {
	Node *y = NULL;
	while ( x ) {
		splay(x);
		x->ch[1] = y;
		x->update();
		y = x;
		x = PRE(x);
	}
	return y;
}

Node *mem[kNMax];
int nMem;
void dfs(Node *x) {
	mem[nMem++] = x;
	pushDown(x);
	if ( x->ch[0] ) dfs(x->ch[0]);
	if ( x->ch[1] ) dfs(x->ch[1]);
}

void mergeToward(Node *x, Node *p) {
	expose(x);
	expose(p);

	splay(x);
	nMem = 0;
	dfs(x);

	splay(p);
	for ( int i = 0; i < nMem; i ++ ) {
		Node *t = mem[i];
		merge(t-node, p-node);
		p->val += t->val;
	}
	p->update();
}

void changeVal(Node *x, int newVal) {
	splay(x);
	x->val += newVal;
	x->update();
}

Node *getRoot(Node *x) {
	expose(x);
	splay(x);
	Node *cur = x;
	while ( cur->ch[0] ) {
		pushDown(cur);
		cur = cur->ch[0];
	}
	return cur;
}

Node *getLCA(Node *u, Node *v) {
	expose(u);
	return expose(v);
}

void mergeCycle(Node *u, Node *v) {
	Node *p = getLCA(u, v);
	if ( u != p )
		mergeToward(u, p);
	if ( v != p )
		mergeToward(v, p);
}

void reverseToRoot(Node *x) {
	expose(x);
	splay(x);
	reverse(x);
}

int askSum(Node *u, Node *v) {
	if ( u == v ) return u->val;
	Node *p = getLCA(u, v);
	if ( p == u ) {
		splay(p);
		return p->val + (p->ch[1]?p->ch[1]->sum:0);
	}
	splay(u);
	splay(p);
	return u->sum + p->val + (p->ch[1]?p->ch[1]->sum:0);
}

int nextInt() {
	int res = 0;
	int ch = getchar();
	while ( !isdigit(ch) )
	   ch = getchar();
	while ( isdigit(ch) ) {
		res = res*10 + (ch-'0');
		ch = getchar();
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	n = nextInt(), m = nextInt();
	for ( int i = 1; i <= n; i ++ )
		p[i] = i;
	for ( int i = 1; i <= n; i ++ ) {
		node[i].val = nextInt();
		realVal[i] = node[i].val;
		node[i].sum = node[i].val;
	}
	while ( m -- ) {
		int p, a, b;
		p = nextInt(); a = nextInt(); b = nextInt();
		if ( p == 1 ) {
			a = find(a), b = find(b);
			if ( getRoot(node+a) == getRoot(node+b) )
				mergeCycle(node+a, node+b);
			else {
				reverseToRoot(node+b);
				expose(node+b);
				splay(node+b);
				(node+b)->dirPre = node+a;
			}
		} else if ( p == 2 ) {
			int delta = b - realVal[a];
			realVal[a] = b;
			a = find(a);
			changeVal(node+a,delta);
		} else {
			a = find(a), b = find(b);
			if ( getRoot(node+a) != getRoot(node+b) )
				puts("-1");
			else
				printf("%d\n", askSum(node+a, node+b));
		}
	}
}
