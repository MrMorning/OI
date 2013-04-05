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

void extended_KMP(int *res, char *S, char *T, int n) {
	static int next[N_MAX];
	next[1] = 0;
	while ( 1 + next[1] < n && T[1 + next[1]] == T[next[1]] )
		next[1] ++;
	int a = 1, p = 1 + next[1] - 1;
	for ( int i = 2; i < n; i ++ ) {
		int L = next[i - a];
		if ( i <= p && i + L - 1 <= p )
			next[i] = L;
		else {
			next[i] = max(0, p - i + 1);
			while ( i + next[i] < n && 
					T[i + next[i]] == T[next[i]] )
				next[i] ++;
			if ( i + next[i] - 1 > p )
				a = i, p = i + next[i] - 1;
		}
	}
	res[1] = 0;
	while ( 1 + res[1] < n && res[1] < n 
			&& S[1 + res[1]] == T[res[1]] )
		res[1] ++;
	a = 1, p = 1 + res[1] - 1;
	for ( int i = 2; i < n; i ++ ) {
		int L = next[i - a];
		if ( i <= p && i + L - 1 <= p )
			res[i] = L;
		else {
			res[i] = max(0, p - i + 1);
			while ( i + res[i] < n && 
					S[i + res[i]] == T[res[i]] )
				res[i] ++;
			if ( i + res[i] - 1 > p )
				a = i, p = i + res[i] - 1;
		}
	}
}

void calc_palin(bool *res, char *s, int n) {
	static char curs[N_MAX], invs[N_MAX];
	static int tmp[N_MAX];
	memcpy(curs, s, sizeof(char) * n);
	for ( int i = 0; i < n; i ++ )
		invs[i] = curs[n - i - 1];
	extended_KMP(tmp, curs, invs, n);
	for ( int i = 0; i < n; i ++ )
		if ( tmp[i] == n - i )
			res[i] = 1;
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
