#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define STILL 0
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 3
const int kDx[5] = {0, 0, 0, 1, -1},
	  kDy[5] = {0, -1, 1, 0, 0};
const int kInv[5] = {0, DOWN, UP, LEFT, RIGHT};
const int kNMax = 510;
const int kVMax = kNMax*kNMax;
const int kInf = 0x3f3f3f3f;
const double kEps = 1e-6;
const int kTimeMax = 1000000;

struct Point {
	int x, y;
	Point(){}
	Point(int xx, int yy):
		x(xx), y(yy){}
};

int n, m;
int flow[kNMax][kNMax];
Point Q[kVMax];
bool inQ[kNMax][kNMax];
int dist[kNMax][kNMax];
Point man, boat;

bool valid(Point p) {
	return 1 <= p.x && p.x <= m
		&& 1 <= p.y && p.y <= n;
}

Point go(Point from, int dir) {
	return Point(from.x+kDx[dir], from.y+kDy[dir]);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		static char ts[kNMax];
		scanf("%s", ts+1);
		for ( int j = 1; j <= m; j ++ )
			flow[j][i] = ts[j]-'0';
	}
	scanf("%d%d", &man.x, &man.y);
	memset(dist, 0x3f, sizeof(dist));
	dist[man.x][man.y] = 0;
	inQ[man.x][man.y] = true;
	int qh = 0, qt = 0;
	Q[qt++] = man;
	while ( qh != qt ) {
		Point u = Q[qh];
		qh = (qh + 1) % kVMax;
		inQ[u.x][u.y] = false;

		for ( int dir = 0; dir < 5; dir ++ ) 
			if ( dir == flow[u.x][u.y] ) { 
				Point v(u.x+kDx[dir],
						u.y+kDy[dir]);
				if ( !valid(v) ) continue;
				if ( dist[v.x][v.y] > dist[u.x][u.y] + 1 ) {
					dist[v.x][v.y] = dist[u.x][u.y] + 1;
					if ( !inQ[v.x][v.y] ) {
						inQ[v.x][v.y] = true;
						Q[qt] = v;
						qt = (qt + 1) % kVMax;
					}
				}
			}
			else {
				Point v(u.x+kDx[dir]+kDx[flow[u.x][u.y]],
						u.y+kDy[dir]+kDy[flow[u.x][u.y]]);
				if ( !valid(v) ) continue;
				if ( dist[v.x][v.y] > dist[u.x][u.y] + 2 ) {
					dist[v.x][v.y] = dist[u.x][u.y] + 2;
					if ( !inQ[v.x][v.y] ) {
						inQ[v.x][v.y] = true;
						Q[qt] = v;
						qt = (qt + 1) % kVMax;
					}
				}
			}
	}

	double ans = 1e100;
	for ( int j = 1; j <= n; j ++ ) {
		if ( dist[1][j] != kInf ) {
			if ( flow[1][j] == LEFT ) 
				ans = min(ans, (double)dist[1][j]/2 + 0.25);
			else if ( flow[1][j] != RIGHT ) 
				ans = min(ans, (double)dist[1][j]/2 + 0.5);
		}
		if ( dist[m][j] != kInf ) {
			if ( flow[m][j] == RIGHT ) 
				ans = min(ans, (double)dist[m][j]/2 + 0.25);
			else if ( flow[m][j] != LEFT ) 
				ans = min(ans, (double)dist[m][j]/2 + 0.5);
		}
	}
	for ( int i = 1; i <= m; i ++ ) {
		if ( dist[i][1] != kInf ) { 
			if ( flow[i][1] == UP )
				ans = min(ans, (double)dist[i][1]/2 + 0.25);
			else if ( flow[i][1] != DOWN ) 
				ans = min(ans, (double)dist[i][1]/2 + 0.5);
		}
		if ( dist[i][n] != kInf ) { 
			if ( flow[i][n] == DOWN )
				ans = min(ans, (double)dist[i][n]/2 + 0.25);
			else if ( flow[i][n] != UP ) 
				ans = min(ans, (double)dist[i][n]/2 + 0.5);
		}
	}
	scanf("%d%d", &boat.x, &boat.y);
	for ( int tb = 0; tb < ans+kEps && tb < kTimeMax; tb ++ ) {
		if ( dist[boat.x][boat.y] <= tb*2 ) 
			ans = min(ans, (double)tb);
		int dir = flow[boat.x][boat.y];
		if ( dir != STILL ) {
			man = go(boat, dir);
			if ( valid(man) && dist[man.x][man.y] != kInf ) {
				//meet
				double tm = (double)dist[man.x][man.y] / 2;
				if ( flow[man.x][man.y] == STILL || flow[man.x][man.y] == kInv[dir] ) {
					double vm = flow[man.x][man.y] == STILL? 1.0 : 2.0;
					if ( tb >= tm-kEps && (tb-tm)*vm-kEps <= 1.0 ) {
						double x = (1.0-(tb-tm)*vm)/(vm+1.0);
						ans = min(ans, tb+x);
					} 
					if ( tb-kEps <= tm && (tm-tb)*1.0-kEps <= 1.0 ) {
						double x = (1.0-(tm-tb)*1.0)/(vm+1.0);
						ans = min(ans, tm+x);
					}
				}
			}
			man = boat;
			if ( valid(man) && dist[man.x][man.y] != kInf ) {
				//chase
				double tm = (double)dist[man.x][man.y] / 2;
				if ( tm >= tb-kEps && 2*(tm-tb)-kEps <= 1.0 ) {
					double x = tm-tb;
					ans = min(ans, tm+x);
				}
			}
		}

		Point nextPos = go(boat, dir);
		if ( !valid(nextPos) ) 
			break;
		boat = nextPos;
	}
	if ( ans < 1e99 ) printf("%.2lf\n", ans);
	else puts("SOS");
}
