#include <cstdio>
#include <cassert>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double val_t;
typedef set<int>::iterator itr_t;

const int kNMax = 1111111;
const int kLogMax = 22;

struct IndexTree {
	val_t ele[kNMax];

	void add(int i, val_t val) {
		i += 5;
		for ( ; i < kNMax; i += i & -i )
			ele[i] += val;
	}
	void add(int l, int r, val_t val) {
		if ( l > r ) return;
		add(l, val);
		add(r+1, -val);
	}
	val_t get(int i) {
		i += 5;
		val_t res = 0;
		for ( ; i; i -= i & -i )
			res += ele[i];
		return res;
	}
} idt1, idt2;

int a[kNMax], f[kNMax], g[kNMax];
int st[kLogMax][kNMax], log2[kNMax];
//val_t haha[kNMax];

int n, m;

void initST() {
	for ( int i = 0; (1<<i) <= n; i ++ )
		log2[1<<i] = i;
	for ( int i = 2; i <= n; i ++ )
		if ( !log2[i] ) log2[i] = log2[i-1];
	for ( int i = 1; i <= n; i ++ )
		st[0][i] = i;
	for ( int k = 1; k < kLogMax; k ++ )
		for ( int i = 1; i <= n; i ++ ) {
			st[k][i] = st[k-1][i];
			int p = i+(1<<(k-1));
			if ( p <= n && a[st[k-1][p]] < a[st[k][i]] )
				st[k][i] = st[k-1][p];
		}
}

int findMin(int l, int r) {
	assert(l <= r);
	int k = log2[r-l+1],
		p = r-(1<<k)+1;
	return min(a[st[k][l]], a[st[k][p]]);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) 
		scanf("%d", &a[i]);

	initST();
	f[1] = 0;
	for ( int i = 2; i <= n; i ++ ) {
		int lb = 1, rb = i-1 + 1;
		while ( lb < rb-1 ) {
			int mid = (lb + rb) / 2;
			if ( findMin(mid, i-1) < a[i] )
				lb = mid;
			else
				rb = mid;
		}
		if ( findMin(lb, i-1) < a[i] ) 
			f[i] = lb;
		else f[i] = 0;
	}
	g[n] = n+1;
	for ( int i = n-1; i >= 1; i -- ) {
		int lb = i+1 -1, rb = n;
		while ( lb < rb-1 ) {
			int mid = (lb + rb) / 2;
			if ( findMin(i+1,mid) <= a[i] )
				rb = mid;
			else
				lb = mid;
		}
		if ( findMin(i+1,rb) <= a[i] ) 
			g[i] = rb;
		else g[i] = n+1;
	}	

	for ( int i = 1; i <= n; i ++ ) {
		int m1 = i-f[i]-1, m2 = g[i]-i-1;
		if ( m2 > m1 ) swap(m1, m2);
	/*	for ( int k = 1; k <= m2+1; k ++ )
			haha[k] += (ll)k*a[i];
		for ( int k = m2+2; k <= m1+1; k ++ )
			haha[k] += (ll)(m2+1)*a[i];
		for ( int k = m1+2; k <= m1+m2+1; k ++ )
			haha[k] += (ll)(m1+m2+2-k)*a[i];
		*/		
		idt2.add(1, m2+1, (val_t)a[i]);

		idt1.add(m2+2, m1+1, (val_t)(m2+1)*a[i]);

		idt1.add(m1+2, m1+m2+1, (val_t)(m1+m2+2)*a[i]);
		idt2.add(m1+2, m1+m2+1, (val_t)-a[i]);
	}
	scanf("%d", &m);
	while ( m -- ) {
		int k;
		scanf("%d", &k);
		val_t ans = idt1.get(k)+(val_t)k*idt2.get(k);
		//val_t ans = haha[k];
		ans = ans/(n-k+1);
		printf("%.12lf\n", (double)ans);
	}
}
