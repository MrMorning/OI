#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
const int WIDTH = 555;
const int EDGE_MAX = 2000000;


int n, m, bound;
int belong[WIDTH][WIDTH];
char board[WIDTH][WIDTH];
int colIdx = 0;
int weight[WIDTH * WIDTH];
int low[WIDTH * WIDTH], dfn[WIDTH * WIDTH];
bool isCut[WIDTH * WIDTH];

struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):x(_x), y(_y){}
	bool valid() {
		return 0 <= x && x < n && 0 <= y && y < m;
	}
	Point walk(int dir) {
		return Point(x + dx[dir], y + dy[dir]);
	}
};

struct Edge {
	int to;
	Edge *next, *inv;
} edge[EDGE_MAX], *begin[WIDTH * WIDTH];
int edgeCnt = 0;

Edge *makeEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	return begin[u] = e;
}

void addEdge(int u, int v) {
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inv = e2, e2->inv = e1;
}

void tarjan(int x, Edge *pe) {
	static int timeStamp = 0;
	dfn[x] = low[x] = timeStamp ++;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( e->inv != pe ) {
			int y = e->to;
			if ( dfn[y] == -1 ) {
				tarjan(y, e);
				low[x] = min(low[x], low[y]);
			} else if ( dfn[y] < dfn[x] ) 
				low[x] = min(low[x], dfn[y]);
		}
}

void color(int sx, int sy, int col) {
	static Point Q[WIDTH * WIDTH];
	int qt = 0;
	belong[sx][sy] = col;
	Q[qt ++] = Point(sx, sy);
	for ( int qh = 0; qh < qt; qh ++ ) {
		Point u = Q[qh];
		for ( int dir = 0; dir < 4; dir ++ ) {
			Point v = u.walk(dir);
			if ( v.valid() && belong[v.x][v.y] == -1 && board[v.x][v.y] == board[u.x][u.y]) {
				belong[v.x][v.y] = col;
				Q[qt ++] = v;
			}
		}
	}
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &bound);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%s", board[i]);
	memset(belong, -1, sizeof(belong));
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ ) 
			if ( belong[i][j] == -1 ) 
				color(i, j, colIdx++);
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ ) {
			Point p(i, j);
			weight[belong[i][j]] ++;
			for ( int dir = 0; dir < 2; dir ++ ) {
				Point q = p.walk(dir);
				if ( !q.valid() )
					continue;
				if ( belong[q.x][q.y] != belong[p.x][p.y] )
					addEdge(belong[p.x][p.y], belong[q.x][q.y]);
			}
		}
	for ( int i = 0; i < n; i ++ ) {
		addEdge(belong[i][0], colIdx);
		addEdge(belong[i][m - 1], colIdx);
	}
	for ( int i = 0; i < m; i ++ ) {
		addEdge(belong[0][i], colIdx);
		addEdge(belong[n - 1][i], colIdx);
	}

	memset(dfn, -1, sizeof(dfn));
	tarjan(colIdx, NULL);

/*	static int Q[WIDTH * WIDTH];
	static bool vis[WIDTH * WIDTH];
	int qt = 0;
	Q[qt++] = colIdx;
	vis[colIdx] = true;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		for ( Edge *e = begin[u]; e; e = e->next ) {
			int v = e->to;
			if ( vis[v] || (weight[v] >= bound && isCut[v]) )
				continue;
			vis[v] = true;
			Q[qt ++] = v;
		}
	}*/
	int ans = 0;
	for ( int i = 0; i < colIdx; i ++ )
		if ( low[i] != dfn[colIdx] && weight[i] < bound ) 
			ans += weight[i];
	for ( int i = 0; i < colIdx; i ++ )
		if ( weight[i] >= bound )
			ans += weight[i];
	printf("%d\n", ans);
}
