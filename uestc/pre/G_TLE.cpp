#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;
int n, A, B, x[3333], axis[3333], axis_cnt, cntA[3333], cntB[3333];
void solve() {
	scanf("%d", &n);
	axis_cnt = 0;
	memset(cntA, 0, sizeof(cntA));
	memset(cntB, 0, sizeof(cntB));
	int totA = 0, totB = 0;
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &x[i]);
		axis[axis_cnt ++] = x[i];
	}
	sort(axis, axis + axis_cnt);
	axis_cnt = unique(axis, axis + axis_cnt) - axis;
	for ( int i = 1; i <= n; i ++ )
		x[i] = lower_bound(axis, axis + axis_cnt, x[i]) - axis;
	scanf("%d%d", &A, &B);

	for ( int st = 1; st + A - 1 <= n; st ++ ) {
		static multiset<int> S;
		S.clear();
		for ( int i = st; i <= st + A - 1; i ++ ) 
			S.insert(x[i]);
		int mx = *(-- S.end());
		cntA[mx] ++;
		totA ++;
		for ( int en = st + A; en <= n; en ++ ) {
			if ( x[en] < mx ) {
				S.erase(-- S.end());
				S.insert(x[en]);
				mx = *(-- S.end());
			}
			cntA[mx] ++;
			totA ++;
		}
	}
	for ( int st = 1; st + B - 1 <= n; st ++ ) {
		static multiset<int> S;
		S.clear();
		for ( int i = st; i <= st + B - 1; i ++ ) 
			S.insert(x[i]);
		int mx = *(-- S.end());
		cntB[mx] ++;
		totB ++;
		for ( int en = st + B; en <= n; en ++ ) {
			if ( x[en] < mx ) {
				S.erase(-- S.end());
				S.insert(x[en]);
				mx = *(-- S.end());
			}
			cntB[mx] ++;
			totB ++;
		}
	}

	double res = 0;
	for ( int i = 0; i < axis_cnt; i ++ )
		for ( int j = 0; j < axis_cnt; j ++ ) {
			double prob = ((double)cntA[i] / totA) * ((double)cntB[j] / totB);
			if ( i > j )
				res += prob;
			else if ( i == j )
				res += 0.5 * prob;
		}
	printf("%.6lf\n", res);
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for ( int t = 1; t <= TST; t ++ ) {
		printf("Case #%d: ", t);
		solve();
	}
}
