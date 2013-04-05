#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;
typedef pair<int, int> pair_t;
const int MOD = 1000000007;
const int S_MAX = 1300000;
const int inf = 0x3f3f3f3f;
const int HASH_SIZE = 1 << 18;
int n, board[32][33][2], sz[22];
int to_mask[S_MAX], tot_mask;
struct Info {
	int key, val;
	Info(){}
	Info (int _key, int _val):
		key(_key), val(_val){}
} f[S_MAX], g[S_MAX];

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
void upd(Info &x, Info y) {
	if (x.key > y.key)
		x = y;
	else if (x.key == y.key)
		x.val = (x.val + y.val) % MOD;
}
int GET(int x, int i) {
	return (((x) >> ((i) << 1)) & 3);
}
int SET(int x, int i, int t) {
	int rem = x & ((1 << (i << 1)) - 1);
	x >>= i << 1;
	x >>= 2; x <<= 2;
	x += t;
	x <<= i << 1;
	x += rem;
	return x;
}

inline int rev(int mask) {
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
	f[rev(0)].key = 0, f[rev(0)].val = 1;
	for (int i = 0; i < 2 * n; i ++) {
		for (int j = 0; j < sz[i]; j ++) {
			memset(g, 0x3f, sizeof(g));
			for (int k = 0, lim = tot_mask; k < lim; k ++)
				if (f[k].key != inf) {
					int s = to_mask[k];
					int a = GET(s, j), b = GET(s, j + 1);
					int u = board[i][j][0], v = board[i][j][1];
#define REF(x) upd(g[rev(ns)], Info(f[k].key + x, f[k].val))
#define REF2(x) upd(g[k], Info(f[k].key + x, f[k].val))
					if (u == 0 && v == 0) {/*{{{*/
						if (a == 0 && b == 0) {
							upd(g[k], f[k]);
							for (int t = 1; t <= 3; t ++) {
								int ns = SET(s, j, t);
								ns = SET(ns, j + 1, t);
								REF(2);
							}
						}
						else if (a == 0 && IS_TARGET(b)) {
							REF2(1);
							int ns = SET(s, j + 1, 0);
							ns = SET(ns, j, b);
							REF(2);
						}
						else if (IS_TARGET(a) && b == 0) {
							REF2(1);
							int ns = SET(s, j, 0);
							ns = SET(ns, j + 1, a);
							REF(2);
						}
						else {
							assert(IS_TARGET(a) && IS_TARGET(b));
							REF2(2);
							if (a != b)
								continue;
							int ns = SET(s, j, 0);
							ns = SET(ns, j + 1, 0);
							REF(2);
						}
					}/*}}}*/
					else if (u == 0 && IS_TARGET(v)) {/*{{{*/
						if (a == 0 && b == 0) {
							int ns = SET(s, j, v);
							REF(2);
							ns = SET(s, j + 1, v);
							REF(1);
						}
						else if (a == 0 && IS_TARGET(b)) {
							if (b != v)
								continue;
							int ns = SET(s, j + 1, 0);
							REF(1);
						}
						else if (IS_TARGET(a) && b == 0) {
							int ns = SET(s, j + 1, v);
							REF(2);
							if (a == v) {
								int ns = SET(s, j, 0);
								REF(2);
							}
						}
						else {
							assert(IS_TARGET(a) && IS_TARGET(b));
							if (b != v)
								continue;
							int ns = SET(s, j + 1, 0);
							REF(2);
						}
					}/*}}}*/
					else if (u == 0 && v == 4) {/*{{{*/
						if (a == 0 && b == 0)
							upd(g[k], f[k]);
						else if (IS_TARGET(a) && b == 0)
							REF2(1);
					}/*}}}*/
					else if (IS_TARGET(u) && v == 0) {/*{{{*/
						if (a == 0 && b == 0) {
							int ns = SET(s, j + 1, u);
							REF(2);
							ns = SET(s, j, u);
							REF(1);
						}
						else if (a == 0 && IS_TARGET(b)) {
							int ns = SET(s, j, u);
							REF(2);
							if (b == u) {
								ns = SET(s, j + 1, 0);
								REF(2);
							}
						}
						else if (IS_TARGET(a) && b == 0) {
							if (a != u)
								continue;
							int ns = SET(s, j, 0);
							REF(1);
						}
						else {
							assert(IS_TARGET(a) && IS_TARGET(b));
							if (a != u)
								continue;
							int ns = SET(s, j, 0);
							REF(2);
						}
					}/*}}}*/
					else if (IS_TARGET(u) && IS_TARGET(v)) {/*{{{*/
						if (u == v) {
							if (a == 0 && b == 0) {
								REF2(2);
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
								REF(2);
							}
							else if (a == 0) {
								int ns = SET(s, j, u);
								ns = SET(ns, j + 1, 0);
								REF(2);
							}
							else if (b == 0) {
								int ns = SET(s, j + 1, v);
								ns = SET(ns, j, 0);
								REF(2);
							}
							else {
								int ns = SET(s, j, 0);
								ns = SET(ns, j + 1, 0);
								REF(2);
							}
						}
					}/*}}}*/
					else if (IS_TARGET(u) && v == 4) {/*{{{*/
						if (b != 0)
							continue;
						if (a == 0) {
							int ns = SET(s, j, u);
							REF(1);
						}
						else {
							assert(IS_TARGET(a));
							if (a == u) {
								int ns = SET(s, j, 0);
								REF(1);
							}
						}
					}/*}}}*/
					else if (u == 4 && v == 0) {/*{{{*/
						if (a == 0 && b == 0)
							upd(g[k], f[k]);
						else if (a == 0 && IS_TARGET(b))
							REF2(1);
					}/*}}}*/
					else if (u == 4 && IS_TARGET(v)) {/*{{{*/
						if (a != 0)
							continue;
						if (b == 0) {
							int ns = SET(s, j + 1, v);
							REF(1);
						}
						else {
							assert(IS_TARGET(b));
							if (b == v) {
								int ns = SET(s, j + 1, 0);
								REF(1);
							}
						}
					}/*}}}*/
					else {/*{{{*/
						assert(u == 4 && v == 4);
						if (a == 0 && b == 0)
							upd(g[k], f[k]);
					}/*}}}*/
				}
			memcpy(f, g, sizeof(Info) * tot_mask);
		}
		memset(g, 0x3f, sizeof(g));
		if (i < n) {
			for (int k = 0, lim = tot_mask; k < lim; k ++) 
				if (f[k].key != inf) {
					int s = to_mask[k];
					if (GET(s, sz[i]) == 0) {
						int ns = s << 2;
						upd(g[rev(ns)], f[k]);
					}
				}
		}
		else {
			for (int k = 0, lim = tot_mask; k < lim; k ++) 
				if (f[k].key != inf) {
					int s = to_mask[k];
					if (GET(s, 0) == 0 && GET(s, sz[i]) == 0)
						upd(g[k], f[k]);
				}
		}
		memcpy(f, g, sizeof(Info) * tot_mask);
	}
	if (f[rev(0)].key == inf)
		puts("-1 -1");
	else
		printf("%d %d\n", f[rev(0)].key - 3, f[rev(0)].val);
}
int main() {
	freopen("t.in", "r", stdin);
	while (scanf("%d", &n) != EOF)
		solve();
}
