#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000, kMaxR = 1 << 17;
int n, m, x[kMaxN + 1];

struct Mark {
	int v;
	Mark() : v(0) {}
	Mark(int v_) : v(v_) {}
	void clear() { v = 0; }
} mark[kMaxR << 1];

Mark operator * (const Mark &a, const Mark &b) {
	return Mark(a.v + b.v);
}

struct Node {
	int lb, rb, len, lv, rv, v;
	Node() { lb = rb = len = lv = rv = v = 0; }
	void clear() { lb = rb = len = lv = rv = v = 0; }
} node[kMaxR << 1];

Node operator + (const Node &a, const Node &b) {
	Node res;
	res.lb = a.lb;
	res.rb = b.rb;
	res.len = a.len + b.len;
	res.lv = a.lv;
	res.rv = b.rv;
	res.v = max(a.v, b.v);
	if (a.rb < b.lb) res.v = max(res.v, a.rv + b.lv);
	if (a.lv == a.len && a.rb < b.lb) res.lv += b.lv;
	if (b.rv == b.len && a.rb < b.lb) res.rv += a.rv;
	return res;
}

Node operator * (const Node &a, const Mark &b) {
	Node res = a;
	res.lb += b.v;
	res.rb += b.v;
	return res;
}

#define L(x) ((x) << 1)
#define R(x) ((x) << 1 | 1)

int h, sz;

void AddNewChange(int x, const Mark &p) {
	node[x] = node[x] * p;
	mark[x] = mark[x] * p;
}

void PushToSon(int x) {
	AddNewChange(L(x), mark[x]);
	AddNewChange(R(x), mark[x]);
	mark[x].clear();
}

void PushToLeaf(int x) {
	for (int i = h; i; -- i)
		PushToSon(x >> i);
}

void ChangeOnRange(int l, int r, const Mark &p) {
	PushToLeaf(l += sz - 1);
	PushToLeaf(r += sz + 1);
	for (int ll = l, rr = r; ll ^ rr ^ 1; ll >>= 1, rr >>= 1) {
		if (~ll & 1) AddNewChange(ll ^ 1, p);
		if (rr & 1) AddNewChange(rr ^ 1, p);
	}
	for (int i = 1; i <= h; ++ i) {
		l >>= 1, node[l] = node[L(l)] + node[R(l)];
		r >>= 1, node[r] = node[L(r)] + node[R(r)];
	}
}

Node AskOnRange(int l, int r) {
	PushToLeaf(l += sz - 1);
	PushToLeaf(r += sz + 1);
	Node la, ra;
	for ( ; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) la = la + node[l ^ 1];
		if (r & 1) ra = node[r ^ 1] + ra;
	}
	return (la + ra);
}

void Init() {
	int t = (n & (n + 1)) == 0 ? n + 1 : n;
	h = 0;
	while (t >>= 1) ++ h;
	sz = 1 << (h + 1);
	for (int i = kMaxR << 1; i; -- i) {
		node[i - 1].clear();
		mark[i - 1].clear();
	}
	for (int i = 1; i <= n; ++ i) {
		Node &r = node[i + sz];
		r.lb = r.rb = x[i];
		r.len = 1;
		r.lv = r.rv = r.v = 1;
	}
	for (int i = sz - 1; i; -- i)
		node[i] = node[L(i)] + node[R(i)];
}

int casen;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &casen);
	for (int cas = 0; cas ++ < casen; ) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++ i) scanf("%d", &x[i]);
		Init();
		printf("Case #%d:\n", cas);
		char cmd[2];
		int l, r, d;
		while (m --) {
			scanf("%s%d%d", cmd, &l, &r);
			if (l > r) swap(l, r);
			if (cmd[0] == 'q') printf("%d\n", AskOnRange(l, r).v);
			else {
				scanf("%d", &d);
				ChangeOnRange(l, r, Mark(d));
			}
		}
	}
	return 0;
}
