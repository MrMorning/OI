#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
const int VTX_MAX = 10010;
const int inf = VTX_MAX;
int N, M, NA, NB;
vector<int> adj[VTX_MAX], memo;
int kind[VTX_MAX], dist[VTX_MAX], que[VTX_MAX];
vector<vector<int> > out;
bool vis[VTX_MAX], done[VTX_MAX];

bool dfs(int x, int rest) {
	assert(!vis[x]);
	vis[x] = true;
	if ( rest == 0 ) {
		if ( kind[x] == 2 ) 
			return true;
		return false;
	}

	foreach(it, adj[x]) {
		int y = *it;
		if ( !vis[y] && dist[y] == dist[x] + 1 ) {
			memo.push_back(y);
			if ( dfs(y, rest - 1) )
				return true;
			memo.pop_back();
		}
	}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	while ( M -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	scanf("%d", &NA);
	for ( int i = 1; i <= NA; i ++ ) {
		int x;
		scanf("%d", &x);
		kind[x] = 1;
	}
	scanf("%d", &NB);
	for ( int i = 1; i <= NB; i ++ ) {
		int x;
		scanf("%d", &x);
		kind[x] = 2;
	}

	memset(dist, -1, sizeof(dist));
	int tail = 0;
	for ( int i = 1; i <= N; i ++ )
		if ( kind[i] == 1 ) {
			que[tail++] = i;
			dist[i] = 0;
		}
	for ( int head = 0; head < tail; head ++ ) {
		int x = que[head];
		foreach(it, adj[x]) {
			int y = *it;
			if ( dist[y] == -1 ) {
				dist[y] = dist[x] + 1;
				que[tail++] = y;
			}
		}
	}

	int des = inf;
	for ( int i = 1; i <= N; i ++ )
		if ( kind[i] == 2 && dist[i] != -1 )
			des = min(des, dist[i]);

	memset(vis, 0, sizeof(vis));
	for ( int i = 1; i <= N; i ++ ) 
		if ( kind[i] == 1 ) {
			memo.push_back(i);
			if ( dfs(i, des) ) {
				out.push_back(memo);
				assert((int)memo.size() == des + 1);
			}
			memo.clear();
		}

	printf("%d %d\n", (int)out.size(), des);
	foreach(path, out) {
		foreach(it, *path) {
			printf("%d ", *it);
			assert(!done[*it]);
			done[*it] = true;
		}
		printf("\n");
	}
}
