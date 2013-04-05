#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const int N_MAX = 100005;
const ll inf = 1000000000000000LL;

#define HOUSE 0
#define OFFICE 1
int n, L;

pair<int, int> arr[N_MAX];
int nArr = 0;
int que1[N_MAX], que2[N_MAX];
ll f[N_MAX], g[N_MAX];

int getDist(int i, int j) {
	int tmp = abs(arr[i].first - arr[j].first);
	return min(tmp, L - tmp);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &L);
	for ( int i = 0; i < n; i ++ ) {
		int x;
		scanf("%d", &x);
		arr[nArr++] = make_pair(x, HOUSE);
	}
	for ( int i = 0; i < n; i ++ ) {
		int x;
		scanf("%d", &x);
		arr[nArr++] = make_pair(x, OFFICE);
	}
	sort(arr, arr + nArr);
	n *= 2;

	for ( int i = 0; i < n; i ++ ) 
		f[i] = g[i] = inf;
	ll acc = 0;
	int qh1 = 0, qt1 = 0, qh2 = 0, qt2 = 0;
	for ( int i = 1; i < n - 1; i ++ ) {
		if ( arr[i].second == HOUSE ) {
			if ( qh2 != qt2 ) 
				acc += arr[i].first - arr[que2[qh2++]].first;
			else
				que1[qt1++] = i;
		} else {
			if ( qh1 != qt1 ) 
				acc += arr[i].first - arr[que1[qh1++]].first;
			else
				que2[qt2++] = i;
		}
		if ( qh1 == qt1 && qh2 == qt2 ) 
			f[i] = acc;
	}

	acc = 0;
	qh1 = 0, qt1 = 0, qh2 = 0, qt2 = 0;
	for ( int i = n - 1; i > 1; i -- ) {
		if ( arr[i].second == HOUSE ) {
			if ( qh2 != qt2 ) 
				acc += arr[que2[qh2++]].first - arr[i].first;
			else
				que1[qt1++] = i;
		} else {
			if ( qh1 != qt1 ) 
				acc += arr[que1[qh1++]].first - arr[i].first;
			else
				que2[qt2++] = i;
		}
		if ( qh1 == qt1 && qh2 == qt2 ) 
			g[i] = acc;
	}

	ll ans = min(f[n - 2] + getDist(0, n - 1), g[2] + getDist(0, 1));
	for ( int mid = 2; mid < n - 1; mid ++ ) 
		ans = min(ans, getDist(0, mid) + f[mid - 1] + g[mid + 1]);
	printf(LL_FMT "\n", ans);
}
