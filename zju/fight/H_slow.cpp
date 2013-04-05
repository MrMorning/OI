#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 1010;
struct Node {
	int l, r;
	bool isSame;
	int maxVal, sameVal;
};

struct SGT {
	Node node[N_MAX * 3];
	void update(int i) {
		node[i].maxVal = max(node[i * 2].maxVal, node[i * 2 + 1].maxVal);
	}
	void mark(int i, int val) {
		node[i].maxVal = val;
		node[i].isSame = true;
		node[i].sameVal = val;
	}
	void pushDown(int i) {
		if ( node[i].isSame ) {
			mark(i * 2, node[i].sameVal);
			mark(i * 2 + 1, node[i].sameVal);
			node[i].isSame = false;
		}
	}
	void build(int i, int l, int r) {
		node[i].l = l, node[i].r = r;
		node[i].isSame = 0;
		node[i].maxVal = 0;
		if ( l == r )
			return;
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
	}
	int ask(int i, int l, int r) {
		if ( node[i].l > r || node[i].r < l )
			return 0;
		if ( l <= node[i].l && node[i].r <= r )
			return node[i].maxVal;
		pushDown(i);
		int res = max(ask(i * 2, l, r), ask(i * 2 + 1, l, r));
		update(i);
		return res;
	}
	void set(int i, int l, int r, int val) {
		if ( node[i].l > r || node[i].r < l )
			return;
		if ( l <= node[i].l && node[i].r <= r ) {
			mark(i, val);
			return;
		}
		pushDown(i);
		set(i * 2, l, r, val);
		set(i * 2 + 1, l, r, val);
		update(i);
	}
} sgt[N_MAX];

int main() {
//	freopen("t.in", "r", stdin);
	int N, M, C;
	while ( scanf("%d%d%d", &N, &M, &C) != EOF ) {
		for ( int i = 1; i <= N; i ++ )
			sgt[i].build(1, 1, M);
		while ( C -- ) {
			int a, b, h, x, y;
			scanf("%d%d%d%d%d", &a, &b, &h, &x, &y);
			int tmp = 0;
			for ( int i = x; i <= x + a; i ++ )
				tmp = max(tmp, sgt[i].ask(1, y, y + b));
			for ( int i = x; i <= x + a; i ++ )
				sgt[i].set(1, y, y + b, tmp + h);
		}
		int res = 0;
		for ( int i = 1; i <= N; i ++ )
			res = max(res, sgt[i].ask(1, 1, M));
		printf("%d\n", res);
	}
}	

