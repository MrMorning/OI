
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}
const int kPointMax = 1510;
struct Point {
	int x, y, id;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
} p[kPointMax], stp;
int size[kPointMax], match[kPointMax];
vector<int> adj[kPointMax], son[kPointMax];

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

ll cross(const Point &p1, const Point &p2) {
	return (ll)p1.x * p2.y - (ll)p1.y * p2.x;
}

bool cmpP(const Point &p1, const Point &p2) {
	return cross(p1 - stp, p2 - stp) > 0;
}

void dfs(int x, int fa) {
	size[x] = 1;
	FOREACH(it, adj[x])
		if ( *it != fa ) {
			son[x].push_back(*it);
			dfs(*it, x);
			size[x] += size[*it];
		}
}

void solve(int cur, int l, int r) {
	assert(size[cur] == r - l + 1);
	int best = -1;
	for ( int k = l; k <= r; k ++ ) {
		if ( best == -1 || p[best].x > p[k].x || (p[best].x == p[k].x && p[best].y > p[k].y) ) 
			best = k;
	}
	match[p[best].id] = cur;
	stp = p[best];
	swap(p[l], p[best]);
	sort(p + l + 1, p + r + 1, cmpP);
	int ptr = l + 1;
	FOREACH(it, son[cur]) {
		int y = *it;
		solve(y, ptr, ptr + size[y] - 1);
		ptr += size[y];
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for ( int i = 0; i < n - 1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].id = i;
	}
	int root = 1;
	dfs(root, 0);
	solve(root, 0, n - 1);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", match[i]);
}
