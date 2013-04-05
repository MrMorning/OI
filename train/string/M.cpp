#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cstring>
using namespace std;

const int N_MAX = 100010;
int sa[N_MAX], rank[N_MAX], height[N_MAX], rank1[N_MAX];
char str[2][N_MAX];
int log2[N_MAX];

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

void init_SA(char *s, int n) {
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

int len;

void init_log2() {
	memset(log2, 0, sizeof(log2));
	for ( int i = 0; 1 << i <= N_MAX; i ++ )
		log2[1 << i] = i;
	for ( int i = 1; i <= N_MAX; i ++ )
		if ( log2[i] == 0 )
			log2[i] = log2[i - 1];
}

struct ST {
	int st[20][N_MAX];
	void init(int n, int *arr) {
		for ( int i = 0; i < n; i ++ ) 
			st[0][i] = arr[i];
		for ( int k = 1; k <= log2[n]; k ++ ) 
			for ( int i = 0; i < n; i ++ ) {
				st[k][i] = st[k - 1][i];
				if ( i + (1 << (k - 1)) < n )
					st[k][i] = min(st[k][i], st[k - 1][i + (1 << (k - 1))]);
			}
	}
	int ask(int l, int r) {
		assert(l <= r);
		assert(r <= len);
		int sz = r - l + 1,
			k = log2[sz];
		return min(st[k][l], st[k][r - (1 << k) + 1]);
	}
} rmq_lcp, rmq_rank, rmq_lcs;

int TST;

int get_lcp(int a, int b) {
	assert(a != b);
	if ( rank[a] > rank[b] )
		swap(a, b);
	return rmq_lcp.ask(rank[a] + 1, rank[b]);
}

int get_lcs(int a, int b) {
	assert(a != b);
	a = len - a - 1, b = len - b - 1;
	if ( rank1[a] > rank1[b] )
		swap(a, b);
	return rmq_lcs.ask(rank1[a] + 1, rank1[b]);
}

int main() {
	freopen("t.in", "r", stdin);
	init_log2();
	while ( 1 ) {
		scanf("%s", str[0]);
		if ( str[0][0] == '#' )
			break;
		TST ++;
		printf("Case %d: ", TST);
		int ans_val = 0, ans_pos = 0, ans_L = 0;

		len = strlen(str[0]);
		str[0][len] = '$';
		for ( int i = 0; i < len; i ++ )
			str[1][i] = str[0][len - i - 1];
		str[1][len] = '$';

		init_SA(str[1], len + 1);
		rmq_lcs.init(len + 1, height);
		memcpy(rank1, rank, sizeof(rank));

		init_SA(str[0], len + 1);
		rmq_lcp.init(len + 1, height);

		rmq_rank.init(len + 1, rank);

		//fprintf(stderr, "%d\n", get_lcp(3,4));

		for ( int L = 1; L <= len; L ++ ) {
			for ( int st = 0; st < len; st += L ) {
				int en = st;
				while ( en + L < len && get_lcp(en, en + L) >= L ) 
					en += L;
				int suf = en + L >= len ? 0 : get_lcp(en, en + L),
					pre = (st >= 1 && st + L - 1 < len) ? get_lcs(st + L - 1, st - 1) : 0;

				int cur_pos = sa[rmq_rank.ask(max(0, st - pre), min(len - 1, st + suf))];
				int cur_val = en / L - st / L + 1;

				if ( cur_val + 1 < ans_val ) continue;

				int delta = L - suf;
				if ( st - pre <= st - delta && st - delta <= st + suf && st - delta + L < len ) {
					int nxt_val = get_lcp(st - delta, st - delta + L) / L + 1;
					int nxt_pos = sa[rmq_rank.ask(max(0, st - pre), st - delta)];
					if ( nxt_val > cur_val 
							|| (nxt_val == cur_val && rank[cur_pos] > rank[nxt_pos])) {
						cur_val = nxt_val;
						cur_pos = nxt_pos;
					}
				}

				if ( cur_val > ans_val ||
						(cur_val == ans_val && rank[cur_pos] < rank[ans_pos])) {
					ans_val = cur_val;
					ans_pos = cur_pos;
					ans_L = L;
				}

				st = en;
			}
		}
		for ( int i = ans_pos; i < ans_pos + ans_val * ans_L; i ++ )
			printf("%c", str[0][i]);
		puts("");
	}
}
