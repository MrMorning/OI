#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAX_N = 2000000, SON = 26;
string str[MAX_N * 2];
int n, sz[MAX_N], vv[MAX_N * 2 + 2], sa[MAX_N * 2 + 2], rank[MAX_N * 2 + 1], height[MAX_N * 2 + 2], cnt[MAX_N * 2 + 2], len;
bool vis[MAX_N];
long long ans = 0LL;

namespace trie {
	struct node_t {
		int cnt, end;
		node_t *son[SON];
		node_t() { cnt = 0, end = 0, memset(son, 0, sizeof(son)); }
	} *root = NULL;

	void init() {
		root = new node_t;
	}

	void ins(int sz, const string &x) {
		node_t *pos = root;
		for (int i = 0; i < sz; i ++) {
			int t = x[i] - 'a';
			if (vv[rank[i]] == sz - i) pos -> cnt ++;
			if (!pos -> son[t]) pos -> son[t] = new node_t;
			pos = pos -> son[t];
		}
		pos -> end ++;
	}

	void go(int sz, const string &x) {
		node_t *pos = root;
		for (int i = 0; i < sz; i ++) {
			int t = x[i] - 'a';
			pos = pos -> son[t];
			if (!pos) return;
			if (pos -> end && vv[rank[i + 1]] == sz - i - 1) ans += pos -> end;
		}
		ans += pos -> cnt;
	}
}

struct node_t {
	int v[2], p;
	bool operator == (const node_t &t) const {
		return v[0] == t.v[0] && v[1] == t.v[1];
	}
} nd[MAX_N * 2 + 1], tp[MAX_N * 2 + 1];

void ra(int b) {
	for (int i = 1; i >= 0; i --) {
		memset(cnt, 0, sizeof(int) * (b + 1));
		for (int j = 0; j < len; j ++) cnt[nd[j].v[i]] ++;
		for (int j = 1; j <= b; j ++) cnt[j] += cnt[j - 1];
		for (int j = len - 1; j >= 0; j --) tp[-- cnt[nd[j].v[i]]] = nd[j];
		memcpy(nd, tp, sizeof(node_t) * len);
	}
	for (int i = 0, j = 0, k = 1; i < len; i = j, k ++)
		while (j < len && nd[j] == nd[i]) rank[nd[j ++].p] = k;
}

void get_sa(const string &x) {
	len = x.size();
	for (int i = 0; i < len; i ++) nd[i].v[0] = x[i], nd[i].v[1] = 0, nd[i].p = i;
	ra(255);
	for (int s = 1; s < len; s <<= 1) {
		for (int i = 0; i < len; i ++) {
			nd[i].v[0] = rank[i], nd[i].v[1] = i + s < len ? rank[i + s] : 0;
			nd[i].p = i;
		}
		ra(len);
	}
	for (int i = 0; i < len; i ++) sa[rank[i]] = i;
	for (int i = 0, j, k = 0; i < len; height[rank[i ++]] = k)
		for (k ? k -- : 0, j = sa[rank[i] - 1]; x[i + k] == x[j + k]; k ++);
}

int main() {
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i ++) {
		cin >> sz[i] >> str[i];
		str[i + n] = str[i];
		sz[i + n] = sz[i];
		reverse(str[i].begin(), str[i].end());
	}
	trie::init();
	for (int i = 0; i < n; i ++) {
		string tmp = str[i] + '#' + str[i + n];
		get_sa(tmp);
		memset(vv, 0, sizeof(vv));
		vv[rank[sz[i] + 1]] = height[rank[sz[i] + 1]];
		for (int j = rank[sz[i] + 1] - 1; j >= 1; j --) vv[j] = min(vv[j + 1], height[j + 1]);
		vv[rank[sz[i] + 1] + 1] = height[rank[sz[i] + 1] + 1];
		for (int j = rank[sz[i] + 1] + 2; j <= sz[i] * 2 + 1; j ++) vv[j] = min(vv[j - 1], height[j]);
		trie::ins(sz[i], str[i]);
	}
	for (int i = 0; i < n; i ++) {
		string tmp = str[i + n] + '#' + str[i];
		get_sa(tmp);
		memset(vv, 0, sizeof(vv));
		vv[rank[sz[i] + 1]] = height[rank[sz[i] + 1]];
		for (int j = rank[sz[i] + 1] - 1; j >= 1; j --) vv[j] = min(vv[j + 1], height[j + 1]);
		vv[rank[sz[i] + 1] + 1] = height[rank[sz[i] + 1] + 1];
		for (int j = rank[sz[i] + 1] + 2; j <= sz[i] * 2 + 1; j ++) vv[j] = min(vv[j - 1], height[j]);
		trie::go(sz[i], str[i + n]);
	}
	cout << ans << endl;
	return 0;
}
