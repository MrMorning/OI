#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
const int N_MAX = 2000000;

char str[2 * N_MAX];
bool pal[2 * N_MAX];

typedef pair<char, int> edge_t;

struct Trie {
	vector<edge_t> go;
	int pal_cnt, end_cnt;
} trie[2 * N_MAX];
int n_trie;

struct Info {
	int len;
	int st[2];
} info[N_MAX];

int tot_len = 0;

int sa[2 * N_MAX], rank[2 * N_MAX], height[2 * N_MAX];
void calc_sa(int *x, int *y, int n) {
	static int w[2 * N_MAX];
	int upper = 0;
	for ( int i = 0; i < n; i ++ )
		upper = max(upper, x[y[i]]);
	upper ++;
	memset(w, 0, sizeof(int) * upper);
	for ( int i = 0; i < n; i ++ )
		w[x[y[i]]] ++;
	for ( int i = 1; i < upper; i ++ )
		w[i] += w[i - 1];
	for ( int i = n - 1; i >= 0; i -- )
		sa[-- w[x[y[i]]]] = y[i];
}

bool is_equal(int *x, int i, int j, int l) {
	return x[i] == x[j] && x[i + l] == x[j + l];
}

void init_sa(char *s, int n) {
	static int _x[N_MAX], _y[N_MAX];
	int *x = _x, *y = _y;
	for ( int i = 0; i < n; i ++ )
		x[i] = s[i], y[i] = i;
	calc_sa(x, y, n);
	for ( int len = 1, p = 0; p < n - 1; len <<= 1 ) {
		p = 0;
		for ( int i = n - len; i < n; i ++ )
			y[p ++] = i;
		for ( int i = 0; i < n; i ++ )
			if ( sa[i] >= len )
				y[p ++] = sa[i] - len;
		calc_sa(x, y, n);
		swap(x, y);
		p = x[sa[0]] = 0;
		for ( int i = 1; i < n; i ++ ) 
			x[sa[i]] = is_equal(y, sa[i - 1], sa[i], len) ? p : ++ p;
	}

	for ( int i = 0; i < n; i ++ )
		rank[sa[i]] = i;

	for ( int i = 0, k = 0; i < n; height[rank[i ++]] = k )
		if ( rank[i] )
			for ( k ? k -- : 0; s[i + k] == s[sa[rank[i] - 1] + k]; k ++ );
}

void calc_palin(bool *res, char *s, int n) {
	static char curs[2 * N_MAX];
	memcpy(curs, s, sizeof(char) * n);
	curs[n] = 1;
	for ( int i = n + 1; i <= n + n; i ++ )
		curs[i] = s[n - (i - n - 1) - 1];
	curs[n + n + 1] = 0;
	init_sa(curs, 2 * n + 2);
	int pos = rank[n + 1];
	int mi = height[pos];
	for ( int i = pos - 1; i >= 0; i -- ) {
		if ( sa[i] < n ) {
			if ( mi == n - sa[i] )
				res[sa[i]] = 1;
		}
		mi = min(mi, height[i]);
	}
	mi = height[pos + 1];
	for ( int i = pos + 1; i <= n + n + 1; i ++ ) {
		mi = min(mi, height[i]);
		if ( sa[i] < n )
			if ( mi == n - sa[i] )
				res[sa[i]] = 1;
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int n_str;
	scanf("%d", &n_str);
	for ( int i = 0; i < n_str;i ++ ) {
		int len;
		scanf("%d", &len);
		scanf("%s", str + tot_len);
		info[i].len = len;
		info[i].st[0] = tot_len;
		tot_len += len;
	}
	for ( int i = 0; i < n_str; i ++ ) {
		info[i].st[1] = info[i].st[0] + tot_len;
		for ( int k = 0; k < info[i].len; k ++ )
			str[info[i].st[1] + k] = str[info[i].st[0] + info[i].len - k - 1];
	}

	for ( int i = 0; i < n_str; i ++ ) {
		calc_palin(pal + info[i].st[0], str + info[i].st[0], info[i].len);
		calc_palin(pal + info[i].st[1], str + info[i].st[1], info[i].len);
	}

	n_trie = 0;
	int root = n_trie ++;
	for ( int i = 0; i < n_str; i ++ ) {
		int cur = root;
		for ( int j = info[i].st[1]; j < info[i].st[1] + info[i].len; j ++ ) {
			Trie &it = trie[cur];
			it.pal_cnt += pal[j];
			char ch = str[j];
			int sz = it.go.size(), k;
			for ( k = 0; k < sz; k ++ ) 
				if ( it.go[k].first == ch )
					break;
			if ( k == sz ) 
				it.go.push_back(make_pair(ch, n_trie ++));
			cur = it.go[k].second;
		}
		trie[cur].end_cnt ++;
	}

	long long ans = 0;
	for ( int i = 0; i < n_str; i ++ ) {
		int cur = root;
		int j;
		for ( j = info[i].st[0]; j < info[i].st[0] + info[i].len; j ++ ) {
			Trie &it = trie[cur];
			char ch = str[j];
			int sz = it.go.size(), k;
			for ( k = 0; k < sz; k ++ )
				if ( it.go[k].first == ch )
					break;
			if ( k == sz )
				break;
			cur = it.go[k].second;
			if ( j + 1 == info[i].st[0] + info[i].len || pal[j + 1] )
				ans += trie[cur].end_cnt;
		}
		if ( j == info[i].st[0] + info[i].len )
			ans += trie[cur].pal_cnt;
	}
	cout << ans << '\n';
}
