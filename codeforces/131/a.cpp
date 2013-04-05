#include <cstdio>
#include <cstring>
#include <vector>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
int inDgr[222], dgrCp[222];
int n, c[222];
vector<int> adj[222];
bool over[222];

int calc(int x) {
	memset(over, false, sizeof(over));
	memcpy(inDgr, dgrCp, sizeof(dgrCp));
	int cur = x, ret = 0;
	while ( 1 ) {
		bool done = true;
		for ( int i = 1; i <= n; i ++ )
			done &= over[i];
		if ( done ) break;

		bool changed = true;
		while ( changed ) {
			changed = false;
			for ( int i = 1; i <= n; i ++ )
				if ( !over[i] && inDgr[i] == 0 && c[i] == cur ) {
					changed = true;
					over[i] = true;
					ret++;
					FOREACH(it, adj[i])
						inDgr[*it]--;
				}
		}

		done = true;
		for ( int i = 1; i <= n; i ++ )
			done &= over[i];
		if ( done ) break;

		ret ++;
		cur = (cur-1+1)%3+1;
	}
	return ret;
}

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &c[i]);
	for ( int i = 1; i <= n; i ++ ) {
		int k, x;
		scanf("%d", &k);
		while ( k -- ) {
			scanf("%d", &x);
			adj[x].push_back(i);
			inDgr[i]++;
		}
	}

	memcpy(dgrCp, inDgr, sizeof(inDgr));
	int ans = calc(1);
	for ( int i = 2; i <= 3; i ++ )
		ans = min(ans, calc(i));
	printf("%d\n", ans);
}
