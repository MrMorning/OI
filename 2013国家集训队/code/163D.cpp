#include <cstdio>
#include <cassert>
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
#define mp(a,b) make_pair(a, b)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pair_t;

const double kEps = 1e-6;
map <ll, pair_t> memo;
map <ll, pair<pair_t, pair_t> > memo2;
int n;
ll p[111], m[111];
ll bndB, curRem, limA, limB;
int cnt[111];
ll V;
ll minSurf, minSurfA, minSurfB, minSurfC;
int curTst;

pair_t recB(int i, ll B) {
	if ( i == n ) {
		return mp(B, curRem/B);
	}
	pair_t best = mp(0, 0);
	for ( int k = 0; B <= limB && k <= m[i]-cnt[i]; k++ ) {
		pair_t tmp = recB(i+1, B);
		if ( tmp.first != 0 )
			if ( best.first==0 || tmp.first+tmp.second<best.first+best.second )
				best = tmp;
		B = B * p[i];
	}
	return best;
}

void recA(int i, ll A) {
	if ( i == n ) {
		curRem = V/A;
		bndB = A;
		limB = floor(sqrt((long double)V/A)+kEps);

		if ( minSurf != -1 && (limB+limB)*A+V/A > minSurf ) return;

		if ( !memo.count(V/A) ) 
			memo[V/A] = recB(0, 1LL);
		pair_t pi = memo[V/A];
		if ( pi.first == 0 ) return;
		if ( minSurf==-1 || A*(pi.first+pi.second)+V/A < minSurf ) {
			minSurf = A*(pi.first+pi.second)+V/A;
			minSurfA = A, minSurfB = pi.first, minSurfC = pi.second;
		}
		return;
	}
	ll tmp = 1;
	for ( int k = 0; k < m[i]; k ++ ) tmp *= p[i];
	for ( int k = (int)m[i]; k >= 0; k --, tmp /= p[i] ) 
		if ( A*tmp <= limA ) {
			cnt[i] = k;
			recA(i+1, A*tmp);
		}
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	cin >> TST;
	for ( curTst = 1; curTst <= TST; curTst ++ ) {
		minSurf = -1;
		cin >> n;
		V = 1;
		for ( int i = 0; i < n; i ++ ) {
			cin >> p[i] >> m[i];
			for ( int t = 0; t < m[i]; t ++ )
				V = V * p[i];
		}
		if ( memo2.count(V) ) {
			cout << memo2[V].first.first << ' ' << memo2[V].first.second 
				<< ' ' << memo2[V].second.first << ' ' << memo2[V].second.second << '\n';
			continue;
		}
		limA = (ll)floor(pow((long double)V, 1.0/3.0)+kEps);
		recA(0, 1LL);
		cout << 2*minSurf << ' ' << minSurfA << ' ' << minSurfB << ' ' << minSurfC << '\n';
		memo2[V] = mp(mp(2*minSurf, minSurfA), mp(minSurfB, minSurfC));
	}
}
