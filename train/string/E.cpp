#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;
const int N_MAX = 2000010;

char str[2 * N_MAX];
bool pal[2 * N_MAX];

typedef pair<char, int> edge_t;

struct Edge {
	Edge *next;
	int to;
	char ch;
} edge[4 * N_MAX], *begin[2 * N_MAX];

void add_edge(int u, int v, char ch) {
	static int free_pos = 0;
	Edge *e = edge + free_pos ++;
	e->to = v, e->ch = ch, e->next = begin[u];
	begin[u] = e;
}

struct Trie {
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
		if ( i + L - 1 < p )
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
		if ( i + L - 1 < p )
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
	res[0] = 0;
	while ( res[0] < n && S[res[0]] == T[res[0]] )
		res[0] ++;
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
			Edge *e;
			for ( e = begin[cur]; e; e = e->next )
				if ( e->ch == ch )
					break;
			if ( !e ) {
				add_edge(cur, n_trie, ch);
				cur = n_trie ++;
			} else
				cur = e->to;
		}
		trie[cur].end_cnt ++;
	}

	long long ans = 0;
	for ( int i = 0; i < n_str; i ++ ) {
		int cur = root;
		int j;
		for ( j = info[i].st[0]; j < info[i].st[0] + info[i].len; j ++ ) {
			char ch = str[j];
			Edge *e;
			for ( e = begin[cur]; e; e = e->next )
				if ( e->ch == ch )
					break;
			if ( !e )
				break;
			cur = e->to;
			if ( j + 1 == info[i].st[0] + info[i].len || pal[j + 1] )
				ans += trie[cur].end_cnt;
		}
		if ( j == info[i].st[0] + info[i].len )
			ans += trie[cur].pal_cnt;
	}
	cout << ans << '\n';
}
