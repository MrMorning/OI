#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int inf = 0x3f3f3f3f;

int adj[55][55], visX[55], visY[55], lx[55], ly[55];
int match[55], slk[55];
int N, K;
int VIS_TAG = 0;
double dist[55][55];

struct Point {
	int x, y;
} fairy[55], stone[55];

inline double sqr(double x) { return x * x; }

double calc_dist(const Point &p1, const Point &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

bool dfs(int x) {
	visX[x] = VIS_TAG;
	for ( int y = 1; y <= N; y ++ ) {
		if ( visY[y] == VIS_TAG )
			continue;
		int t = lx[x] + ly[y] - adj[x][y];
		if ( t == 0 ) {
			visY[y] = VIS_TAG;
			if ( match[y] == -1 || dfs(match[y]) ) {
				match[y] = x;
				return true;
			}
		} else
			slk[y] = min(slk[y], t);
	}
	return false;
}

int solve(double rad, int val) {

	memset(adj, 0, sizeof(adj));
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ )
			if ( dist[i][j] < rad )
				adj[i][j] = val;
	for ( int i = 1; i <= N; i ++ ) {
		match[i] = -1;
		lx[i] = -inf;
		ly[i] = 0;
		for ( int j = 1; j <= N; j ++ )
			lx[i] = max(lx[i], adj[i][j]);
	}

	for ( int i = 1; i <= N; i ++ ) {
		for (;;) {
			for ( int j = 1; j <= N; j ++ )
				slk[j] = inf;
			VIS_TAG ++;
			if ( dfs(i) ) break;
			int delta = inf;
			for ( int j = 1; j <= N; j ++ )
				if ( visY[j] != VIS_TAG )
					delta = min(delta, slk[j]);
			for ( int j = 1; j <= N; j ++ ) {
				if ( visX[j] == VIS_TAG )
					lx[j] -= delta;
				if ( visY[j] == VIS_TAG )
					ly[j] += delta;
			}
		}
	}

	int res = 0;
	for ( int i = 1; i <= N; i ++ )
		res += lx[i] + ly[i];

	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d%d", &fairy[i].x, &fairy[i].y);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d%d", &stone[i].x, &stone[i].y);
	double farthest = 0;
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ ) {
			dist[i][j] = calc_dist(fairy[i], stone[j]);
			farthest = max(farthest, dist[i][j]);
		}
	double lb = 0, rb = farthest;

	for ( int cnt = 0; cnt < 100; cnt ++ ) {
		double mid = (lb + rb) / 2;
		if ( solve(mid, 1) >= K )
			rb = mid;
		else
			lb = mid;
	}

	printf("%.2lf", lb);

	lb = 0, rb = farthest + 1;

	for ( int cnt = 0; cnt < 100; cnt ++ ) {
		double mid = (lb + rb) / 2;
		if ( -solve(mid, -1) <= K )
			lb = mid;
		else
			rb = mid;
	}

	if ( rb > farthest + 0.5 )
		printf(" +INF\n");
	else
		printf(" %.2lf\n", rb);
}
