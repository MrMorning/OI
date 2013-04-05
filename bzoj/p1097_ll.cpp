#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> pair_t;
const int inf = 0x3f3f3f3f;
const int N_MAX = 20010, M_MAX = 200010, S_MAX = 250000;
const int HASH_SIZE = 65536;

struct Edge {
	int to,cost;
	Edge *next;
} edge[M_MAX * 2], *begin[N_MAX];

void add_edge(int u, int v, int c) {
	static int edge_cnt = 0;
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->cost = c, e->next = begin[u], begin[u] = e;
}

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
} hash;
int tot_mask, to_mask[S_MAX];
 
inline int rev(int mask) {
    if (hash[mask] == -inf) {
        hash[mask] = tot_mask ++;
        to_mask[tot_mask - 1] = mask;
    }
    return hash[mask];
}

int rest[25];
int n, m, k;
int dist[N_MAX], f[25][25];
int log2[(1 << 20) + 1];
ll g[S_MAX][22];
priority_queue<pair_t, vector<pair_t>, greater<pair_t> > PQ;

int main() {
	//freopen("t.in", "r", stdin);
	for (int i = 0; i < 20; i ++)
		log2[1 << i] = i;
	scanf("%d%d%d", &n, &m, &k);
	while (m --) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add_edge(x, y, z);
		add_edge(y, x, z);
	}
	{
		int t;
		scanf("%d", &t);	
		while (t --) {
			int x, y;
			scanf("%d%d", &x, &y);
			rest[y] |= 1 << (x - 2);
		}
	}
	for (int i = 1; i <= k + 1; i ++) {
		int st = i;
		memset(dist, 0x3f, sizeof(dist));
		dist[st] = 0;
		PQ.push(make_pair(0, st));
		while (!PQ.empty()) {
			pair_t p = PQ.top(); PQ.pop();
			int u = p.second;
			if (dist[u] < p.first)
				continue;
			for (Edge *e = begin[u]; e; e = e->next) {
				int v = e->to;
				if (dist[v] > p.first + e->cost) {
					dist[v] = p.first + e->cost;
					PQ.push(make_pair(dist[v], v));
				}
			}
		}
		for (int j = 1; j <= k + 1; j ++)
			f[i][j] = dist[j];
		f[i][0] = dist[n];
	}
	memset(g, 0x3f, sizeof(g));
	g[rev(0)][1] = 0;
	for (int t = 0; t < tot_mask; t ++)
		for (int i = 1; i <= k + 1; i ++)
			if (g[t][i] != 0x3f3f3f3f3f3f3f3fLL) {
				int s = to_mask[t];
				int tmp = (~s) & ((1 << k) - 1);
				while (tmp) {
					int v = tmp & -tmp;
					tmp -= v;
					int j = log2[v] + 2;
					if ((s & rest[j]) == rest[j])
						g[rev(s + v)][j] = min(g[rev(s + v)][j], g[t][i] + f[i][j]);
				}
			}
	ll res = 0x3f3f3f3f3f3f3f3fLL;
	for (int lim = 1 << k, i = 1; i <= k + 1; i ++)
		res = min(res, g[rev(lim - 1)][i] + f[i][0]);
	printf("%lld\n", res);
}
