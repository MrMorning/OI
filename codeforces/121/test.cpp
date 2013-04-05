#include <cstdio>
#include <algorithm>
using namespace std;
const int kEleMax = 1000;
int tree[kEleMax];
int n, q, a[kEleMax];
void add(int i, int k) {
	for ( ; i < kEleMax; i += i & -i )
		tree[i] = max(tree[i], k);
}
int getMax(int l, int r) {
	int res = 0;
	int i = r;
	while ( 1 ) {
		while ( i >= l && i - (i & -i) < l ) 
			res = max(res, a[i--]);
		if ( i < l )
			break;
		res = max(res, tree[i]);
		i -= i & -i;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &q);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &a[i]);
		add(i, a[i]);
	}
	while ( q -- ) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", getMax(l, r));
	}
}
