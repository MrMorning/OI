#include <cstdio>
const int N_MAX = 250010;
struct Edge {
	int to;
	Edge *next;
} edge[N_MAX], *begin[N_MAX];
int idt[2 * N_MAX], st[N_MAX], en[N_MAX];
int n, m;
void add(int i, int t) {
	for (; i < 2 * N_MAX; i += i & -i)
		idt[i] += t;
}
int sum(int i) {
	int res = 0;
	for (; i; i -= i & -i)
		res += idt[i];
	return res;
}
void add_edge(int x, int y) {
	static int edge_cnt = 0;
	Edge *e = edge + edge_cnt ++;
	e->to = y, e->next = begin[x], begin[x] = e;
}
int pos;
void dfs(int x) {
	st[x] = ++ pos;
	for (Edge *e = begin[x]; e; e = e->next) {
		int y = e->to;
		dfs(y);
	}
	en[x] = ++ pos;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i ++) {
		int a, b;
		scanf("%d%d", &a, &b);
		add_edge(a, b);
	}
	dfs(1);
	for (int i = 1; i <= n; i ++)
		add(st[i], 1), add(en[i], -1);
	scanf("%d", &m);
	for (int i = 0; i < n - 1 + m; i ++) {
		char cmd[5];
		scanf("%s", cmd);
		if (cmd[0] == 'W') {
			int x;
			scanf("%d", &x);
			printf("%d\n", sum(st[x]) - 1);
		}
		else {
			int x, y;
			scanf("%d%d", &x, &y);
			add(st[y], -1);
			add(en[y], 1);
		}
	}
}
