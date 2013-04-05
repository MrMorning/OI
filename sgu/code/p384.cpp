#include <cstdio>
#include <algorithm>
using namespace std;
const int kNMax = 100010;
const int kMMax = 2*kNMax;

int n, m;
pair<int, int> edge[kMMax];
int dgr[kNMax], another[kNMax], toRoot[kNMax], bridge[kNMax];
bool del[kMMax];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= m; i ++ ) {
		scanf("%d%d", &edge[i].first, &edge[i].second);
		dgr[edge[i].first]++;
		dgr[edge[i].second]++;
	}
	int root = -1;
	for ( int i = 1; i <= n; i ++ )
		if ( root == -1 || dgr[root] < dgr[i] )
			root = i;
	for ( int i = 1; i <= m; i ++ ) {
		int u = edge[i].first, v = edge[i].second;
		if ( u != root && v != root ) {
			another[u] = v;
			another[v] = u;
			bridge[u] = bridge[v] = i;
		} else if ( u == root ) 
			toRoot[v] = i;
		else 
			toRoot[u] = i;
	}

	static char cmd[10];
	while ( scanf("%s", cmd) != EOF ) {
		if ( cmd[0] == 'L' ) {
			int u, v;
			scanf("%d%d", &u, &v);
			if ( u == v ) puts("0");
			else if ( u == root || v == root ) {
				if ( u == root ) swap(u, v);
				if ( !del[toRoot[u]] ) puts("1");
				else if ( !del[toRoot[another[u]]] && !del[bridge[u]] ) puts("2");
				else puts("-1");
			} else if ( another[u] == v && !del[bridge[u]] ) puts("1");
			else {
				int ans1 = 0x3f3f3f3f, ans2 = 0x3f3f3f3f;
				if ( !del[toRoot[u]] )
					ans1 = min(ans1, 1);
				if ( !del[toRoot[another[u]]] && !del[bridge[u]] )
					ans1 = min(ans1, 2);
				if ( !del[toRoot[v]] )
					ans2 = min(ans2, 1);
				if ( !del[toRoot[another[v]]] && !del[bridge[v]] )
					ans2 = min(ans2, 2);
				if ( ans1 == 0x3f3f3f3f || ans2 == 0x3f3f3f3f )
					puts("-1");
				else
					printf("%d\n", ans1+ans2);
			}
		} else {
			int x;
			scanf("%d", &x);
			del[x] = true;
		}
	}
}
