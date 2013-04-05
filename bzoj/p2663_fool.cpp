#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

bool adj[55][55], vis[55];
int match[55];
int N, K;
double dist[55][55];

struct Point {
	int x, y;
} fairy[55], stone[55];

inline double sqr(double x) { return x * x; }

double calc_dist(const Point &p1, const Point &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

bool dfs(int x) {
	for ( int y = 1; y <= N; y ++ )
		if ( adj[x][y] && !vis[y] ) {
			vis[y] = true;
			if ( match[y] == -1 || dfs(match[y]) ) {
				match[y] = x;
				return true;
			}
		}	
	return false;
}

int solve(double rad) {
	memset(adj, 0, sizeof(adj));
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ )
			if ( dist[i][j] < rad )
				adj[i][j] = 1;
	memset(match, -1, sizeof(match));

	int res = 0;
	for ( int i = 1; i <= N; i ++ ) {
		memset(vis, 0, sizeof(vis));
		res += dfs(i);
	}
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
		if ( solve(mid) < K )
			lb = mid;
		else
			rb = mid;
	}

	printf("%.2lf", lb);

	lb = 0, rb = farthest + 1;

	for ( int cnt = 0; cnt < 100; cnt ++ ) {
		double mid = (lb + rb) / 2;
		if ( solve(mid) > K )
			rb = mid;
		else
			lb = mid;
	}

	if ( rb > farthest )
		printf(" +INF\n");
	else
		printf(" %.2lf\n", rb);
}
