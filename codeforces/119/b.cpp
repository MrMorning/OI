#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int kVtxMax = 66*66;

int n, m;
int e[66][66][66];
int f[66][66];
bool inQ[66][66];
pair<int, int> Q[kVtxMax];
int dist[66][66][66];


void expand(int src) {
	memset(dist[src], 0x3f, sizeof(dist[src]));
	memset(inQ, 0, sizeof(inQ));
	dist[src][src][0] = 0;
	int qh = 0, qt = 0;
	Q[qt++] = make_pair(src, 0);
	inQ[src][0] = true;
	while ( qh != qt ) {
		pair<int, int> u = Q[qh];
		qh = (qh + 1) % kVtxMax;
		inQ[u.first][u.second] = false;
		for ( int x = 0; x < m; x ++ ) {
			if ( u.second + 1 >= 60 ) continue;
			pair<int, int> v = make_pair(x, u.second + 1);
			int tmp = dist[src][u.first][u.second] + f[u.first][x];
			if ( dist[src][v.first][v.second] > tmp ) {
				dist[src][v.first][v.second] = tmp;
				if ( !inQ[v.first][v.second] ) {
					inQ[v.first][v.second] = true;
					Q[qt] = v;
					qt = (qt + 1) % kVtxMax;
				}
			}
		}
	}
}

int main() {
	int r;
	scanf("%d%d%d", &m, &n, &r);
	memset(f, 0x3f, sizeof(f));
	for ( int i = 0; i < n; i ++ ) {
		for ( int j = 0; j < m; j ++ )
			for ( int k = 0; k < m; k ++ )
				scanf("%d", &e[i][j][k]);
		for ( int k = 0; k < m; k ++ )
			for ( int ii = 0; ii < m; ii ++ )
				for ( int jj = 0; jj < m; jj ++ )
					e[i][ii][jj] = min(e[i][ii][jj], e[i][ii][k] + e[i][k][jj]);
		for ( int ii = 0; ii < m; ii ++ )
			for ( int jj = 0; jj < m; jj ++ )
				f[ii][jj] = min(f[ii][jj], e[i][ii][jj]);
	}
	for ( int i = 0; i < m; i ++ )
		expand(i);
	while ( r -- ) {
		int s, t, k;
		scanf("%d%d%d", &s, &t, &k);
		k++;
		s--, t--;
		k = min(k, 59);
		int ans = 0x3f3f3f3f;
		for ( int p = 0; p <= k; p ++ )
			ans = min(ans, dist[s][t][p]);
		printf("%d\n", ans);
	}
}
