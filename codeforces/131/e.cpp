#include <cstdio>

typedef long long msk_t;
const int kNMax = 200010;
const int kBase = 1000000007;

struct Node {
	int l, r;
	msk_t h;
	int cnt;
} node[kNMax*4];

msk_t powMem[kNMax];
int seqA[kNMax], seqB[kNMax], pos[kNMax];
int n, m;

void update(int i) {
	node[i].cnt = node[i*2].cnt + node[i*2+1].cnt;
	node[i].h = node[i*2].h * powMem[node[i*2+1].cnt] + node[i*2+1].h;
}

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	node[i].h = 0;
	node[i].cnt = 0;
	if ( l == r ) return;
	int mid = (l + r) / 2;
	build(i*2, l, mid);
	build(i*2+1, mid+1, r);
}

void change(int pos, int newS) {
	int cur = 1;
	while ( 1 ) {
		if ( node[cur].l == node[cur].r ) {
			if ( newS == 0 ) {
				node[cur].h = 0;
				node[cur].cnt = 0;
			} else {
				node[cur].h = seqB[pos];
				node[cur].cnt = 1;
			}
			break;
		}
		int mid = (node[cur].l + node[cur].r) / 2;
		if ( pos <= mid )
			cur *= 2;
		else
			cur = cur * 2 + 1;
	}
	for ( cur >>= 1; cur; cur >>= 1 )
		update(cur);
}

int main() {
	//freopen("t.in", "r", stdin);
	powMem[0] = 1;
	for ( int i = 1; i < kNMax; i ++ )
		powMem[i] = powMem[i-1] * kBase;
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &seqA[i]);
	for ( int i = 1; i <= m; i ++ ) {
		scanf("%d", &seqB[i]);
		pos[seqB[i]] = i;
	}
	build(1, 1, m);
	for ( int i = 1; i <= n; i ++ )
		change(pos[i], 1);
	msk_t curMsk = 0, dlt = 0;
	for ( int i = 1; i <= n; i ++ ) {
		curMsk += seqA[i] * powMem[n-i];
		dlt += powMem[n-i];
	}
	int ans = node[1].h == curMsk;
	for ( int i = n+1; i <= m; i ++ ) {
		curMsk += dlt;
		change(pos[i-n], 0);
		change(pos[i], 1);
		ans += node[1].h == curMsk;
	}
	printf("%d\n", ans);
}
