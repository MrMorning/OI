
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
const int kVtxMax = 200010;
vector<int> adj[kVtxMax];
bool okay[kVtxMax];
int height[kVtxMax], dist[kVtxMax];
char wallL[kVtxMax], wallR[kVtxMax];
int n, delta;
int Q[kVtxMax];

void addEdge(int u, int v) {
	adj[u].push_back(v);
}

int main(){
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &delta);
	scanf("%s%s", wallL, wallR);
	for ( int i = 0; i < n; i ++ ) {
		okay[i] = wallL[i] == '-';
		okay[i+n] = wallR[i] == '-';
		height[i] = height[i+n] = i;
		if ( i < n ) {
			addEdge(i, i + 1);
			addEdge(n + i, n + i + 1);
		}
		if ( i > 0 ) {
			addEdge(i, i - 1);
			addEdge(n + i, n + i - 1);
		}
		if ( i + delta < n ) {
			addEdge(i, i + n + delta);
			addEdge(i + n, i + delta);
		}
	}
	memset(dist, -1, sizeof(dist));
	dist[0] = 0;
	int qt = 0;
	Q[qt++] = 0;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		if ( !okay[u] || dist[u] > height[u] ) continue;
		FOREACH(it, adj[u]) {
			int v = *it;
			if ( dist[v] != -1 ) continue;
			dist[v] = dist[u] + 1;
			Q[qt++] = v;
		}
	}
	for ( int i = 0; i < 2 * n; i ++ )
		if ( okay[i] && dist[i] != -1 && dist[i] <= height[i] 
				&& height[i] + delta >= n ) {
			puts("YES");
			return 0;
		}
	puts("NO");
}
