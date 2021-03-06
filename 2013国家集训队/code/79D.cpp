#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int kNMax = 10005;
int n, k, l;
int a[105], src[kNMax], des[kNMax];
int pos[22], nPos;
int f[1<<20], g[22][22];
int que[kNMax];
int dis[kNMax];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &k, &l);
	for ( int i = 0; i < k; i ++ ) {
		int x;
		scanf("%d", &x);
		src[x] = 1;
	}
	for ( int i = 0; i <= n; i ++ )
		des[i] = src[i+1] ^ src[i];
	for ( int i = 0; i < l; i ++ )
		scanf("%d", &a[i]);
	for ( int i = 0; i <= n; i ++ ) {
		if ( des[i] ) 
			pos[nPos++] = i;
	}
	for ( int i = 0; i < nPos; i ++ ) {
		memset(dis, -1, sizeof(dis));
		dis[pos[i]] = 0;
		int qt = 0;
		que[qt++] = pos[i];
		for ( int qh = 0; qh < qt; qh ++ ) {
			int u = que[qh];
			for ( int t = 0; t < l; t ++ ) {
				int v = u + a[t];
				if ( v <= n && dis[v]==-1 ) {
					dis[v] = dis[u] + 1;
					que[qt++] = v;
				}	
				v = u - a[t];
				if ( v >= 0 && dis[v]==-1 ) {
					dis[v] = dis[u] + 1;
					que[qt++] = v;
				}
			}
		}
		for ( int j = 0; j < nPos; j ++ )
			g[i][j] = dis[pos[j]];
	}
	int upperlim = 1 << nPos;
	f[0] = 0;
	for ( int s = 1; s < upperlim; s ++ ) {
		f[s] = -1;
		int t;
		for ( int i = 0; i < nPos; i ++ )
			if ( (s&(1<<i)) ) {
				t = i;
				break;
			}
		for ( int i = 0; i < nPos; i ++ )
			if ( i != t && (s&(1<<i)) ) {
				if ( f[s-(1<<i)-(1<<t)] != -1 && g[i][t] != -1 ) {
					int tmp = f[s-(1<<i)-(1<<t)]+g[i][t];
					f[s] = f[s]==-1?tmp:min(f[s],tmp);
				}
			}
	}
	printf("%d\n", f[upperlim-1]);
}
