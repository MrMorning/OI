#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ull;

struct Edge {
	int to;
	Edge *next;
	ull d;
} edge[222222], *begin[111111];
int S[111111], T[111111];
ull W[111111], D[111111];
bool vis[111111];
int N, M;
ull X[222222];

void add_edge(int u, int v, ull d) {
	static int edge_cnt = 0;
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u], e->d = d;
	begin[u] = e;
}

ull gauss(ull certain) {
	ull res = certain;
	for (int d = 62; d >= 0; d --) {
		ull m = 0;
		for (int i = 0; i < M; i ++)
			m = max(m, X[i]);
		for (int i = 0; i < M; i ++)
			X[i] = min(X[i], X[i] ^ m);
		res = max(res, res ^ m);
	}
	return res;
}

void dfs(int x) {
	vis[x] = true;
	for(Edge *e = begin[x]; e; e = e->next){
		int y = e->to;
		if (vis[y])
			continue;
		W[y] = W[x] ^ e->d;
		dfs(y);
	}
}

int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i ++) {
		scanf("%d%d%llu", &S[i], &T[i], &D[i]);
		add_edge(S[i], T[i], D[i]);
		add_edge(T[i], S[i], D[i]);
	}
	W[1] = 0;
	dfs(1);
	for (int i = 0; i < M; i ++)
		X[i] = W[S[i]] ^ W[T[i]] ^ D[i];
	printf("%llu\n", gauss(W[N]));
}
