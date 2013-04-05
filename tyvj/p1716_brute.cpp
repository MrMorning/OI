#include <cstdio>

const int offset[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
const int N_MAX = 1000100;

struct Node {
	Node *ch[4];
	int x1, y1, sz; //size = 2^sz
	int sum, tag;
} node[N_MAX], *root;
int free_pos = 0;

Node *alloc(int x1, int y1, int sz) {
	Node *x = node + free_pos ++;
	x->x1 = x1, x->y1 = y1, x->sz = sz;
	x->sum = 0, x->tag = 0;
	x->ch[0] = x->ch[1] = x->ch[2] = x->ch[3] = NULL;
	return x;
}

Node *deepin(Node *x, int c) {
	if ( x->ch[c] == NULL )
		x->ch[c] = alloc(x->x1 + offset[c][0] * (1 << x->sz) / 2,
				x->y1 + offset[c][1] * (1 << x->sz) / 2, x->sz - 1);
	return x->ch[c];
}

void update(Node *x) {
	x->sum = 0;
	for ( int t = 0; t < 4; t ++ )
		x->sum += x->ch[t]->sum;
}

void mark(Node *x, int val) {
	x->sum += (1 << x->sz) * (1 << x->sz) * val;
	x->tag += val;
}

void push_down(Node *x) {
	if ( x->tag ) {
		for ( int t = 0; t < 4; t ++ )
			mark(deepin(x, t), x->tag);
		x->tag = 0;
	}
}

int calc_sum(Node *cur, int x1, int y1, int x2, int y2) {
	if ( x1 <= cur->x1 && cur->x1 + (1 << cur->sz) - 1 <= x2
			&& y1 <= cur->y1 && cur->y1 + (1 << cur->sz) - 1 <= y2 )
		return cur->sum;
	if ( x2 < cur->x1 || cur->x1 + (1 << cur->sz) - 1 < x1
			|| y2 < cur->y1 || cur->y1 + (1 << cur->sz) - 1 < y1 )
		return 0;
	push_down(cur);
	int res = 0;
	for ( int c = 0; c < 4; c ++ )
		res += calc_sum(deepin(cur, c), x1, y1, x2, y2);
	update(cur);
	return res;
}

void add(Node *cur, int x1, int y1, int x2, int y2, int val) {
	if ( x1 <= cur->x1 && cur->x1 + (1 << cur->sz) - 1 <= x2
			&& y1 <= cur->y1 && cur->y1 + (1 << cur->sz) - 1 <= y2 ) {
		mark(cur, val);
		return;
	}
	if ( x2 < cur->x1 || cur->x1 + (1 << cur->sz) - 1 < x1
			|| y2 < cur->y1 || cur->y1 + (1 << cur->sz) - 1 < y1 )
		return;
	push_down(cur);
	for ( int c = 0; c < 4; c ++ )
		add(deepin(cur, c), x1, y1, x2, y2, val);
	update(cur);
}

int main() {
	freopen("t.in", "r", stdin);
	root = alloc(1, 1, 7);
	int n, m;
	static char cmd[10];
	scanf("X %d %d", &n, &m);
	while ( scanf("%s", cmd) != EOF ) {
		if ( cmd[0] != 'L' && cmd[0] != 'k' )
			break;
		if ( cmd[0] == 'L' ) {
			int a, b, c, d, delta;
			scanf("%d%d%d%d%d", &a, &b, &c, &d, &delta);
			add(root, a, b, c, d, delta);
		} else {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			int res = calc_sum(root, a, b, c, d);
			printf("%d\n", res);
		}
	}
}
