#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define pb(x) push_back(x)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#define UP 0
typedef long long ll;
using namespace std;
const int OFFSET=305;
const int kDx[4] = {-1, 0, 1, 0};
const int kDy[4] = {0, 1, 0, -1};
int dis[305*305*2], nDis;
struct Point {
	int x, y; Point(){}
	Point(int xx, int yy):x(xx),y(yy){}
} queue[305*305];
vector<Point> list[305*305*2];
int f[888][888];
int panel[305][305], symbol[305][305];
bool vis[305][305];
int qt;
Point core;
int n, m, xs, ys;

bool comp(const Point &p1, const Point &p2) {
	return f[p1.x-core.x+OFFSET][p1.y-core.y+OFFSET] < f[p2.x-core.x+OFFSET][p2.y-core.y+OFFSET];
}

void work(int c) {
	if ( !list[c].size() ) return;
	sort(list[c].begin(), list[c].end(), comp);
	foreach(it, list[c]) {
		if ( symbol[it->x][it->y] != -1 && !vis[it->x][it->y] ) {
			vis[it->x][it->y] = true;
			queue[qt++] = *it;
		}
	}
}

void init() {
	Point cur(0, 0);
	f[0+OFFSET][0+OFFSET] = 1;
	for ( int inc = 0, step = 1, len = 0, dir = UP; min(abs(cur.x), abs(cur.y)) < max(n, m); step += len, dir = (dir+1)%4, inc^=1 ) {
		if ( inc == 0 ) len++;
		for ( int k = 1; k <= len; k ++ ) 
			f[cur.x+k*kDx[dir]+OFFSET][cur.y+k*kDy[dir]+OFFSET] = step+k;
		cur.x += len*kDx[dir], cur.y += len*kDy[dir];
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	init();

	dis[nDis++] = 0;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			scanf("%d", &panel[i][j]);
			dis[nDis++] = panel[i][j];
		}
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			scanf("%d", &symbol[i][j]);
			if ( symbol[i][j] != -1 )
				dis[nDis++] = symbol[i][j];
		}
	sort(dis, dis + nDis);
	nDis = unique(dis, dis + nDis) - dis;
	for ( int i = 1; i <= n; i ++ ) 
		for ( int j = 1; j <= m; j ++ ) {
			panel[i][j] = lower_bound(dis, dis+nDis, panel[i][j])-dis;
			if ( symbol[i][j] != -1 )
				symbol[i][j] = lower_bound(dis, dis+nDis, symbol[i][j])-dis;
			list[panel[i][j]].pb(Point(i,j));
		}
	scanf("%d%d", &xs, &ys);
	qt = 0;
	queue[qt++] = Point(xs, ys);
	vis[xs][ys] = true;
	ll ans = 0, acc = 0;
	int curColor = panel[xs][ys];
	for ( int qh = 0; qh < qt; qh ++ ) {
		Point cur = queue[qh];
		if ( curColor != 0 && curColor != symbol[cur.x][cur.y] ) {
			core = cur;
			work(curColor);

			acc += list[curColor].size();
			ans += acc;
			list[curColor].clear();

			curColor = symbol[cur.x][cur.y];
		}
	}
	cout << ans;
}
