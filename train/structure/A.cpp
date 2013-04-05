#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N_MAX = 50010;
const int inf = 0x3f3f3f3f;

struct Info {
	int lval, rval, mval, sum;
	bool e;
	Info(bool _e = true):
		e(_e){}
};

Info operator+ (const Info &lch, const Info &rch){
	if ( !lch.e ) return rch;
	if ( !rch.e ) return lch;
	Info x;
	x.sum = lch.sum + rch.sum;
	x.lval = max(lch.lval, lch.sum + rch.lval);
	x.rval = max(rch.rval, rch.sum + lch.rval);
	x.mval = max(lch.mval, max(rch.mval, lch.rval + rch.lval));
	return x;
}

struct Node {
	int l, r;
	Info info;
} node[N_MAX * 3];
int arr[N_MAX];

void update(int i) {
	node[i].info = node[i * 2].info + node[i * 2 + 1].info;
}

void build(int i, int l, int r) {
	Node &x = node[i];
	x.l = l, x.r = r;
	if ( l == r )
		x.info.lval = x.info.rval = x.info.mval = x.info.sum = arr[l];
	else {
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
		update(i);
	}
}

Info ask(int i, int l, int r) {
	if ( node[i].l > r || node[i].r < l )
		return Info(false);
	if ( l <= node[i].l && node[i].r <= r )
		return node[i].info;
	Info I1 = ask(i * 2, l, r),
		 I2 = ask(i * 2 + 1, l, r);
	return I1 + I2;
}

int next_int() {
	char ch = getchar();
	while ( !isdigit(ch) && ch != '-')
		ch = getchar();
	int x = 0;
	bool flag = false;
	if ( ch == '-' ) {
		flag = true;
		ch = getchar();
	}
	while ( isdigit(ch) ) {
		x = x * 10 + ch - '0', ch = getchar();
	}
	return x * (flag ? -1 : 1);
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	n = next_int();
	for ( int i = 1; i <= n; i ++ )
		arr[i] = next_int();
	build(1, 1, n);
	scanf("%d", &m);
	while ( m -- ) {
		int x, y;
		x = next_int();
	   	y = next_int();
		printf("%d\n", ask(1, x, y).mval);
	}
}
