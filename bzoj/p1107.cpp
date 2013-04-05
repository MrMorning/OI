#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
const int N_MAX = 100010;

struct Node {
	int l, r;
	int maxval;
	int tag;
} node[N_MAX * 4];
void update(int i) {
	node[i].maxval = max(node[i * 2].maxval, node[i * 2 + 1].maxval);
}
void mark(int i, int tag) {
	node[i].maxval += tag;
	node[i].tag += tag;
}
void push_down(int i) {
	if (node[i].tag) {
		mark(i * 2, node[i].tag);
		mark(i * 2 + 1, node[i].tag);
		node[i].tag = 0;
	}
}
void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r, node[i].tag = 0;
	if (l == r)
		node[i].maxval = 0;
	else {
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
		update(i);
	}
}

int get_val(int p) {
	int cur = 1;
	while (1) {
		if (node[cur].l == node[cur].r)
			break;
		push_down(cur);
		int mid = (node[cur].l + node[cur].r) / 2;
		if (p <= mid)
			cur = cur * 2;
		else
			cur = cur * 2 + 1;
	}
	int res = node[cur].maxval;
	cur >>= 1;
	while (cur) {
		update(cur);
		cur >>= 1;
	}
	return res;
}

int find_left(int bound) {
	int cur = 1;
	while (1) {
		if (node[cur].l == node[cur].r)
			break;
		push_down(cur);
		if (node[cur * 2].maxval >= bound)
			cur = cur * 2;
		else
			cur = cur * 2 + 1;
	}
	int res = node[cur].l;
	cur >>= 1;
	while (cur) {
		update(cur);
		cur >>= 1;
	}
	return res;
}

void seg_plus(int i, int l, int r, int t) {
	if (node[i].l > r || node[i].r < l)
		return;
	if (l <= node[i].l && node[i].r <= r)
		mark(i, t);
	else {
		push_down(i);
		seg_plus(i * 2, l, r, t);
		seg_plus(i * 2 + 1, l, r, t);
		update(i);
	}
}

vector<int> begin[N_MAX][2];
int f[N_MAX][2];
int val[N_MAX];
int n, len, upper;
/*
void build(int i, int l, int r) {
	for (int j = l; j <= r; j ++)
		val[j] = 0;
}

int get_val(int i, int p) {
	return val[p];
}

int find_left(int i, int bound) {
	for (int i = len; i >= 0; i --)
		if (val[i] < bound)
			return i + 1;
	return 0;
}

void seg_plus(int i, int l, int r, int t) {
	for (int j = l; j <= r; j ++)
		val[j] += t;
}*/


void init() {
	int p;
	scanf("%d%d%d%d", &n, &len, &p, &upper);
	while (p --) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (c == 0)
			begin[a + 1][c].push_back(b);
		else
			begin[a][c].push_back(b);
	}
}
void work_forward() {
	build(1, 0, len);
	f[1][1] = 0;
	for (int i = 1; i < n; i ++) {
		sort(begin[i][1].begin(), begin[i][1].end());
		int sz = begin[i][1].size();
		for (int j = 0; j < sz; j ++) {
			int k = begin[i][1][j];
			int en = find_left(get_val(k)) - 1,
				st = j ? begin[i][1][j - 1] + 1 : 0;
			if (st <= en)
				seg_plus(1, st, en, 1);
		}
		if (sz)
			seg_plus(1, begin[i][1].back() + 1, len, 1);
		else
			seg_plus(1, 0, len, 1);
		f[i + 1][1] = get_val(0);
	}
}
void work_backward() {
	build(1, 0, len);
	f[n][0] = 0;
	for (int i = n; i > 1; i --) {
		sort(begin[i][0].begin(), begin[i][0].end());
		int sz = begin[i][0].size();
		for (int j = 0; j < sz; j ++) {
			int k = begin[i][0][j];
			int en = find_left(get_val(k)) - 1,
				st = j ? begin[i][0][j - 1] + 1 : 0;
			if (st <= en)
				seg_plus(1, st, en, 1);
		}
		if (sz)
			seg_plus(1, begin[i][0].back() + 1, len, 1);
		else
			seg_plus(1, 0, len, 1);
		f[i - 1][0] = get_val(0);
	}
}
int stat_ans() {
	int org_ans = 0;
	for (int i = 1; i <= n; i ++)
		if (f[i][1] + f[i][0] == 0)
			org_ans ++;
	int ans = 0;
	for (int l = 1, r = 0; l <= n; l ++) {
		while (r < n && f[l][0] + f[r + 1][1] <= upper)
			r ++;
		ans = max(ans, r - l + 1);
	}
	return ans - org_ans;
}
int main() {
//	freopen("t.in", "r", stdin);	
	init();
	work_forward();
	work_backward();
	printf("%d\n", stat_ans());
}
