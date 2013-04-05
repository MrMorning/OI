#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 1000010;
struct Node{
	Node *ch[2];
	int dist, size;
	ll key;
} node[N_MAX], *null;

struct Segment {
	int l, r;
	Node *root;
} seg[N_MAX];
int seg_num;

Node *alloc(ll key, int dist) {
	static int free_pos = 0;
	Node *x = node + free_pos ++;
	x->key = key, x->dist = dist;
	x->ch[0] = x->ch[1] = null;
	x->size = 1;
	return x;
}

Node *merge(Node *x, Node *y) {
	if (x == null) return y;
	if (y == null) return x;
	if (x->key < y->key)
		swap(x, y);
	x->ch[1] = merge(x->ch[1], y);
	if (x->ch[1]->dist > x->ch[0]->dist)
		swap(x->ch[1], x->ch[0]);
	x->dist = x->ch[1]->dist + 1;
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
	return x;
}

void insert(Node *&x, ll key) {
	Node *y = alloc(key, 0);
	x = merge(x, y);
}

void delete_max(Node *&x) {
	x = merge(x->ch[0], x->ch[1]);
}

int n;
ll a[N_MAX];

int main() {
	freopen("t.in", "r", stdin);
	null = alloc(0, -1);
	null->size = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) {
		scanf("%lld", &a[i]);
		a[i] -= i;
	}
	for (int i = 1; i <= n; i ++) {
		seg_num ++;
		seg[seg_num].root = alloc(a[i], 0);
		seg[seg_num].l = seg[seg_num].r = i;

		while (seg_num > 1 && seg[seg_num - 1].root->key >= seg[seg_num].root->key) {
			Segment &last = seg[seg_num], 
					&prev = seg[seg_num - 1];
			prev.r = last.r;
			prev.root = merge(prev.root, last.root);
			seg_num --;
			while (prev.root->size > (prev.r - prev.l + 2) / 2)
				delete_max(prev.root);
		}
	}
	ll res = 0;
	for (int i = 1; i <= seg_num; i ++) {
		Segment &it = seg[i];
		for (int j = it.l; j <= it.r; j ++)
			res += abs(it.root->key - a[j]);
	}
	printf("%lld\n", res);
}
