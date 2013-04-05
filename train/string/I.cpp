#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

const int LEN_MAX = 110000;
const int N_MAX = 110;

int n_str;
int str[LEN_MAX];
int bel[LEN_MAX], len[N_MAX], st[N_MAX];
int sa[LEN_MAX], rank[LEN_MAX], height[LEN_MAX];
int tot_len;
vector<string> out;

bool is_equal(int *x, int i, int j, int l) {
	return x[i] == x[j] && x[i + l] == x[j + l];
}

void count_sort(int *x, int *y, int n) {
	static int w[LEN_MAX];
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

void init_sa(int *s, int n) {
	static int _x[LEN_MAX], _y[LEN_MAX];
	int *x = _x, *y = _y;
	for ( int i = 0; i < n; i ++ )
		x[i] = s[i], y[i] = i;
	count_sort(x, y, n);
	for ( int len = 1, p = 0; p < n - 1; len *= 2 ) {
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
			x[sa[i]] = is_equal(y, sa[i - 1], sa[i], len) ? p : ++ p;
	}

	for ( int i = 0; i < n; i ++ )
		rank[sa[i]] = i;
	for ( int i = 0, k = 0; i < n; height[rank[i ++]] = k ) 
		if ( rank[i] )
			for ( k ? k -- : 0; s[i + k] == s[sa[rank[i] - 1] + k]; k ++ );
}

bool check(int lim) {
	for ( int i = 1; i < tot_len; i ++ )
		if ( height[i] >= lim ) {
			int be = i;
			while ( i + 1 < tot_len && height[i + 1] >= lim )
				i ++;
			set<int> S;
			for ( int k = be - 1; k <= i; k ++ )
				if ( str[sa[k]] != 'z' - 'a')
					S.insert(bel[sa[k]]);
			if ( (int)S.size() > n_str / 2 )
				return true;
		}
	return false;
}

void output(int lim) {
	out.clear();
	for ( int i = 1; i < tot_len; i ++ )
		if ( height[i] >= lim ) {
			int be = i;
			while ( i + 1 < tot_len && height[i + 1] >= lim )
				i ++;
			set<int> S;
			for ( int k = be - 1; k <= i; k ++ )
				if ( str[sa[k]] <= 'z' - 'a' )
					S.insert(bel[sa[k]]);
			if ( (int)S.size() > n_str / 2 ) {
				string ts;
				int pos = sa[be];
				for ( int k = 0; k < lim; k ++ )
					ts += str[pos + k] + 'a';
				out.push_back(ts);
			}
		}
	sort(out.begin(), out.end());
	for ( int i = 0; i < (int)out.size(); i ++ )
		printf("%s\n", out[i].c_str());
}

int main() {
	freopen("t.in", "r", stdin);
	while ( 1 ) {
		scanf("%d", &n_str);
		if ( n_str == 0 )
			break;
		tot_len = 0;
		for ( int i = 0; i < n_str; i ++ ) {
			static char ts[1111];
			scanf("%s", ts);
			len[i] = strlen(ts);
			for ( int k = 0; k < len[i]; k ++ ) 
				str[tot_len + k] = ts[k] - 'a';
			st[i] = tot_len;
			for ( int k = st[i]; k < st[i] + len[i]; k ++ )
				bel[k] = i;
			tot_len += len[i];
			str[tot_len ++] = 26 + i;
		}
		init_sa(str, tot_len);
		int len_max = 0;
		for ( int i = 0; i < n_str; i ++ )
			len_max = max(len_max, len[i]);
		int lb = 1, rb = len_max + 1;

		for ( int mid = (lb + rb) / 2;
				lb < rb - 1; mid = (lb + rb) / 2 ) 
			if ( check(mid) )
				lb = mid;
			else
				rb = mid;
		if ( check(lb) )
			output(lb);
		else
			printf("?\n");
		puts("");
	}
}
