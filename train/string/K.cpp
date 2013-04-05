#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

const int N_MAX = 400010;

int sa[N_MAX], rank[N_MAX], height[N_MAX];
int s[N_MAX];

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

int n, axis[N_MAX];
int memo[N_MAX];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d", &s[i]);
		axis[i] = s[i];
	}
	sort(axis, axis + n);
	int axis_cnt = unique(axis, axis + n) - axis;


	for ( int i = 0; i < n; i ++ )
		s[i] = lower_bound(axis, axis + axis_cnt, s[i]) - axis + 1;

	for ( int i = 0; i < n / 2; i ++ )
		swap(s[i], s[n - i - 1]);
	for ( int i = 0; i < n; i ++ )
		memo[i] = s[i];

	init_SA(n);
	int A_pos;
	for ( int i = 0; i < n; i ++ )
		if ( sa[i] >= 2 ) {
			A_pos = sa[i];
			break;
		}


	for ( int i = A_pos; i < 2 * A_pos; i ++ )
		s[i] = s[i - A_pos];
	s[2 * A_pos + 1] = 0;
	init_SA(2 * A_pos + 1);

	int B_pos;
	for ( int i = 0; i < 2 * A_pos + 1; i ++ )
		if ( sa[i] < A_pos && sa[i] >= 1) {
			B_pos = sa[i];
			break;
		}
	for ( int i = A_pos; i < n; i ++ )
		printf("%d\n", axis[memo[i] - 1]);
	for ( int i = B_pos; i < A_pos; i ++ )
		printf("%d\n", axis[memo[i] - 1]);
	for ( int i = 0; i < B_pos; i ++ )
		printf("%d\n", axis[memo[i] - 1]);
}
