#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N_MAX = 20010;
const int inf = 0x3f3f3f3f;
int sa[N_MAX], rank[N_MAX], height[N_MAX];
int s[N_MAX], ts[N_MAX];

void count_sort(int *x, int *y, int n) {
	static int w[N_MAX];
	int lim = 0;
	for ( int i = 0; i < n; i ++ )
		lim = max(lim, x[y[i]]);
	memset(w, 0, sizeof(int) * (lim + 1));
	for ( int i = 0; i < n; i ++ )
		w[x[y[i]]] ++;
	for ( int i = 1; i <= lim; i ++ )
		w[i] += w[i - 1];
	for ( int i = n - 1; i >= 0; i -- )
		sa[-- w[x[y[i]]]] = y[i];
}

bool is_equal(int *x, int i, int j, int l) {
	return x[i] == x[j] && x[i + l] == x[j + l];
}

void init_SA(int n) {
	static int _x[N_MAX], _y[N_MAX];
	int *x = _x, *y = _y;
	for ( int i = 0; i < n; i ++ )
		x[i] = s[i], y[i] = i;
	count_sort(x, y, n);
	for ( int len = 1, p = 0; p < n - 1; len <<= 1 ) {
		p = 0;
		for ( int i = n - len; i < n; i ++ )
			y[p ++] = i;
		for ( int i = 0; i < n; i ++ )
			if ( sa[i] >= len )
				y[p ++] = sa[i] - len;
		count_sort(x, y, n);
		swap(x, y);
		p = x[sa[0]] = 0;
		for ( int i = 1; i < n; i ++ )
			if ( is_equal(y, sa[i - 1], sa[i], len) )
				x[sa[i]] = p;
			else
				x[sa[i]] = ++ p;
	}

	for ( int i = 0; i < n; i ++ )
		rank[sa[i]] = i;
	for ( int k = 0, i = 0; i < n; height[rank[i ++]] = k )
		if ( rank[i] != 0 )
			for ( k ? k -- : 0; s[i + k] == s[sa[rank[i] - 1] + k]; k ++ );
}

int n;
bool check(int upper) {
	for ( int i = 1; i < n; i ++ ) 
		if ( height[i] >= upper ) {
			int st = i;
			while ( i + 1 < n && height[i + 1] >= upper ) 
				i ++;
			int mi = inf, ma = -inf;
			for ( int j = st - 1; j <= i; j ++ ) {
				mi = min(mi, sa[j]);
				ma = max(ma, sa[j]);
			}
			if ( ma - mi >= upper )
				return true;
		}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	while ( 1 ) {
		scanf("%d", &n);
		if ( n == 0 )
			break;
		for ( int i = 0; i < n; i ++ )
			scanf("%d", &ts[i]);
		for ( int i = 0; i < n - 1; i ++ ) {
			s[i] = 88 + ts[i + 1] - ts[i];
		}
		s[n - 1] = 0;
		init_SA(n);

		int lb = 4, rb = n / 2 + 1;
		for ( int mid = (lb + rb) / 2; lb < rb - 1;
				mid = (lb + rb) / 2 )
			if ( check(mid) )
				lb = mid;
			else
				rb = mid;
		if ( check(lb) )
			printf("%d\n", lb + 1);
		else
			printf("0\n");
	}
}
