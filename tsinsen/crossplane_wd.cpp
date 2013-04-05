#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int kMaxN = 3000;
int n, m, cnt;
vector<int> to[kMaxN];
vector<int> cost[kMaxN];
vector<bool> used[kMaxN];
vector<int> idx[kMaxN], ridx[kMaxN];
struct Point {
	int x, y;
	Point() {}
	Point(int x_, int y_) : x(x_), y(y_) {}
} pnt[kMaxN];
typedef Point Vector;
inline Vector operator + (const Vector &a, const Vector &b) {
	return Vector(a.x + b.x, a.y + b.y);
}
inline Vector operator - (const Vector &a, const Vector &b) {
	return Vector(a.x - b.x, a.y - b.y);
}
inline int det(const Vector &a, const Vector &b) {
	return (a.x * b.y - b.x * a.y);
}
#define pb push_back
vector<int> way;
vector<int> eid;
bool Dfs(int cur, int pre, int sta) {
	if (cur == sta && pre != -1) return true;
	way.pb(cur);
	int sz = to[cur].size();
	int rec = 0;
	while (rec < sz && (used[cur][rec] || to[cur][rec] == pre)) ++ rec;
	for (int i = rec + 1; i < sz; ++ i)
		if (!used[cur][i] && to[cur][i] != pre && det(pnt[to[cur][i]] - pnt[cur], pnt[to[cur][rec]] - pnt[cur]) > 0) rec = i;
	if (rec < sz) {
		used[cur][rec] = true;
		eid.pb(rec);
		if (Dfs(to[cur][rec], cur, sta)) return true;
		used[cur][rec] = false;
	}
	return false;
}
struct Edge {
	int u, v, c;
	Edge() {}
	Edge(int u_, int v_, int c_) : u(u_), v(v_), c(c_) {}
	bool operator < (const Edge &t) const {
		return (c < t.c);
	}
};
struct DS {
	int root[kMaxN];
	int find(int x) {
		return (x == root[x] ? x : root[x] = find(root[x]));
	}
} ds;
vector<Edge> e;
int SpanningTree() {
	for (int i = 0; i < n; ++ i) {
		int sz = to[i].size();
		for (int j = 0; j < sz; ++ j) {
			if (cost[i][j] == 0) continue;
			e.pb(Edge(ridx[i][j], idx[i][j], cost[i][j]));
		}
	}
	sort(e.begin(), e.end());
	for (int i = 0; i < cnt; ++ i) ds.root[i] = i;
	int ec = e.size(), res = 0;
	for (int i = 0; i < ec; ++ i) {
		int u = e[i].u, v = e[i].v;
		u = ds.find(u), v = ds.find(v);
		if (u != v) {
			res += e[i].c;
			ds.root[u] = v;
		}
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &pnt[i].x, &pnt[i].y);
	for (int u, v, cuv, cvu; m --; ) {
		scanf("%d%d%d%d", &u, &v, &cuv, &cvu);
		-- u, -- v;
		to[u].pb(v), cost[u].pb(cuv), used[u].pb(false);
		to[v].pb(u), cost[v].pb(cvu), used[v].pb(false);
	}
	for (int i = 0; i < n; ++ i) {
		int sz = to[i].size();
		to[i].resize(sz);
		cost[i].resize(sz);
		used[i].resize(sz);
		idx[i].resize(sz);
		ridx[i].resize(sz);
		for (int j = 0; j < sz; ++ j) idx[i][j] = -1, ridx[i][j] = -1;
	}
	for (int i = 0; i < n; ++ i) {
		int sz = to[i].size();
		for (int j = 0; j < sz; ++ j) if (!used[i][j]) {
			way.clear(), eid.clear();
			way.pb(i), eid.pb(j);
			if (Dfs(to[i][j], i, i)) {
				used[i][j] = true;
				int s = way.size();
				for (int k = 0; k < s; ++ k) {
					idx[way[k]][eid[k]] = cnt;
				}
				++ cnt;
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		int sz = to[i].size();
		for (int j = 0; j < sz; ++ j) {
			assert(used[i][j] == true);
			int k = to[i][j];
			int zs = to[k].size();
			for (int l = 0; l < zs; ++ l)
				if (to[k][l] == i) {
					ridx[i][j] = idx[k][l];
					break;
				}
		}
	}
	printf("%d\n", SpanningTree());
	return 0;
}
