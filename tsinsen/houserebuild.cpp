#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int kNMax = 100010;

int X[kNMax], Y[kNMax], Z[kNMax];
int n, m;

struct Point {
	int x, y;
	Point(){}
	Point(int xx, int yy):
		x(xx), y(yy){}
	bool operator== (const Point &T) const {
		return x == T.x && y == T.y;
	}
	bool operator< (const Point &T) const {
		return (ll)x * T.y - (ll)y * T.x > 0;
	}
} P[kNMax], dis[kNMax];
int nDis;

struct Node {
	int l, r, mx, cnt;
} node[kNMax * 4];

int ask(int i, int low);

void update(int i) {
	node[i].mx = max(node[i*2].mx, node[i*2+1].mx);
	node[i].cnt = node[i*2].cnt;

	if ( node[i*2].mx >= node[i*2+1].mx ) return;
	int low = node[i*2].mx, cur = i*2+1;
	while ( node[cur].l != node[cur].r ) {
		if ( node[cur*2].mx > low )
			cur = cur * 2;
		else cur = cur * 2 + 1;
	}
	node[i].cnt++;
	while ( cur / 2 != i ) {
		if ( cur == cur/2*2 )
			node[i].cnt += node[cur/2].cnt-node[cur].cnt;
		cur /= 2;
	}
}

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	node[i].mx = 0;
	node[i].cnt = 0;
	if ( l == r ) return;
	int mid = (l + r) / 2;
	build(i*2, l, mid);
	build(i*2+1, mid+1, r);
}

void change(int pos, int newVal) {
	int cur = 1;
	while ( node[cur].l != node[cur].r ) {
		int mid = (node[cur].l + node[cur].r) / 2;
		if ( pos <= mid ) cur *= 2;
		else cur = cur * 2 + 1;
	}
	node[cur].mx = newVal, node[cur].cnt = 1;
	for ( cur /= 2; cur; cur /= 2 )
		update(cur);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for ( int i = 1; i <= m; i ++ ) {
		scanf("%d%d", &X[i], &Y[i]);
		P[i] = Point(X[i], Y[i]);
		dis[nDis++] = P[i];
	}
	sort(dis, dis+nDis);
	nDis = unique(dis, dis+nDis)-dis;
	for ( int i = 1; i <= m; i ++ ) {
		Z[i] = lower_bound(dis, dis+nDis, P[i])-dis+1;
		change(X[i], Z[i]);
		printf("%d\n", node[1].cnt);
	}
}
