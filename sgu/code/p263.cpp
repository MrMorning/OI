#include <cstdio>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
const int nCell = 1000010;

int cube[nCell];

namespace sgt {
	int sum[nCell * 4];
	void set(int p, int x) {
		int cur = 1, l = 1, r = nCell;
		while ( l != r ) {
			int mid = (l + r) >> 1;
			if ( p <= mid ) {
				cur *= 2;
				r = mid;
			} else {
				cur = cur * 2 + 1;
				l = mid + 1;
			}
		}
		sum[cur] = x;
		cur >>= 1;
		while ( cur ) {
			sum[cur] = sum[cur * 2] + sum[cur * 2 + 1];
			cur >>= 1;
		}
	}
	int find(int x) {
		int cur = 1, l = 1, r = nCell;
		while ( l != r ) {
			int mid = (l + r) >> 1;
			if ( x <= sum[cur * 2] ) {
				cur *= 2;
				r = mid;
			} else {
				l = mid + 1;
				x -= sum[cur * 2];
				cur = cur * 2 + 1;
			}
		}
		return l;
	}
}

struct DisjointSet {
	int len[nCell], parent[nCell];
	ll cnt[nCell];

	int find(int x) {
		return parent[x] == x ? x : parent[x] = find(parent[x]);
	}

	void merge(int a, int b) {
		int p = find(a), q = find(b);
		parent[p] = q;
		cnt[q] += cnt[p];
		len[q] += len[p];
	}
} DS;

void addCube(int x, int c) {
	if ( cube[x] == 0 ) {
		DS.len[x] = 1;
		sgt::set(x, 1);
		if ( cube[x - 1] != 0 ) {
			DS.merge(x, x - 1);
			sgt::set(x, 0);
		} 
		if ( cube[x + 1] != 0 ) {
			DS.merge(x + 1, x);
			sgt::set(x + 1, 0);
		}
	}
	cube[x] += c;
	DS.cnt[DS.find(x)] += c;
}

int main() {
	for ( int i = 1; i <= nCell; i ++ ) {
		DS.parent[i] = i;
		DS.cnt[i] = 0;
		DS.len[i] = 0;
		cube[i] = 0;
	}
	int nCmd;
	scanf("%d", &nCmd);
	while ( nCmd -- ) {
		char cmd[10];
		int x, c, t;

		scanf("%s", cmd);
		if ( cmd[0] == 'p' ) {
			scanf("%d%d", &x, &c);
			addCube(x, c);
		} else if ( cmd[0] == 't' && cmd[1] == 'p' ) {
			scanf("%d%d%d", &t, &x, &c);
			int p = sgt::find(t);
			addCube(p + x - 1, c);
		} else if ( cmd[0] == 't' && cmd[1] == 'o' ) {
		   printf("%d towers\n", sgt::sum[1]);	
		} else if ( cmd[0] == 'c' ) {
			scanf("%d", &t);
			int p = sgt::find(t);
			printf(LL_FMT" cubes in %dth tower\n", DS.cnt[p], t); 
		} else if ( cmd[0] == 'l' ) {
			scanf("%d", &t);
			int p = sgt::find(t);
			printf("length of %dth tower is %d\n", t, DS.len[p]); 
		} else {
			scanf("%d%d", &t, &x);
			int p = sgt::find(t);
			printf("%d cubes in %dth column of %dth tower\n", cube[p + x - 1], x, t);
		}
	}
}
