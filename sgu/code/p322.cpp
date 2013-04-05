#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

const int VTX_MAX = 2010;

bool vis[VTX_MAX];
bool e1[VTX_MAX][VTX_MAX], e2[VTX_MAX][VTX_MAX];
int pre[VTX_MAX];
int n;
vector<int> adj[VTX_MAX];

struct Output {
	int u, v, p, q;
	Output(){}
	Output(int _u, int _v, int _p, int _q):
		u(_u), v(_v), p(_p), q(_q){}
} out[VTX_MAX];
int nOut = 0;

void dfs(int x) {
	vis[x] = true;
	foreach(it, adj[x]) 
		if ( !vis[*it] ) {
			pre[*it] = x;
			dfs(*it);
		}
}

void findSeq(int *seq, int &seqCnt, int u, int v) {
	memset(vis, 0, sizeof(vis));
	dfs(u);
	seqCnt = 0;
	for ( int x = v; ; x = pre[x] ) {
		seq[seqCnt++] = x;
		if ( x == u )
			break;
	}
	reverse(seq, seq + seqCnt);
}

int main() {
	scanf("%d", &n);
	for ( int i = 0; i < n - 1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a --, b --;
		e1[a][b] = e1[b][a] = true;
	}
	for ( int i = 0; i < n - 1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a --, b --;
		e2[a][b] = e2[b][a] = true;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for ( int u = 0; u < n; u ++ )
		for ( int v = u + 1; v < n; v ++ )
			if ( e1[u][v] && !e2[u][v] ) {
				static int seq[VTX_MAX];
				int seqCnt = 0;
				findSeq(seq, seqCnt, u, v);
				for ( int k = 0; k < seqCnt - 1; k ++ ) {
					int p = seq[k], q = seq[k + 1];
					assert(e2[p][q]);
					if ( !e1[p][q] ) {
						e2[p][q] = e2[q][p] = false;
						foreach(it, adj[p]) 
							if ( *it == q ) {
								adj[p].erase(it);
								break;
							}
						foreach(it, adj[q]) 
							if ( *it == p ) {
								adj[q].erase(it);
								break;
							}
						adj[u].push_back(v);
						adj[v].push_back(u);
						e2[u][v] = e2[v][u] = true;

						out[nOut++] = Output(u, v, p, q);
						break;
					}
				}
			}
	printf("%d\n", nOut);
	for ( int i = 0; i < nOut; i ++ )
		printf("2 %d %d %d %d\n", 
				out[i].u + 1, out[i].v + 1, out[i].p + 1, out[i].q + 1);
}
