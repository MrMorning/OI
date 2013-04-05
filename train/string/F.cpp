#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N_MAX = 200010;

struct MonoStack {
	pair<int, int> stack[N_MAX];
	int top;
	ll sum;
	int cnt;
	MonoStack() {
		top = 0;
		sum = 0;
	}

	void refresh(int lim) {
		int acc = 0;
		while ( top && stack[top - 1].first >= lim ) {
			acc += stack[top - 1].second;
			sum -= (ll)stack[top - 1].first * stack[top - 1].second;
			top --;
		}
		if ( acc > 0 ) {
			stack[top ++] = make_pair(lim, acc);
			sum += (ll)lim * acc;
		}
	}

	void push(pair<int, int> p) {
		cnt ++;
		while ( top && stack[top - 1].first >= p.first ) {
			p.second += stack[top - 1].second;
			sum -= (ll)stack[top - 1].first * stack[top - 1].second;
			top --;
		}
		stack[top ++] = p;
		sum += (ll)p.first * p.second;
	}

	void clear() {
		top = 0, sum = 0, cnt = 0;
	}
} MS;

int sa[2 * N_MAX], rank[2 * N_MAX], height[2 * N_MAX];
char s[2 * N_MAX];
char str1[N_MAX], str2[N_MAX];

void count_sort(int *x, int *y, int n) {
	static int w[2 * N_MAX];
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

void init_sa(int n) {
	static int _x[2 * N_MAX], _y[2 * N_MAX];
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

int K;
int main() {
	freopen("t.in", "r", stdin);
	while ( 1 ) {
		scanf("%d", &K);
		if ( K == 0 )
			break;
		scanf("%s%s", str1, str2);
		int N = strlen(str1), M = strlen(str2);
		memcpy(s, str1, sizeof(char) * N);
		s[N] = '#';
		memcpy(s + N + 1, str2, sizeof(char) * M);
		s[N + M + 1] = '?';
		init_sa(N + M + 2);
		int len = N + M + 2;

		//division
		ll res = 0;
		for ( int i = 1; i < len; i ++ )  
			if ( height[i] >= K ) {
				int st = i;
				while ( i + 1 < len && height[i + 1] >= K )
					i ++;
				int en = i;
				MS.clear();

				for ( int k = st - 1; k <= en; k ++ ) {
					if ( sa[k] < N ) {
						res += MS.sum - (ll)(K - 1) * MS.cnt;
						MS.refresh(height[k + 1]);
					}
					else if ( sa[k] > N )
						MS.push(make_pair(height[k + 1], 1));
				}

				MS.clear();
				for ( int k = en; k >= st - 1; k -- ) {
					if ( sa[k] < N ) {
						res += MS.sum - (ll)(K - 1) * MS.cnt;
						MS.refresh(height[k]);
					}
					else if ( sa[k] > N )
						MS.push(make_pair(height[k], 1));
				}
			}	


		cout << res << '\n';
	}
}
