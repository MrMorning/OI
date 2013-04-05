#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;
typedef pair<int, int> pair_t;
const int S_MAX = 300000;
const int inf = 0x3f3f3f3f;
const int HASH_SIZE = 1 << 16;
int n, board[22][22][2], sz[22];
int f[S_MAX], g[S_MAX], to_mask[S_MAX], tot_mask;

struct HashTable {
	vector<pair_t> ele[HASH_SIZE];
	int &operator[] (const int key) {
		int code = (key ^ (key >> 2) ^ (key << 3)) & (HASH_SIZE - 1);
		int sz = ele[code].size();
		for (int i = 0; i < sz; i ++)
			if (ele[code][i].first == key)
				return ele[code][i].second;
		ele[code].push_back(make_pair(key, -inf));
		return ele[code][sz].second;
	}
	void clear() {
		memset(ele, 0, sizeof(ele));
	}
} hash;
void upd(int &x, int y) {
	if (x > y)
		x = y;
}
#define GET(x, i) (((x) >> ((i) << 1)) & 3)
inline int SET(int x, int i, int t) {
    int rem = x & ((1 << (i << 1)) - 1);
    x >>= i << 1;
    x >>= 2; x <<= 2;
    x += t;
    x <<= i << 1;
    x += rem;
    return x;
}
 
int rev(int mask) {
    if (hash[mask] == -inf) {
        hash[mask] = tot_mask ++;
        to_mask[tot_mask - 1] = mask;
    }
    return hash[mask];
}

#define IS_TARGET(x) (1 <= (x) && (x) <= 3)

