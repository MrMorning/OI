#include <cstdio>
#include <algorithm>
using namespace std;

const int kNMax = 100010;

struct Node {
	int l, r;
	int mx;
}node[kNMax * 8];

pair<int, int> ans[4*kNMax];
int nAns = 0;
int height[2*kNMax];

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	if ( l == r ) return;
	int mid = (l + r) / 2;
	build(i*2, l, mid);
	build(i*2+1, mid+1, r);
}

void change(int i, int l, int r, int v) {
	if ( r < node[i].l || l > node[i].r ) return;
	if ( l <= node[i].l && node[i].r <= r ) {
		node[i].mx = max(node[i].mx, v);
		return;
	}
	change(i*2, l, r, v);
	change(i*2+1, l, r, v);
}

int ask(int p) {
	int res = 0;
	int cur = 1;
	while ( 1 ) {
		res = max(res, node[cur].mx);
		if ( node[cur].l == node[cur].r ) break;
		int mid = (node[cur].l + node[cur].r) / 2;
		if ( p <= mid ) cur *= 2;
		else cur = cur * 2 + 1;
	}
	return res;
}
int h[kNMax], l[kNMax], r[kNMax];
int dis[kNMax*2], nDis;
int n;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d%d%d", &h[i], &l[i], &r[i]);
		dis[nDis++] = l[i], dis[nDis++] = r[i];
	}
	sort(dis, dis + nDis);
	nDis = unique(dis, dis + nDis) - dis;
	build(1, 0, nDis-2);
	for ( int i = 0; i < n; i ++ ) {
		int ll = lower_bound(dis, dis + nDis, l[i])-dis,
			rr = lower_bound(dis, dis + nDis, r[i])-dis;
		change(1, ll, rr-1, h[i]);
	}
	for ( int i = 0; i < nDis-1; i ++ ) 
		height[i] = ask(i);
	height[nDis-1] = 0;
	int preH = 0;
	for ( int i = 0; i < nDis; i ++ ) {
		while ( i < nDis && height[i] == preH ) i++;
		if ( i == nDis ) break;
		ans[nAns++] = make_pair(dis[i], preH);
		ans[nAns++] = make_pair(dis[i], height[i]);
		preH = height[i];
	}
	printf("%d\n", nAns);
	for ( int i = 0; i < nAns; i ++ )
		printf("%d %d\n", ans[i].first, ans[i].second);
}
