#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kNMax = 100010;
const int kBlkSz = 300;

#define GET_ID(i) ((i)/kBlkSz)
#define GET_BLK_R(i) (min(((i)+1)*kBlkSz-1, n-1))

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int c[kNMax], l[kNMax], r[kNMax], q[kNMax];
int wait[kNMax], n, m, cnt[kNMax];
ll ans[kNMax];
bool cmpL(int i, int j) { return l[i] < l[j]; }
bool cmpR(int i, int j) { return r[i] < r[j]; }

void bruteWork(int i, int l, int r) {
	for ( int k = l; k <= r; k ++ ) ans[i] += cnt[c[k]]++;
	for ( int k = l; k <= r; k ++ ) cnt[c[k]]--;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%d", &c[i]);
	for ( int i = 0; i < m; i ++ ) { 
		scanf("%d%d", &l[i], &r[i]);
		l[i]--, r[i]--;
		q[i] = i;
	}
	sort(q, q + m, cmpL);
	for ( int i = 0; i < m; i ++ ) {
		int curId = GET_ID(l[q[i]]);
		int start = i;
		while ( i + 1 < m && GET_ID(l[q[i+1]]) == curId )
			i ++;
		int term = i, nWait = 0;
		memset(cnt, 0, sizeof(cnt));
		for ( int k = start; k <= term; k ++ )
			if ( r[q[k]] <= GET_BLK_R(curId) ) 
				bruteWork(q[k], l[q[k]], r[q[k]]);
			else
				wait[nWait++] = q[k];
		sort(wait, wait + nWait, cmpR);
		ll val = 0;
		for ( int k = GET_BLK_R(curId) + 1, ptr = 0; k < n; k ++ ) {
			val += cnt[c[k]]++;
			while ( ptr < nWait && r[wait[ptr]] == k ) {
				ans[wait[ptr]] = val;
				bruteWork(wait[ptr], l[wait[ptr]], GET_BLK_R(curId));
				ptr++;
			}
		}
	}

	for ( int i = 0; i < m; i ++ ) {
		ll a = ans[i], b = (ll)(r[i]-l[i]+1) * (r[i]-l[i]) / 2,
		   g = gcd(a, b);
		if ( b == 0 ) puts("0/1");
		else printf("%lld/%lld\n", a/g, b/g);
	}
}
