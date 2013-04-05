#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>
#define INDEPENDENT 0
#define BRANCH 1
using namespace std;

const int kNMax = 17;
const int kVMax = kNMax*kNMax;
const int kInf = 0x3f3f3f3f;
const int kDx[4] = {0, 0, -1, 1};
const int kDy[4] = {1, -1, 0, 0};

struct Point {
	int x, y;
	Point(){}
	Point(int xx, int yy):
		x(xx), y(yy){}
	bool operator== (const Point &p1) const {
		return x == p1.x && y == p1.y;
	}
	bool operator!= (const Point &p1) const {
		return !((*this)==p1);
	}
	bool inRange();
};

struct DisjointSet {
	Point p[kNMax][kNMax];
	Point find(Point u) {
		return p[u.x][u.y]==u?u:p[u.x][u.y]=find(p[u.x][u.y]);
	}
	void merge(Point u, Point v) {
		p[find(u).x][find(u).y] = find(v);
	}
} ds;

int dist[kNMax][kNMax][kNMax][kNMax];
int toEdge[kNMax][kNMax];
Point toEdgeMemo[kNMax][kNMax];
int toCrater[kNMax][kNMax][kNMax][kNMax];
Point toCraterMemo[kNMax][kNMax][kNMax][kNMax];
int n, m;
char bd[kNMax][kNMax], out[kNMax][kNMax];
vector<Point> list[kNMax][kNMax];

bool Point::inRange() {
	return 1 <= x && x <= n && 1 <= y && y <= m;
}

Point move(Point src, int dir) {
	return Point(src.x+kDx[dir], src.y+kDy[dir]);
}

void paint(Point src, Point des) {
	static Point Q[kVMax], prev[kNMax][kNMax];
	static int dist[kNMax][kNMax];
	memset(dist, 0x3f, sizeof(dist));
	int qt = 0;
	Q[qt++] = src;
	for ( int qh = 0; qh < qt; qh ++ ) {
		Point u = Q[qh];
		for ( int dir = 0; dir < 4; dir ++ ) {
			Point v = move(u, dir);
			if ( v.inRange() 
					&& dist[v.x][v.y] == kInf ) {
				dist[v.x][v.y] = dist[u.x][u.y]+1;
				prev[v.x][v.y] = u;
				if ( bd[v.x][v.y] == '.' )
					Q[qt++] = v;
			}
		}
	}
	assert(dist[des.x][des.y] != kInf);
	Point cur = des;
	do {
		if ( bd[cur.x][cur.y] == '.' )
			out[cur.x][cur.y] = '*';
		cur = prev[cur.x][cur.y];
	} while ( cur != src ) ;
	if ( bd[src.x][src.y] == '.' )
		out[src.x][src.y] = '*';
}

Point curStd;
bool cmpToCrater(const Point &p1, const Point &p2) {
	return toCrater[curStd.x][curStd.y][p1.x][p1.y] < 
		toCrater[curStd.x][curStd.y][p2.x][p2.y];
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			ds.p[i][j] = Point(i, j);
	for ( int i = 1; i <= n; i ++ ) 
		scanf("%s", bd[i]+1);

	memset(dist, 0x3f, sizeof(dist));
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			static Point Q[kVMax];
			int qt = 0;
			Q[qt++] = Point(i, j);
			dist[i][j][i][j] = 0;
			for ( int qh = 0; qh < qt; qh ++ ) {
				Point u = Q[qh];
				for ( int dir = 0; dir < 4; dir ++ ) {
					Point v = move(u, dir);
					if ( v.inRange()  
							&& dist[i][j][v.x][v.y] == kInf ) {
						dist[i][j][v.x][v.y] = dist[i][j][u.x][u.y]+1;
						if ( bd[v.x][v.y] == '.' )
							Q[qt++] = v;
					}
				}
			}
		}

	memset(toEdge, 0x3f, sizeof(toEdge));
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( i == 1 || i == n || j == 1 || j == m )
				if ( bd[i][j] == '.' ) 
					for ( int k = 1; k <= n; k ++ )
						for ( int l = 1; l <= m; l ++ ) {
							if ( toEdge[k][l] > dist[k][l][i][j] ) {
								toEdge[k][l] = dist[k][l][i][j];
								toEdgeMemo[k][l] = Point(i, j);
							}
						}

	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j < m; j ++ )
			if ( bd[i][j] == 'X' && bd[i][j+1] == 'X' )
				ds.merge(Point(i, j), Point(i, j+1));
	for ( int i = 1; i < n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( bd[i][j] == 'X' && bd[i+1][j] == 'X' )
				ds.merge(Point(i, j), Point(i+1, j));

	int ansVal = kInf, ansType;
	Point ansP, ansQ, ansR;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( bd[i][j] == 'X' && toEdge[i][j] != kInf )
				for ( int k = 1; k <= n; k ++ )
					for ( int l = 1; l <= m; l ++ )
						if ( bd[k][l] == 'X' && ds.find(Point(i, j)) != ds.find(Point(k, l)) 
								&& toEdge[k][l] != kInf ) {
							int tmp = toEdge[i][j] + toEdge[k][l];
							if ( tmp < ansVal ) {
								ansVal = tmp;
								ansType = INDEPENDENT;
								ansP = Point(i, j), ansQ = Point(k, l);
							}
						}

	memset(toCrater, 0x3f, sizeof(toCrater));
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) 
			if ( bd[i][j] == '.' && toEdge[i][j] != kInf ) {
				for ( int k = 1; k <= n; k ++ )
					for ( int l = 1; l <= m; l ++ )
						if ( bd[k][l] == 'X' ) {
							int &res = toCrater[i][j][ds.find(Point(k, l)).x][ds.find(Point(k, l)).y];
							if ( dist[i][j][k][l] < res ) {
								res = dist[i][j][k][l];
								toCraterMemo[i][j][ds.find(Point(k, l)).x][ds.find(Point(k, l)).y] = Point(k, l);
							}

							if ( ds.find(Point(k, l)) == Point(k, l) ) 
								list[i][j].push_back(Point(k, l));
						}
				if ( (int)list[i][j].size() < 2 ) continue;
				curStd = Point(i, j);
				sort(list[i][j].begin(), list[i][j].end(), cmpToCrater);

				Point p = list[i][j][0], q = list[i][j][1];

				int tmp = toEdge[i][j] + toCrater[i][j][p.x][p.y]
					+ toCrater[i][j][q.x][q.y] - 1;
				if ( tmp < ansVal ) {
					ansVal = tmp;
					ansType = BRANCH;
					ansP = Point(i, j), ansQ = p, ansR = q;
				}
			}

	fprintf(stderr, "%d\n", ansVal);
	memcpy(out, bd, sizeof(bd));
	if ( ansType == INDEPENDENT ) {
		paint(ansP, toEdgeMemo[ansP.x][ansP.y]);
		paint(ansQ, toEdgeMemo[ansQ.x][ansQ.y]);
	} else {
		paint(ansP, toEdgeMemo[ansP.x][ansP.y]);
		paint(ansP, toCraterMemo[ansP.x][ansP.y][ansQ.x][ansQ.y]);
		paint(ansP, toCraterMemo[ansP.x][ansP.y][ansR.x][ansR.y]);
	}
	for ( int i = 1; i <= n; i ++ )
		printf("%s\n", out[i]+1);
}
