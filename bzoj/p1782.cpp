#include <cstdio>

const int N_MAX = 111111;

struct Edge {
	int to;
	Edge *next;
} edge[N_MAX * 2], *begin[N_MAX];
int edge_cnt = 0;
int seq[2 * N_MAX];
int idt[2 * N_MAX];
int st[N_MAX], en[N_MAX];
int n_seq;

void add_edge(int u, int v) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

void dfs(int x) {
	seq[++ n_seq] = x;
	st[x] = n_seq;

	for (Edge *e = begin[x]; e; e = e->next) {
		int y = e->to;
		if (!st[y]) 
			dfs(y);
	}

	seq[++ n_seq] = -x;
	en[x] = n_seq;
}

void add(int i, int val) {
	for(; i < 2 * N_MAX; i += i & -i)
		idt[i] += val;
}

int sum(int i) {
	int res = 0;
	for(; i; i -= i & -i)
		res += idt[i];
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int N;
	scanf("%d", &N);
	for (int i = 1; i < N; i ++) {
		int a, b;
		 scanf("%d%d", &a, &b);
		 add_edge(a, b), add_edge(b, a);
	}
	dfs(1);
	for (int i = 1; i <= N; i ++) {
		int t;
		scanf("%d", &t);
		printf("%d\n", sum(en[t] - 1));
		add(st[t], 1);
		add(en[t], -1);
	}
}
