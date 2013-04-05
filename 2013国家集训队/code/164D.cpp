#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
const int kNMax = 1005;
int sqr(int x) { return x * x; }
struct Triple {
	int a, b, d;
	Triple(){}
	Triple(int aa, int bb, int dd):
		a(aa), b(bb), d(dd){}
	bool operator< (const Triple &T) const {
		return d < T.d;
	}
} arr[kNMax*kNMax];
struct Edge {
	int to;
	Edge *next;
} edge[kNMax*kNMax], *begin[kNMax];
int edgeCnt = 0;
void addEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], begin[u] = e;
}
int dist[kNMax][kNMax];
int del[kNMax], nDel;
int tmp[kNMax], nTmp;
int match[kNMax];
bool vis[kNMax], elim[kNMax], ban[kNMax], chosen[kNMax];
int n, m;
int x[kNMax], y[kNMax];
int pos[kNMax];
int nArr;

int calcDiameter() {
	int res = 0;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ )
			if ( !elim[i] && !elim[j] )
				res = max(res, dist[i][j]);
	return res;
}

bool aug(int x) {
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( !vis[y] && !ban[y] ) {
			vis[y] = true;
			if ( match[y] == -1 || aug(match[y]) ) {
				match[y] = x;
				match[x] = y;
				return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	if ( n == m+1 ) {
		for ( int i = 1; i < n; i ++ )
			printf("%d ", i);
		return 0;
	}
	for ( int i = 1; i <= n; i ++ )
		scanf("%d%d", &x[i], &y[i]);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ )
			dist[i][j] = sqr(x[i]-x[j])+sqr(y[i]-y[j]);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j < i; j ++ )
			arr[nArr++] = Triple(i, j, dist[i][j]);
	sort(arr, arr+nArr);
	int cnt = 1;
	for ( int i = n; i > n-m; i -- )
		cnt += i-1;
	for ( int i = max(0, nArr-cnt); i < nArr; i ++ ) {
		int a = arr[i].a, b = arr[i].b, d = arr[i].d;
		nDel = 0, nTmp = 0;
		memset(pos, -1, sizeof(pos));
		for ( int j = 1; j <= n; j ++ )
			if ( j != a && j != b ) {
				int da = dist[a][j], db = dist[b][j];
				if ( da <= d && db <= d ) {
					pos[j] = nTmp;
					tmp[nTmp++] = j;
				} else del[nDel++] = j;
			}
		if ( nDel > m ) continue;
		edgeCnt = 0;
		memset(begin, 0, sizeof(begin[0])*nTmp);
		for ( int j = i+1; j < nArr; j ++ ) {
			int u = arr[j].a, v = arr[j].b;
			if ( pos[u] != -1 && pos[v] != -1 )
				addEdge(pos[u], pos[v]); addEdge(pos[v], pos[u]);
		}
		memset(match, -1, sizeof(match[0])*nTmp);
		int nMatch = 0;
		for ( int j = 0; j < nTmp; j ++ ) 
			if ( match[j] == -1 ) {
				for ( Edge *e = begin[j]; e; e = e->next ) {
					if ( match[e->to] == -1 ) {
						match[j] = e->to;
						match[e->to] = j;
						nMatch++;
						break;
					}
				}
			}

		for ( int j = 0; j < nTmp; j ++ ) 
			if ( match[j] == -1 ) {
				memset(vis, 0, sizeof(vis[0])*nTmp);
				if ( aug(j) )
					nMatch++;
			}
		if ( nMatch+nDel > m ) continue;

		//find answer

		for ( int j = 0; j < nTmp && nDel < m; j ++ )
			if ( match[j] != -1 ) {
				static int backup[kNMax];
				memcpy(backup, match, sizeof(match[0])*nTmp);
				match[match[j]] = -1;
				ban[j] = true;
				memset(vis, 0, sizeof(vis[0])*nTmp);
				if ( !aug(match[j]) ) {
					del[nDel++] = tmp[j];
					chosen[j] = true;
				} else {
					ban[j] = false;
					memcpy(match, backup, sizeof(match[0])*nTmp);
				}
			}

		for ( int j = 0; j < nTmp && nDel < m; j ++ )
			if ( !chosen[j] )
				del[nDel++] = tmp[j];

		break;
	}
	for ( int i = 0; i < nDel; i ++ )
		printf("%d ", del[i]);
}
