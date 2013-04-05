#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
using namespace std;
typedef long long ll;
const int kLenMax = 200020;
const int kLogMax = 20;

int sa[kLenMax], rank[kLenMax], height[kLenMax];
int beg[kLenMax], end[kLenMax];
int log2[kLenMax];
int st[kLogMax][kLenMax];
int tot;

void countSort(int *x, int *y, int n) {
	static int w[kLenMax];
	memset(w, 0, sizeof(w));
	for ( int i = 0; i < n; i ++ )
		w[x[y[i]]]++;
	for ( int i = 1; i < kLenMax; i ++ )
		w[i] += w[i-1];
	for ( int i = n - 1; i >= 0; i -- )
		sa[--w[x[y[i]]]] = y[i];
}

bool cmp(int *x, int i, int j, int l) {
	return x[i] == x[j] && x[i+l] == x[j+l];
}

void initSA(char *s, int n) {
	static int _x[kLenMax], _y[kLenMax];
	int *x = _x, *y = _y;
	for ( int i = 0; i < n; i ++ )
		x[i] = s[i], y[i] = i;
	countSort(x, y, n);
	for ( int len = 1, p = 0; p < n; len <<= 1 ) {
		p = 0;
		for ( int i = n-len; i < n; i ++ )
			y[p++] = i;
		for ( int i = 0; i < n; i ++ )
			if ( sa[i] >= len )
				y[p++] = sa[i] - len;
		countSort(x, y, n);
		swap(x, y);
		x[sa[0]] = 0;
		p = 1;
		for ( int i = 1; i < n; i ++ )
			x[sa[i]] = cmp(y, sa[i-1], sa[i], len) ? p-1 : p++;
	}

	for ( int i = 0; i < n; i ++ )
		rank[sa[i]] = i;
	for ( int i = 0; i < n; i ++ ) 
		if ( rank[i] ) {
			int k = max(0, i?height[rank[i-1]]-1:0);
			while ( s[i+k] == s[sa[rank[i]-1]+k] ) k ++;
			height[rank[i]] = k;
		}
}

void initST(int n) {
	for ( int i = 0; (1<<i) <= n; i ++ )
		log2[1 << i]  = i;
	for ( int i = 2; i <= n; i ++ )
		if ( !log2[i] ) log2[i] = log2[i-1];
	for ( int i = 0; i < n; i ++ )
		st[0][i] = i;
	for ( int k = 1; k < kLogMax; k ++ )
		for ( int i = 0; i < n; i ++ ) {
			st[k][i] = st[k-1][i];
			int p = i + (1<<(k-1));
			if ( p < n && height[st[k-1][p]] < height[st[k][i]] )
				 st[k][i] = st[k-1][p];
		}
}

char str[kLenMax];
int getLCP(int i, int j) {
	if ( rank[i] > rank[j] ) swap(i, j);
	int l = rank[i]+1, r = rank[j];
	int k = log2[r-l+1];
	return min(height[st[k][l]], height[st[k][r-(1<<k)+1]]);
}

int findBelow(int i, int len) {
	int lb = i, rb = tot-1  + 1;
	while ( lb < rb-1 ) {
		int mid = (lb + rb) / 2;
		if ( getLCP(sa[i], sa[mid]) >= len )
			lb = mid;
		else
			rb = mid;
	}
	return lb;
}

int findAbove(int i, int len) {
	int lb = -1, rb = i;
	while ( lb < rb-1 ) {
		int mid = (lb + rb) / 2;
		if ( getLCP(sa[i], sa[mid]) >= len )
			rb = mid;
		else
			lb = mid;
	}
	return rb;
}

int diffCnt = 0;
int cnt[kLenMax];
int bel[kLenMax];
int f[kLenMax];
ll ans[kLenMax];
int que[kLenMax];

void inc(int i) {
	if ( cnt[i] == 0 )
		diffCnt++;
	cnt[i]++;
}

void dec(int i) {
	assert(cnt[i]);
	cnt[i]--;
	if ( cnt[i] == 0 )
		diffCnt--;
}

int evalF(int i, int m) {
	memset(cnt, 0, sizeof(cnt));
	diffCnt = 0;
	for ( ; i >= 0; i-- ) 
		if ( bel[sa[i]] != -1 ) {
			inc(bel[sa[i]]);
			if ( diffCnt == m )
				return i;
		}
	return -1;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	tot = 0;
	for ( int i = 0; i < n; i ++ ) {
		beg[i] = tot;
		scanf("%s", str+tot);
		int tlen = strlen(str+tot);
		end[i] = beg[i] + tlen-1;
		tot += tlen;
		str[tot++] = '$';
	}
	memset(bel, -1, sizeof(bel));
	for ( int i = 0; i < n; i ++ )
		for ( int j = beg[i]; j <= end[i]; j ++ )
			bel[j] = i;
	initSA(str, tot);
	initST(tot);

	for ( int i = 0, qh = 0, qt = 0; i < tot; i ++ ) 
		if ( bel[sa[i]] != -1 ) {
			assert(qh <= qt);
			que[qt++] = i;
			inc(bel[sa[i]]);
			while ( diffCnt > m || (diffCnt == m  && cnt[bel[sa[que[qh]]]] > 1) )
				dec(bel[sa[que[qh++]]]);
			f[i] = diffCnt==m?que[qh]:-1;
		}
	for ( int i = 0; i < tot; i ++ ) 
		if ( bel[sa[i]] != -1 ) {
			int s = bel[sa[i]];
			int lb = 0, rb = end[s]-sa[i]+1 +1;
			while ( lb < rb-1 ) {
				int mid = (lb + rb) / 2;
				if ( f[findBelow(i, mid)] >= findAbove(i, mid) )
					lb = mid;
				else
					rb = mid;
			}
			ans[s] += lb;
		}
	for ( int i = 0; i < n; i ++ )
		printf(LL_FMT " ", ans[i]);
}
