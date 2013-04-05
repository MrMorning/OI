#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define LEFT_BRACKET -1
#define RIGHT_BRACKET -2

const int N_MAX = 111111;
const int LEN_MAX = N_MAX * 3;
const int INF = 0x3f3f3f3f;

int n, m;
bool on[N_MAX];
int pos[N_MAX], seq[LEN_MAX];
int seq_len = 0;

struct Node {
	int l, r, a, b;
	int pp, sp, pm, sm, res;
} node[LEN_MAX * 3];

void update(int i) {
	Node &x = node[i],
		 &lc = node[i * 2],
		 &rc = node[i * 2 + 1];
	x.a = lc.a + max(0, rc.a - lc.b);
	x.b = rc.b + max(0, lc.b - rc.a);
	x.res = max(lc.res, rc.res);
	x.res = max(x.res, lc.sp + rc.pm);
	x.res = max(x.res, lc.sm + rc.pp);

	x.pp = max(lc.pp, lc.a + lc.b + rc.pm);
	x.pp = max(x.pp, lc.a - lc.b + rc.pp);
	x.pm = max(lc.pm, lc.b - lc.a + rc.pm);
	x.sp = max(rc.sp, lc.sp + rc.b - rc.a);
	x.sp = max(x.sp, lc.sm + rc.b + rc.a);
	x.sm = max(rc.sm, lc.sm + rc.a - rc.b);
}

void build(int i, int l, int r) {
	Node &x = node[i];
	x.l = l, x.r = r;
	if (l == r) {
		if (seq[l] > 0) {
			x.res = -INF;
			x.a = x.b = 0;
			x.pp = x.sp = x.pm = x.sm = 0;
		}
		else {
			x.res = x.pp = x.sp = x.pm = x.sm = -INF;
			x.a = x.b = 0;
			if (seq[l] == LEFT_BRACKET)
				x.b = 1;
			else
				x.a = 1;
		}
	}
	else {
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i  * 2 + 1, mid + 1, r);
		update(i);
	}
}

void refresh(int i, int pos, bool s) {
	Node &x = node[i];
	if (x.l > pos || x.r < pos)
		return;
	if (x.l == pos && x.r == pos) {
		if (s) {
			x.res = x.pp = x.pm = x.sp = x.sm = -INF;
			x.a = x.b = 0;
		}
		else {
			x.res = -INF;
			x.a = x.b = 0;
			x.pp = x.sp = x.pm = x.sm = 0;
		}
		return;
	}
	refresh(i * 2, pos, s);
	refresh(i * 2 + 1, pos, s);
	update(i);
}

struct Edge {
	int to;
	Edge *next;
} edge[N_MAX << 1], *begin[N_MAX];

void add_edge(int u, int v) {
	static int edge_cnt = 0;
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], begin[u] = e;
}

void dfs(int x) {
	seq[++ seq_len] = LEFT_BRACKET;
	seq[++ seq_len] = x;
	pos[x] = seq_len;
	for (Edge *e = begin[x]; e; e = e->next) {
		if (pos[e->to])
			continue;
		dfs(e->to);
	}
	seq[++ seq_len] = RIGHT_BRACKET;
}

int main() {
//	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1);
	build(1, 1, seq_len);
	scanf("%d", &m);
	while (m --) {
		static char cmd[4];
		scanf("%s", cmd);
		if (cmd[0] == 'G') {
			int res = node[1].res;
			if (res != -INF)
				printf("%d\n", res);
			else {
				if (node[1].pp != -INF)
					printf("0\n");
				else
					printf("-1\n");
			}
		}
		else {
			int x;
			scanf("%d", &x);
			on[x] ^= 1;
			refresh(1, pos[x], on[x]);
		}
	}
}
