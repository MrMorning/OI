#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const int N_MAX = 100005;
const ll inf = 1000000000000000LL;

#define HOUSE -1
#define OFFICE 1
int n, L;
struct Element {
	int ori, x, type;
	Element(){}
	Element(int _ori, int _x, int _type):
		ori(_ori), x(_x), type(_type){}
	bool operator< (const Element &T) const {
		return x < T.x;
	}
} arr[N_MAX];

pair<ll, ll> note[N_MAX];
int stk[N_MAX];
int preSum[N_MAX], match[N_MAX];
int nArr = 0, nNote = 0;
int getDist(int i, int j) {
	int tmp = abs(arr[i].x - arr[j].x);
	return min(tmp, L - tmp);
}


int main() {
	scanf("%d%d", &n, &L);
	for ( int i = 0; i < n; i ++ ) {
		int x;
		scanf("%d", &x);
		arr[nArr++] = Element(i, x, HOUSE);
	}
	for ( int i = 0; i < n; i ++ ) {
		int x;
		scanf("%d", &x);
		arr[nArr++] = Element(i, x, OFFICE);
	}
	sort(arr, arr + nArr);
	n *= 2;
	for ( int i = 0; i < n; i ++ ) {
		preSum[i] = (i ? preSum[i - 1] : 0) + arr[i].type;
		if ( i + 1 < n ) 
			note[nNote++] = make_pair(preSum[i], arr[i + 1].x - arr[i].x);
		else
			note[nNote++] = make_pair(preSum[i], L - (arr[i].x - arr[0].x));
	}
	sort(note, note + nNote);
	ll cur = 0, lws = 0, rws = note[nNote - 1].second;
	for ( int i = nNote - 1; i >= 1; i -- ) {
		ll dist = note[i].first - note[i - 1].first;
		cur += rws * dist;
		rws += note[i - 1].second;
	}
	ll ans = cur, pos = note[0].first;
	lws = note[0].second;
	for ( int i = 0; i < nNote - 1; i ++ ) {
		ll dist = note[i + 1].first - note[i].first;
		rws -= note[i].second;
		cur -= rws * dist;
		cur += lws * dist;
		lws += note[i + 1].second;
		if ( cur < ans ) {
			ans = cur;
			pos = note[i + 1].first;
		}
	}
	printf(LL_FMT "\n", ans);
	for ( int i = 0; i < n; i ++ )
		if ( preSum[i] == pos ) {
			ll sum = 0;
			int top = 0;
			for ( int j = (i + 1) % n; ; j = (j + 1) % n ) {
				if ( top && arr[stk[top - 1]].type != arr[j].type ) { 
					if ( arr[j].type == -1 )
						match[arr[j].ori] = arr[stk[top - 1]].ori;
					else
						match[arr[stk[top - 1]].ori] = arr[j].ori;
					sum += getDist(j, stk[top - 1]);
					top --;
				} else
					stk[top ++] = j;
				if ( j == i )
					break;
			}
			assert(sum == ans);
			for ( int i = 0; i < n / 2; i ++ )
				printf("%d ", match[i] + 1);
			break;
		}
}
