#include <cstdio>
#include <cassert>
#include <set>
using namespace std;
typedef long long ll;
typedef set<int>::iterator itr_t;
const int kNMax = 5005;
int n, tot;
int k[kNMax], a[kNMax], x[kNMax], y[kNMax], m[kNMax];
pair<int, int> out[200005];
int nOut;
struct cmp {
	bool operator() (int i, int j) {
		return a[i] < a[j] || (a[i] == a[j] && i < j);
	}
};
set<int, cmp> S;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d%d%d%d%d", &k[i], &a[i], &x[i], &y[i], &m[i]);
		tot += k[i];
		S.insert(i);
	}
	if ( tot <= 200000 ) {
		int pre = 0, bad = 0;
		for ( int i = 0; i < tot; i ++ ) {
			a[0] = pre;
			itr_t it = S.lower_bound(0);
			if ( it == S.end() ) 
				it = S.begin();
			int t = *it;
			if ( tot <= 200000 ) 
				out[nOut++] = make_pair(a[t], t);
			bad += a[t] < pre;
			pre = a[t];
			S.erase(*it);
			k[t]--;
			if ( k[t] ) {
				a[t] = ((ll)a[t]*x[t]+y[t])%m[t];
				S.insert(t);
			}
		}
		printf("%d\n", bad);
		if ( tot <= 200000 )
			for ( int i = 0; i < nOut; i ++ )
				printf("%d %d\n", out[i].first, out[i].second);
	} else {
		int bad = 0;
		while ( 1 ) {
			int p = 0;
			for ( int i = 1; i <= n; i ++ )
				if ( k[i] )
					if ( p == 0 || a[i] < a[p] )
						p = i;
			if ( !p ) break;
			int bnd = a[p];
			bad ++;
			for ( int i = 1; i <= n; i ++ )
				if ( k[i] && a[i] >= bnd ) {
					int pre = bnd;
					while ( k[i] && a[i] >= pre ) {
						k[i]--;
						pre = a[i];
						a[i] = ((ll)a[i]*x[i]+y[i])%m[i];
					}
				}
		}
		printf("%d\n", bad-1);
	}
}
