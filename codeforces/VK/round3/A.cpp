
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

int N, M;
vector<int> adj[100010], inv[100010];
int f[100010], Q[100010];
bool can1[100010], can2[100010];

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for ( int i = 1; i <= N; i ++ ) 
		scanf("%d", &f[i]);
	while ( M -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		inv[b].push_back(a);
	}
	int qh = 0, qt = 0;
	for ( int i = 1; i <= N; i ++ ) 
		if ( f[i] == 1 ) {
			can1[i] = true;
			Q[qt ++] = i;
		}
	while ( qh < qt ) {
		int u = Q[qh ++];
		FOREACH(it, adj[u]) {
			int v = *it;
			if ( !can1[v] ) {
				can1[v] = true;
				Q[qt ++] = v;
			}
		}
	}

	qh = qt = 0;
	for ( int i = 1; i <= N; i ++ ) 
		if ( f[i] == 2 ) {
			can2[i] = true;
			Q[qt ++] = i;
		}

	while ( qh < qt ) {
		int u = Q[qh ++];
		FOREACH(it, inv[u]) {
			int v = *it;
			if ( !can2[v] ) {
				can2[v] = true;
				if ( f[v] != 1 )
					Q[qt ++] = v;
			}
		}
	}

	for ( int i = 1; i <= N; i ++ ) 
		printf("%d\n", can1[i] && can2[i]);
}
