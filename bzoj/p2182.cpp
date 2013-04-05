#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
using namespace std;
typedef pair<int, int> pair_t;

const int LEN_MAX = 1000;
const int BUFFER_LEN = 1024 * 1024 * 5;
static char buffer[BUFFER_LEN];
char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
{ \
        ptr ++; \
        if (ptr == buf_end) \
        { \
                ptr = buffer; \
                buf_end = buffer + fread(buffer, 1, BUFFER_LEN, stdin); \
        } \
}
#define READ_INT(_x_) \
{ \
        while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
        PTR_NEXT(); \
        bool _nega_ = false; \
        if (*ptr == '-') \
        { \
                _nega_ = true; \
                PTR_NEXT(); \
        } \
        int register _n_ = 0; \
        while (*ptr >= '0' && *ptr <= '9') \
        { \
                _n_ = _n_ * 10 + *ptr - '0'; \
                PTR_NEXT(); \
        } \
        if (_nega_) \
        _n_ = - _n_; \
        (_x_) = (_n_); \
}

const int VERTEX_MAX = 210, EDGE_MAX = 50010;
const int inf = 0x3f3f3f3f;

struct Info {
	int u, v, d, key;
} best;

int f[VERTEX_MAX][VERTEX_MAX];
int e[VERTEX_MAX][VERTEX_MAX];
pair_t order[VERTEX_MAX][VERTEX_MAX];
int stk[VERTEX_MAX];
int n, m;

#define upd(_u, _v, _d, _key) {\
	if ( _key < best.key ) {\
		best.u = _u, best.v = _v;\
		best.d = _d, best.key = _key;\
	}\
}

void solve(int u, int v) {
	int l = e[u][v];
	int top = 0;
	for ( int i = 0; i < n; i ++ ) {
		int w = order[u][i].second;
		if ( top ) {
			int t = stk[top - 1];
			if ( f[w][v] <= f[t][v] )
				continue;
		}
		stk[top ++] = w;
	}
	upd(u, v, 0, f[u][stk[0]]);
	upd(u, v, l, f[v][stk[top - 1]]);
	for ( int i = 0; i < top - 1; i ++ ) {
		int w = stk[i];
		int t = (f[v][w] + l - f[u][w]) >> 1,
			x = ((t << 1) + f[u][w] - f[u][stk[i + 1]] ) >> 1,
			y = x + f[u][stk[i + 1]];
		upd(u, v, x, y);
	}
}

void init() {
	READ_INT(n);
	READ_INT(m);
	memset(f, 0x3f, sizeof(f));
	memset(e, 0x3f, sizeof(e));
	for ( int i = 0; i < m; i ++ ) {
		int u, v, w;
		READ_INT(u);
		READ_INT(v);
		READ_INT(w);
		u --, v --;
		w <<= 1;
		if ( e[u][v] > w )
			e[u][v] = e[v][u] = f[u][v] = f[v][u] = w;
	}

	for ( int k = 0; k < n; k ++ )
		for ( int i = 0; i < n; i ++ )
			for ( int j = 0; j < n; j ++ )
				if ( f[i][j] > f[i][k] + f[k][j] )
					f[i][j] = f[i][k] + f[k][j];
	for ( int i = 0; i < n; i ++ )
		f[i][i] = 0;
	for ( int k = 0; k < n; k ++ ) {
		for ( int i = 0; i < n; i ++ )
			order[k][i] = make_pair(f[k][i], i);
		sort(order[k], order[k] + n, greater<pair_t>());
	}
	best.key = inf;
}

int main() {
	freopen("t.in", "r", stdin);
	init();
	for ( int u = 0; u < n; u ++ )
		for ( int v = u + 1; v < n; v ++ )
			if ( e[u][v] != inf ) 
				solve(u, v);
	printf("%d\n", best.key);
}
