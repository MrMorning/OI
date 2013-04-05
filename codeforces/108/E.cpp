#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> pair_t;
const int offset[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
const int Q_MAX = 222;
const int inf = 0x3f3f3f3f;
int n, m, n_imp, imp_arr[222];
int cost[222][222];
int f[222][222], g[222][222];
int h[222][222];
bool inQ[222];
int Q[222];
pair_t w[222][222];
char out[222][222];

int count_bits(int x) {
	int ret = 0;
	while ( x ) {
		ret += (x & 1) > 0;
		x >>= 1;
	}
	return ret;
}

void paint_dist(int i, int j) {
	if ( i == j )
		out[i / m][i % m] = 'X';
	else {
		int mid = g[i][j];
		if ( mid == -1 ) {
			out[i / m][i % m] = 'X';
			out[j / m][j % m] = 'X';
			return;
		}
		out[mid / m][mid % m] = 'X';
		paint_dist(i, mid);
		paint_dist(mid, j);
	}
}

void paint_h(int i, int s) {
	if ( w[i][s].first == 0 ) {
		paint_h(i, w[i][s].second);
		paint_h(i, s - w[i][s].second);
	} else if ( w[i][s].first == 1 ) {
		int tx = w[i][s].second / m,
			ty = w[i][s].second % m;
		paint_dist(tx * m + ty, i);
		paint_h(tx * m + ty, s);
	} else {
		if ( s == 0 )
			return;
		else if ( count_bits(s) == 1 ) {
			out[i / m][i % m] = 'X';
		} else
			assert(0);
	}
}

int main() {
	//freopen("t.in", "r", stdin);
	memset(g, -1, sizeof(g));
	memset(w, -1, sizeof(w));
	scanf("%d%d%d", &n, &m, &n_imp);
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ )
			scanf("%d", &cost[i][j]);
	memset(f, 0x3f, sizeof(f));
	for ( int i = 0; i < n * m; i ++ )
		f[i][i] = 0;
	for ( int i = 0; i < n; i ++ ) 
		for ( int j = 0; j < m; j ++ ) {
			for ( int dir = 0; dir < 4; dir ++ ) {
				int nx = i + offset[dir][0],
					ny = j + offset[dir][1];
				if ( 0 <= nx && nx < n )
					if ( 0 <= ny && ny < m )
						f[i * m + j][nx * m + ny] = cost[nx][ny];
			}
		}

	for ( int k = 0; k < n * m; k ++ )
		for ( int i = 0; i < n * m; i ++ )
			for ( int j = 0; j < n * m; j ++ ) {
				int tmp = f[i][k] + f[k][j];
				if ( tmp < f[i][j] ) {
					f[i][j] = tmp;
					g[i][j] = k;
				}
			}

	for ( int i = 0; i < n_imp; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		x --, y --;
		imp_arr[i] = x * m + y;
	}
	memset(h, 0x3f, sizeof(h));
	for ( int i = 0; i < n_imp; i ++ ) {
		int tx = imp_arr[i] / m,
			ty = imp_arr[i] % m;
		h[tx * m + ty][1 << i] = cost[tx][ty];
		for ( int nx = 0; nx < n; nx ++ )
			for ( int ny = 0; ny < m; ny ++ )
				if ( nx != tx || ny != ty ) {
					h[nx * m + ny][1 << i] = cost[tx][ty] + f[tx * m + ty][nx * m + ny];
					w[nx * m + ny][1 << i] = make_pair(1, tx * m + ty);
				}
	}
	for ( int s = 0, lim = 1 << n_imp; s < lim; s ++ ) 
		if ( count_bits(s) > 1 ) {
			for ( int x = 0; x < n; x ++ )
				for ( int y = 0; y < m; y ++ ) {
					int cur = x * m + y;
					for ( int ns = (s - 1) & s; ns; ns = (ns - 1) & s ) {
						int tmp = h[cur][ns] + h[cur][s - ns] - cost[x][y];
						if ( tmp < h[cur][s] ) {
							h[cur][s] = tmp;
							w[cur][s] = make_pair(0, ns);
						}
					}
				}
			//spfa
			memset(inQ, 0, sizeof(inQ));
			int qh = 0, qt = 0;
			for ( int x = 0; x < n; x ++ )
				for ( int y = 0; y < m; y ++ ) {
					Q[qt ++] = x * m + y;
					inQ[x * m + y] = true;
				}
			while ( qh != qt ) {
				int u = Q[qh];
				qh = (qh + 1) % Q_MAX;
				inQ[u] = false;
				int tx = u / m, ty = u % m;
				for ( int dir = 0; dir < 4; dir ++ ) {
					int nx = tx + offset[dir][0],
						ny = ty + offset[dir][1];
					if ( 0 <= nx && nx < n )
						if ( 0 <= ny && ny < m ) {
							int tmp = h[tx * m + ty][s] + f[tx * m + ty][nx * m + ny];
							if ( tmp < h[nx * m + ny][s] ) {
								h[nx * m + ny][s] = tmp;
								w[nx * m + ny][s] = make_pair(1, tx * m + ty);
								if ( !inQ[nx * m + ny] ) {
									inQ[nx * m + ny] = true;
									Q[qt] = nx * m + ny;
									qt = (qt + 1) % Q_MAX;
								}
							}
						}
				}
			}
		}

	int best_val = inf, best_pos = 0;
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ )
			if ( h[i * m + j][(1 << n_imp) - 1] < best_val ) {
				best_val = h[i * m + j][(1 << n_imp) - 1];
				best_pos = i * m + j;
			}
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ )
			out[i][j] = '.';
	paint_h(best_pos, (1 << n_imp) - 1);
	printf("%d\n", best_val);
	for ( int i = 0; i < n; i ++ )
		printf("%s\n", out[i]);
}
