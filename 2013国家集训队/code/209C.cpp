#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kVMax = 1000010;

vector<int> adj[kVMax];
int belong[kVMax], oddCnt[kVMax], stk[kVMax];
int dgr[kVMax];
int top, evenComp, compCnt;
bool vis[kVMax];

void bfs(int src, int comp) {
	static int Q[kVMax];
	int qt = 0;
	Q[qt++] = src;
	vis[src] = true;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		belong[u] = comp;
		foreach(it, adj[u]) {
			int v = *it;
			if ( !vis[v] ) {
				vis[v] = true;
				Q[qt++] = v;
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	while ( m -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
		dgr[a]++, dgr[b]++;
	}
	for ( int i = 1; i <= n; i ++ )
		if ( dgr[i] && !vis[i] ) 
			bfs(i, ++compCnt);
	for ( int i = 1; i <= n; i ++ )
		if ( dgr[i] ) {
			if ( dgr[i] & 1 ) 
				oddCnt[belong[i]]++;
		}
	for ( int i = 1; i <= compCnt; i ++ )
		if ( oddCnt[i] == 0 ) 
			evenComp++;
		else
			stk[top++] = oddCnt[i];
	if ( dgr[1] == 0 )
		evenComp++;
	sort(stk, stk+top);
	int ans = 0;
	while ( top > 1 ) {
		int x = stk[top-1], y = stk[top-2];
		ans++;
		if ( x+y-2 == 0 ) {
			top -= 2;
			evenComp++;
		} else {
			top--;
			stk[top-1] = x+y-2;
		}
	}
	if ( top ) {
		assert(stk[0] % 2 == 0);
		ans += (stk[0]-2)/2 + evenComp+1;
	} else
		ans += evenComp==1?0:evenComp;
	printf("%d\n", ans);
}
