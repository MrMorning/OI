#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kNMax = 100010;
int cnt1, cnt2, cnt3, cnt4;
int arr3[kNMax], arr4[kNMax];
int c[kNMax], f[kNMax], l[kNMax];
int n, d, S;

bool cmpF(int i, int j) {
	return f[i] < f[j];
}

pair<int, int> work(int S, int lim) {
	pair<int, int> ret = make_pair(0, 0);
	for ( int i = 0; ret.first < lim && i < cnt3; i ++ ) {
		if ( S < f[arr3[i]] )
			break;
		S -= f[arr3[i]];
		ret.second += f[arr3[i]];
		ret.first++;
	}
	return ret;
}

int main() {
	scanf("%d%d%d", &n, &d, &S);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d%d%d", &c[i], &f[i], &l[i]);
		if ( c[i] == 0 && l[i] < d ) 
			cnt1 ++;
		if ( c[i] > 0 && l[i] < d )
			cnt2 ++;
		if ( c[i] == 0 && l[i] >= d )
			arr3[cnt3++] = i;
		if ( c[i] > 0 && l[i] >= d )
			arr4[cnt4++] = i;
	}
	sort(arr3, arr3 + cnt3, cmpF);
	sort(arr4, arr4 + cnt4, cmpF);
	pair<int, int> tmpp = work(S, cnt3);
	if ( !(cnt4 == 0 || f[arr4[0]] > S) ) {
		int best = arr4[0];
		S -= f[best];
		ll sumC = 0;
		int goodCnt = 0;
		for ( int i = 0; i < n; i ++ )
			if ( c[i] > 0 ) {
				goodCnt++;
				sumC += c[i];
			}
		if ( cnt4 - 1 <= cnt1 ) {
			for ( int i = 1; i < cnt4; i ++ )
				arr3[cnt3++] = arr4[i];
			cnt1 -= cnt4 - 1;
		} else {
			for ( int i = 1; i <= cnt1; i ++ )
				arr3[cnt3++] = arr4[i];
			sort(arr3, arr3 + cnt3, cmpF);

			for ( int i = cnt1 + 1, j = cnt3 - 1; j >= 0 && i < cnt4; i ++, j -- ) {
				f[arr3[j]] = min(f[arr3[j]], f[arr4[i]]);
			}
			sort(arr3, arr3 + cnt3, cmpF);
			cnt1 = 0;
		}

		int more = (int)min((ll)cnt1 + cnt3, sumC - goodCnt + 1);
		pair<int, int> tmp;
		if ( more <= cnt1 ) 
			tmp = work(S, cnt3);
		else
			tmp = work(S, cnt3 - (more - cnt1));
		tmp.first += more + goodCnt;
		tmp.second += f[best];
		if ( tmp.first > tmpp.first || (tmp.first == tmpp.first && tmp.second < tmpp.second) )
			tmpp = tmp;
	}
	printf("%d %d\n", tmpp.first, tmpp.second);
}
