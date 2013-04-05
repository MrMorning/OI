#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N_MAX = 1010;
const int BLK_SIZE = 16;
const int N_BLK = N_MAX / BLK_SIZE + 5;
inline int getIdx(int i) {
	return (i - 1) / BLK_SIZE + 1;
}
struct RowInfo{
	struct Node {
		int l, r;
		bool isSame;
		int maxVal, sameVal;
	};
	Node node[N_BLK];
	int arr[N_MAX];
	void update(int i) {
		for ( int k = node[i].l; k <= node[i].r; k ++ )
			node[i].maxVal = max(node[i].maxVal, arr[k]);
	}
	void mark(int i, int val) {
		node[i].maxVal = val;
		node[i].isSame = true;
		node[i].sameVal = val;
	}
	void pushDown(int i) {
		if ( node[i].isSame ) {
			for ( int k = node[i].l; k <= node[i].r; k ++ )
				arr[k] = node[i].sameVal;
			node[i].isSame = false;
		}
	}
	void build(int n) {
		int n_blk = n / BLK_SIZE + 1;
		for ( int i = 1; i <= n_blk; i ++ ) {
			node[i].l = (i - 1) * BLK_SIZE + 1;
			node[i].r = min(n, i * BLK_SIZE);
			node[i].isSame = false;
			node[i].maxVal = node[i].sameVal = 0;
		}
	}
	int ask(int l, int r) {
		int t1 = getIdx(l), t2 = getIdx(r);
		int res = 0;
		if ( t1 == t2 ) {
			pushDown(t1);
			for ( int k = l; k <= r; k ++ )
				res = max(res, arr[k]);
			update(t1);
		} else {
			pushDown(t1);
			pushDown(t2);
			for ( int k = l; k <= node[t1].r; k ++ )
				res = max(res, arr[k]);
			for ( int k = node[t2].l; k <= r; k ++ )
				res = max(res, arr[k]);
			for ( int t = t1 + 1; t < t2; t ++ )
				res = max(res, node[t].maxVal);
			update(t1);
			update(t2);
		}
		return res;
	}
	void set(int l, int r, int val) {
		int t1 = getIdx(l), t2 = getIdx(r);
		if ( t1 == t2 ) {
			pushDown(t1);
			for ( int k = l; k <= r; k ++ )
				arr[k] = val;
			update(t1);
		} else {
			pushDown(t1);
			pushDown(t2);
			for ( int k = l; k <= node[t1].r; k ++ )
				arr[k] = val;
			for ( int k = node[t2].l; k <= r; k ++ )
				arr[k] = val;
			for ( int t = t1 + 1; t < t2; t ++ )
				mark(t, val);
			update(t1);
			update(t2);
		}
	}
};

struct Node {
	int l, r;
	RowInfo row;
} node[N_MAX * 3];
int N, M, C;

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	node[i].row.build(M);
	if ( l == r )
		return;
	int mid = (l + r) / 2;
	build(i * 2, l, mid);
	build(i * 2 + 1, mid + 1, r);
}
int ask(int i, int x1, int x2, int y1, int y2) {
	if ( node[i].l > x2 || node[i].r < x1 )
		return 0;
	if ( x1 <= node[i].l && node[i].r <= x2 )
		return node[i].row.ask(y1, y2);
	int res = max(ask(i * 2, x1, x2, y1, y2), ask(i * 2 + 1, x1, x2, y1, y2));
	return res;
}
void set(int i, int x1, int x2, int y1, int y2, int val) {
	if ( node[i].l > x2 || node[i].r < x1 )
		return;
	if ( x1 <= node[i].l && node[i].r <= x2 ) {
		node[i].row.set(y1, y2, val);
		return;
	}
	set(i * 2, x1, x2, y1, y2, val);
	set(i * 2 + 1, x1, x2, y1, y2, val);
}

int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d%d%d", &N, &M, &C) != EOF ) {
		memset(node, 0, sizeof(node));
		build(1, 1, N);
		while ( C -- ) {
			int a, b, h, x, y;
			scanf("%d%d%d%d%d", &a, &b, &h, &x, &y);
			x ++, y ++;
			int tmp = ask(1, x, x + a - 1, y, y + b - 1);
			set(1, x, x + a - 1, y, y + b - 1, tmp + h);
			fprintf(stderr, "%d\n", ask(1, 1, N, 1, M));
		}
		int res = ask(1, 1, N, 1, M);
		printf("%d\n", res);
	}

}	