void solve() {
	hash.clear();
	memset(f, 0x3f, sizeof(f));
	tot_mask = 0;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n + i; j ++)
			scanf("%d%d", &board[i][j][0], &board[i][j][1]);
		scanf("%d", &board[i][n + i][0]);
		board[i][n + i][1] = 4;
		sz[i] = n + i + 1;
	}
	for (int i = n; i < 2 * n; i ++) {
		scanf("%d", &board[i][0][1]);
		board[i][0][0] = 4;
		for (int j = 1; j < 2 * n - (i - n); j ++)
			scanf("%d%d", &board[i][j][0], &board[i][j][1]);
		sz[i] = 2 * n - (i - n);
	}
	f[rev(0)] = 0;
	for (int i = 0; i < 2 * n; i ++) {
		for (int j = 0; j < sz[i]; j ++) {
			memset(g, 0x3f, sizeof(g));
			for (int k = 0, lim = tot_mask; k < lim; k ++)
				if (f[k] != inf) {
					int s = to_mask[k];
					int a = GET(s, j), b = GET(s, j + 1);
					int u = board[i][j][0], v = board[i][j][1];
					if (u == 0 && v == 0) {/*{{{*/
						if (a == 0 && b == 0) {
							upd(g[k], f[k]);
							for (int t = 1; t <= 3; t ++) {
								int ns = SET(s, j, t);
								ns = SET(ns, j + 1, t);
								upd(g[rev(ns)], f[k] + 2);
							}
						}
						else if (a == 0 && IS_TARGET(b)) {
							upd(g[k], f[k] + 1);
							int ns = SET(s, j + 1, 0);
							ns = SET(ns, j, b);
							upd(g[rev(ns)], f[k] + 2);
						}
						else if (IS_TARGET(a) && b == 0) {
							upd(g[k], f[k] + 1);
							int ns = SET(s, j, 0);
							ns = SET(ns, j + 1, a);
							upd(g[rev(ns)], f[k] + 2);
						}
						else {
							assert(IS_TARGET(a) && IS_TARGET(b));
							upd(g[k], f[k] + 2);
							if (a != b)
								continue;
							int ns = SET(s, j, 0);
							ns = SET(ns, j + 1, 0);
							upd(g[rev(ns)], f[k] + 2);
						}
					}/*}}}*/
					else if (u == 0 && IS_TARGET(v)) {/*{{{*/
						if (a == 0 && b == 0) {
							int ns = SET(s, j, v);
							upd(g[rev(ns)], f[k] + 2);
							ns = SET(s, j + 1, v);
							upd(g[rev(ns)], f[k] + 1);
						}
						else if (a == 0 && IS_TARGET(b)) {
							if (b != v)
								continue;
							int ns = SET(s, j + 1, 0);
							upd(g[rev(ns)], f[k] + 1);
						}
						else if (IS_TARGET(a) && b == 0) {
							int ns = SET(s, j + 1, v);
							upd(g[rev(ns)], f[k] + 2);
							if (a == v) {
								int ns = SET(s, j, 0);
								upd(g[rev(ns)], f[k] + 2);
							}
						}
						else {
							assert(IS_TARGET(a) && IS_TARGET(b));
							if (b != v)
								continue;
							int ns = SET(s, j + 1, 0);
							upd(g[rev(ns)], f[k] + 2);
						}
					}/*}}}*/
					else if (u == 0 && v == 4) {/*{{{*/
						if (a == 0 && b == 0)
							upd(g[k], f[k]);
						else if (IS_TARGET(a) && b == 0)
							upd(g[k], f[k] + 1);
					}/*}}}*/
					else if (IS_TARGET(u) && v == 0) {/*{{{*/
						if (a == 0 && b == 0) {
							int ns = SET(s, j + 1, u);
							upd(g[rev(ns)], f[k] + 2);
							ns = SET(s, j, u);
							upd(g[rev(ns)], f[k] + 1);
						}
						else if (a == 0 && IS_TARGET(b)) {
							int ns = SET(s, j, u);
							upd(g[rev(ns)], f[k] + 2);
							if (b == u) {
								ns = SET(s, j + 1, 0);
								upd(g[rev(ns)], f[k] + 2);
							}
						}
						else if (IS_TARGET(a) && b == 0) {
							if (a != u)
								continue;
							int ns = SET(s, j, 0);
							upd(g[rev(ns)], f[k] + 1); //!
						}
						else {
							assert(IS_TARGET(a) && IS_TARGET(b));
							if (a != u)
								continue;
							int ns = SET(s, j, 0);
							upd(g[rev(ns)], f[k] + 2);
						}
					}/*}}}*/
					else if (IS_TARGET(u) && IS_TARGET(v)) {/*{{{*/
						if (u == v) {
							if (a == 0 && b == 0) {
								upd(g[k], f[k] + 2);
							}
						}
						else {
							if (IS_TARGET(a) && a != u)
								continue;
							if (IS_TARGET(b) && b != v)
								continue;
							if (a == 0 && b == 0) {
								int ns = SET(s, j, u);
								ns = SET(ns, j + 1, v);
								upd(g[rev(ns)], f[k] + 2);
							}
							else if (a == 0) {
								int ns = SET(s, j, u);
								ns = SET(ns, j + 1, 0);
								upd(g[rev(ns)], f[k] + 2);
							}
							else if (b == 0) {
								int ns = SET(s, j + 1, v);
								ns = SET(ns, j, 0);
								upd(g[rev(ns)], f[k] + 2);
							}
							else {
								int ns = SET(s, j, 0);
								ns = SET(ns, j + 1, 0);
								upd(g[rev(ns)], f[k] + 2);
							}
						}
					}/*}}}*/
					else if (IS_TARGET(u) && v == 4) {/*{{{*/
						if (b != 0)
							continue;
						if (a == 0) {
							int ns = SET(s, j, u);
							upd(g[rev(ns)], f[k] + 1);
						}
						else {
							assert(IS_TARGET(a));
							if (a == u) {
								int ns = SET(s, j, 0);
								upd(g[rev(ns)], f[k] + 1);
							}
						}
					}/*}}}*/
					else if (u == 4 && v == 0) {/*{{{*/
						if (a == 0 && b == 0)
							upd(g[k], f[k]);
						else if (a == 0 && IS_TARGET(b))
							upd(g[k], f[k] + 1);
					}/*}}}*/
					else if (u == 4 && IS_TARGET(v)) {/*{{{*/
						if (a != 0)
							continue;
						if (b == 0) {
							int ns = SET(s, j + 1, v);
							upd(g[rev(ns)], f[k] + 1);
						}
						else {
							assert(IS_TARGET(b));
							if (b == v) {
								int ns = SET(s, j + 1, 0);
								upd(g[rev(ns)], f[k] + 1);
							}
						}
					}/*}}}*/
					else {/*{{{*/
						assert(u == 4 && v == 4);
						if (a == 0 && b == 0)
							upd(g[k], f[k]);
					}/*}}}*/
				}
			memcpy(f, g, sizeof(g));
		}
		memset(g, 0x3f, sizeof(g));
		if (i < n) {
			for (int k = 0, lim = tot_mask; k < lim; k ++) 
				if (f[k] != inf) {
					int s = to_mask[k];
					if (GET(s, sz[i]) == 0) {
						int ns = s << 2;
						upd(g[rev(ns)], f[k]);
					}
				}
		}
		else {
			for (int k = 0, lim = tot_mask; k < lim; k ++) 
				if (f[k] != inf) {
					int s = to_mask[k];
					if (GET(s, 0) == 0 && GET(s, sz[i]) == 0)
						upd(g[k], f[k]);
				}
		}
		memcpy(f, g, sizeof(g));
	}
	printf("%d\n", f[rev(0)] - 3);
}
int main() {
	freopen("t.in", "r", stdin);
	while (scanf("%d", &n) != EOF)
		solve();
}
