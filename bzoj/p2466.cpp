#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N_MAX = 105;
const int inf = 0x3f3f3f3f;

void upd(int &x, int y) {
	if ( y < x )
		x = y;
}

struct Edge {
	int to;
	Edge *next;
} edge[N_MAX * 2], *begin[N_MAX];
int edge_cnt;

void add_edge(int u, int v) {
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

int n;
int f[N_MAX][2][2];

void work(int x, int fa) {
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( y == fa ) continue;
		work(y, x);
	}

	f[x][0][0] = 0, f[x][1][1] = 1;
	f[x][0][1] = f[x][1][0] = inf;
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( y == fa ) continue;
		static int pre_fx[2][2];
		memcpy(pre_fx, f[x], sizeof(f[x]));
		memset(f[x], 0x3f, sizeof(f[x]));

		upd(f[x][0][0], pre_fx[0][0] + f[y][0][1]);
		upd(f[x][0][1], pre_fx[0][0] + f[y][1][1]);
		upd(f[x][0][1], pre_fx[0][1] + f[y][0][1]);
		upd(f[x][0][0], pre_fx[0][1] + f[y][1][1]);

		upd(f[x][1][0], pre_fx[1][0] + f[y][0][0]);
		upd(f[x][1][1], pre_fx[1][0] + f[y][1][0]);
		upd(f[x][1][1], pre_fx[1][1] + f[y][0][0]);
		upd(f[x][1][0], pre_fx[1][1] + f[y][1][0]);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d", &n), n ) {
		memset(begin, 0, sizeof(begin));
		edge_cnt = 0;
		for ( int i = 0; i < n - 1; i ++ ) {
			int a, b;
			scanf("%d%d", &a, &b);
			add_edge(a, b);
			add_edge(b, a);
		}
		work(1, 0);
		printf("%d\n", min(f[1][0][1], f[1][1][1]));
	}
}
