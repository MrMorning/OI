#include <cstdio>
#include <vector>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
const int inf = 0x3f3f3f3f;
vector<int> adj[30005];
int N, K;
int tag[30005];
bool placed[30005];

void work(int x, int fa) {
	foreach(it, adj[x]) 
		if ( fa == *it ) {
			adj[x].erase(it);
			break;
		}
	if ( !adj[x].size() ) 
		tag[x] = K + 1;
	else {
		foreach(it, adj[x]) 
			work(*it, x);
		int mi = inf, mx = -inf;
		foreach(it, adj[x]) {
			mi = min(mi, tag[*it]);
			mx = max(mx, tag[*it]);
		}
		if ( mi + mx + 2 <= 2 * K + 1 ) 
			tag[x] = mi + 1;
		else {
			tag[x] = mx + 1;
			if ( tag[x] == 2 * K + 1 ) {
				placed[x] = true;
				tag[x] = 0;
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 0; i < N - 1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	work(1, 0);
	if ( tag[1] > K )
		placed[1] = true;
	int cnt = 0;
	for ( int i = 1; i <= N; i ++ )
		if ( placed[i] )
			cnt ++;
	printf("%d\n", cnt);
	for ( int i = 1; i <= N; i ++ )
		if ( placed[i] )
			printf("%d ", i);
}
