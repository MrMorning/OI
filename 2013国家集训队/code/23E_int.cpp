#include <cstdio>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#define pb(x) push_back(x)
using namespace std;

const int kNMax = 705;
int f[kNMax], g[kNMax], h[kNMax], w[kNMax];
vector<int> adj[kNMax];
int nv;

void work(int x, int pa) {
	foreach(it, adj[x]) 
		if ( (*it) != pa ) 
			work(*it, x);
	int sz = (int)adj[x].size() - 1 + (pa == -1);
	g[0] = 1;
	for ( int i = 1; i <= sz; i++ )
		g[i] = 0;
	h[x] = 1;
	foreach(it, adj[x]) 
		if ( (*it) != pa ) {
			int acc = 1;
			foreach(it2, adj[x])
				if ( (*it2) != pa && (*it2) != (*it) )
					acc *= f[*it2];
			f[x] = max(f[x], acc * w[*it]);
			h[x] *= f[*it];
			for ( int j = sz; j >= 0; j -- ) {
				g[j] = g[j]*f[*it];
				if ( j >= 1 ) 
					g[j] = max(g[j], g[j-1]*h[*it]);
			}
		}
	for ( int j = 0; j <= sz; j ++ ) {
		f[x] = max(f[x], g[j]*(j+1));
		w[x] = max(w[x], g[j]*(j+2));
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	for ( int i = 0; i < nv-1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b); adj[b].pb(a);
	}
	work(1, -1);
	printf("%d\n", f[1]);
}
