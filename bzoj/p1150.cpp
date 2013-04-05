#include <cstdio>
#include <set>
#include <queue>
#include <iostream>
using namespace std;

typedef long long ll;

int N, K, X[100010];
ll val[100010];
bool exist[100010];

set<int> S;
priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > PQ;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d", &X[i]);
	for ( int i = 1; i < N; i ++ ) {
		S.insert(i);
		PQ.push(make_pair(X[i + 1] - X[i], i));
		val[i] = X[i + 1] - X[i];
		exist[i] = true;
	}

	ll res = 0;
	for (; K;) {
		pair<ll, int> p = PQ.top(); PQ.pop();
		if ( !exist[p.second] ) 
			continue;
		K --;
		res += p.first;
		ll newVal = -p.first;
		set<int>::iterator it = S.lower_bound(p.second);

		bool hasPrev = false, hasSucc = false;
		if ( it != S.begin() ) {
			hasPrev = true;
			set<int>::iterator pv = it;
			pv --;
			exist[*pv] = false;
			newVal += val[*pv];
			S.erase(pv);
		}

		set<int>::iterator nx = it;
		nx ++;
		if ( nx != S.end() ) {
			hasSucc = true;
			exist[*nx] = false;
			newVal += val[*nx];
			S.erase(nx);
		}

		if ( hasPrev && hasSucc ) {
			val[p.second] = newVal;
			p.first = newVal;
			PQ.push(p);
		} else {
			exist[*it] = false;
			S.erase(it);
		}
	}

	cout << res;
}
