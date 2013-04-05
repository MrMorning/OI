#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
typedef long long ll;
const int kEdMax = 50010, kNdMax = 210;
struct Edge {
	int x, y, g, s;
} ed[kEdMax];
bool cmpG(const Edge &e1, const Edge &e2) {
	return e1.g<e2.g;
}
int n, m, G, S;
int parent[kNdMax];
vector<pair<int, int> > adj[kNdMax];
bool vis[kNdMax];
int prev[kNdMax], edpre[kNdMax];
int path[kNdMax], pathL;
int curS, curG;

int find(int i) {
	return parent[i] == i ? i : parent[i] = find(parent[i]);
}
void merge(int i, int j) {
	parent[find(i)] = find(j);
}
void dfs(int x) {
	vis[x] = true;
	foreach(it, adj[x]) {
		int y = it->first;
		if ( vis[y] ) continue;
		prev[y] = x;
		edpre[y] = it->second;
		dfs(y);
	}
}
void dfs2(int x) {
	vis[x] = true;
	foreach(it, adj[x]) {
		int y = it->first;
		if ( vis[y] ) continue;
		curG = max(curG, ed[it->second].g);
		curS = max(curS, ed[it->second].s);
		dfs2(y);
	}
}

void getPath(int start, int end) {
	memset(vis, 0, sizeof(vis));
	memset(prev, 0, sizeof(prev));
	memset(edpre, 0, sizeof(edpre));
	dfs(start);
	int cur = end;
	pathL = 0;
	while ( edpre[cur] ) {
		path[pathL++] = edpre[cur];
		cur = prev[cur];
	}
}

bool connected() {
	for ( int i = 1; i <= n; i ++ )
		if ( find(i) != find(1) ) return false;
	return true;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		parent[i] = i;
	scanf("%d%d", &G, &S);
	for ( int i = 1; i <= m; i ++ )
		scanf("%d%d%d%d", &ed[i].x, &ed[i].y, &ed[i].g, &ed[i].s);
	sort(ed+1,ed+1+m, cmpG);
	ll ans = -1;
	for ( int i = 1; i <= m; i ++ ) {
		if ( find(ed[i].x) != find(ed[i].y) ) {
			merge(ed[i].x, ed[i].y);
			adj[ed[i].x].pb(make_pair(ed[i].y, i));
			adj[ed[i].y].pb(make_pair(ed[i].x, i));
		} else {
			getPath(ed[i].x, ed[i].y);
			int t = i;
			for ( int k = 0; k < pathL; k ++ )
				if ( ed[t].s < ed[path[k]].s ) 
					t = path[k];
			if ( t != i ) {
				foreach(it, adj[ed[t].x])
					if ( it->first == ed[t].y ) {
						adj[ed[t].x].erase(it);
						break;
					}
				foreach(it, adj[ed[t].y])
					if ( it->first == ed[t].x ) {
						adj[ed[t].y].erase(it);
						break;
					}
				adj[ed[i].x].pb(make_pair(ed[i].y, i));
				adj[ed[i].y].pb(make_pair(ed[i].x, i));
			}
		}

		if ( connected() )  {
			curG = curS = 0;
			memset(vis, 0, sizeof(vis));
			dfs2(1);
			ans = ans==-1?(ll)curG*G+(ll)curS*S:min(ans, (ll)curG*G+(ll)curS*S);
		}
	}
	cout << ans << '\n';
}
