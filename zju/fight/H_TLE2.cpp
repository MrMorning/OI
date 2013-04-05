#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 1010;
const int BLK_SIZE = 16;
const int N_BLK = N_MAX / BLK_SIZE + 5;
struct Node {
	int l, r;
	bool isSame;
	int maxVal, sameVal;
};
inline int getIdx(int i) {
	return (i - 1) / BLK_SIZE + 1;
}
struct SGT {
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
} sgt[N_MAX];

int main() {
	freopen("t.in", "r", stdin);
	int N, M, C;
	while ( scanf("%d%d%d", &N, &M, &C) != EOF ) {
		for ( int i = 1; i <= N; i ++ )
			sgt[i].build(M);
		while ( C -- ) {
			int a, b, h, x, y;
			scanf("%d%d%d%d%d", &a, &b, &h, &x, &y);
			x ++, y ++;
			int tmp = 0;
			for ( int i = x; i <= x + a; i ++ )
				tmp = max(tmp, sgt[i].ask(y, y + b));
			for ( int i = x; i <= x + a; i ++ )
				sgt[i].set(y, y + b, tmp + h);
		}
		int res = 0;
		for ( int i = 1; i <= N; i ++ )
			res = max(res, sgt[i].ask(1, M));
		printf("%d\n", res);
	}
}	

